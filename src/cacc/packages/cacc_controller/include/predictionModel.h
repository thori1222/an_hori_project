#ifndef PREDICTION_MODEL_H_
#define PREDICTION_MODEL_H_
#pragma once

#include <math.h>
#include <float.h>
#include <cgmres_lib/model.hpp>
#include <carFollowing.h>
#include <ros/ros.h>

#pragma pack(1)
#include <cacc_msgs/PrarxParam.h>
#pragma pack()

template<int NCAR>
class PredictionModel{
using x_t = typename Model<3*NCAR, 1*NCAR>::x_t;
	
protected:
	int idx;

    ros::NodeHandle nh;
    ros::NodeHandle private_nh;
    ros::Publisher param_pub;
    ros::Subscriber param_sub;
    std::string param_pub_topic, param_sub_topic;

    void rosSetup(){
        param_pub_topic = "model_"+std::to_string(idx)+"/curr_param";
        param_sub_topic = "model_"+std::to_string(idx)+"/updated_param";
    };
    void rosSetup(std::string _param_pub, std::string _param_sub){
        param_pub_topic = _param_pub;
        param_sub_topic = _param_sub;
    };
    virtual void pubSubSetup() = 0;

public:
	PredictionModel(int _idx):private_nh("~"){
        idx = _idx;
    };
    void init(){
        rosSetup();
        pubSubSetup();
    };
    void init(std::string _param_pub, std::string _param_sub){
        rosSetup(_param_pub, _param_sub);
        pubSubSetup();
    };
    int getIdx(){return idx;};
	virtual void cal_output(const x_t &in_x, double* out_y) = 0;
	virtual void cal_dt(const x_t &in_x, double* out_dt) = 0;
	virtual void cal_dfdx(const x_t &in_x, x_t* out_dfdx) = 0;
};



// PrARX model
template<int NCAR>
class Prarx : public PredictionModel<NCAR>{
    using x_t = typename Model<3*NCAR, 1*NCAR>::x_t;
protected:    
	PrarxModel* model;

    void paramCallback(const cacc_msgs::PrarxParam msg){
        double theta1[4], theta2[4], eta[4], scale[3];
        for(int i = 0; i < 4; i++){
			theta1[i] = msg.theta1[i];
			theta2[i] = msg.theta2[i];
			eta[i] = msg.eta[i];
			if(i != 3) scale[i] = msg.scale[i];			
		}

        this->model->setParameters(theta1, theta2, eta, scale);
    };

    void pubSubSetup(){
        this->param_pub = this->nh.template advertise<cacc_msgs::PrarxParam>(this->param_pub_topic,1);
        this->param_sub = this->nh.subscribe(this->param_sub_topic, 1, &Prarx::paramCallback, this);
    };

public:
	Prarx(int _idx):PredictionModel<NCAR>(_idx){
		this->model = new PrarxModel();
        init();
    }
	Prarx(int _idx, std::string _param_pub, std::string _param_sub):PredictionModel<NCAR>(_idx, _param_pub, _param_sub){
		this->model = new PrarxModel();
        init(_param_pub, _param_sub);
    }
    Prarx(int _idx, PrarxModel* _model):PredictionModel<NCAR>(_idx){
		this->model = _model;
        init();
    }
    Prarx(int _idx, PrarxModel* _model, std::string _param_pub, std::string _param_sub):PredictionModel<NCAR>(_idx, _param_pub, _param_sub){
		this->model = _model;
        init(_param_pub, _param_sub);
    }
	~Prarx(){
		delete this->model;
	}
    void init(){
        this->rosSetup();
        pubSubSetup();
    };
    void init(std::string _param_pub, std::string _param_sub){
        this->rosSetup(_param_pub, _param_sub);
        pubSubSetup();
    };

    void set_model(PrarxModel* _model){
        this->model = _model;
    }
    void publishParams(){
        cacc_msgs::PrarxParam msg;
        double theta1[4], theta2[4], eta[4], scale[3];
        this->model->getParameters(theta1, theta2, eta, scale);

        for(int i = 0; i < 4; i++){
			msg.theta1.push_back(theta1[i]);
			msg.theta2.push_back(theta2[i]);
			msg.eta.push_back(eta[i]);
			if(i != 3) msg.scale.push_back(scale[i]);		
		}

        this->param_pub.publish(msg);
    };
    void cal_output(const x_t &in_x, double* out_y, double* theta1_phi, double* theta2_phi, double* eta_phi, double* w, double* P)
	{
		this->model->setMeasurement(ros::Time::now(), in_x[3*(this->idx)+1], in_x[3*(this->idx)+2], in_x[3*(this->idx)+0], 
								in_x[3*((this->idx)-1)+1] - in_x[3*(this->idx)+1]);

        this->model->getOutput(out_y, theta1_phi, theta2_phi, eta_phi, w, P);
	}

    void cal_output(const x_t &in_x, double* out_y){
        double theta1_phi, theta2_phi, eta_phi, w, P;
		this->cal_output(in_x, out_y, &theta1_phi, &theta2_phi, &eta_phi, &w, &P);
    }

    void cal_output(const x_t &in_x, double* out_y, double* P)
	{
		double theta1_phi, theta2_phi, eta_phi, w;
		this->cal_output(in_x, out_y, &theta1_phi, &theta2_phi, &eta_phi, &w, P);
	}

    void cal_dt(const x_t &in_x, double* out_dt){
        double y;
        this->cal_output(in_x, &y);
        *out_dt = (y - in_x[3*(this->idx)+2])/(model->getDelay());
    }
    
    void cal_dfdx(const x_t &in_x, x_t* out_dfdx){
        double y, theta1_phi, theta2_phi, eta_phi, w, P;
        double theta1[4], theta2[4], eta[4], scale[3];
		double tmp;
        double M[3];
        double P_phi[3];

        for(int ic = 0; ic < 3*NCAR; ic++){
            *out_dfdx[ic] = 0.0;
        }
        this->model->getParameters(theta1, theta2, eta, scale);

        this->cal_output(in_x, &y, &theta1_phi, &theta2_phi, &eta_phi, &w, &P);
        tmp = w / ((1+w)*(1+w));
				
        P_phi[0] = eta[0] * tmp;
		P_phi[1] = eta[1] * tmp;
		P_phi[2] = eta[2] * tmp;

        M[0] = scale[2] * (P_phi[0] * (theta2_phi - theta1_phi) + (1 - P)*theta1[0] + P*theta2[0]) / scale[0];
		M[1] = scale[2] * (P_phi[1] * (theta2_phi - theta1_phi) + (1 - P)*theta1[1] + P*theta2[1]) / scale[1];
		M[2] = scale[2] * (P_phi[2] * (theta2_phi - theta1_phi) + (1 - P)*theta1[2] + P*theta2[2]) / scale[2];

        *out_dfdx[3*(this->idx)+0] = M[0]/(model->getDelay()) * 1;
        *out_dfdx[3*(this->idx)+1] = M[1]/(model->getDelay()) * (-1);
		if((this->idx) != 0) *out_dfdx[3*((this->idx)-1)+1] += M[1]/(model->getDelay()) * 1;
        *out_dfdx[3*(this->idx)+2] = (M[2]-1)/(model->getDelay()) * 1;	
    }
};

#endif //PREDICTION_MODEL_H_