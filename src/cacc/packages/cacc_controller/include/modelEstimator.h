#ifndef MODEL_ESTIMATOR_H_
#define MODEL_ESTIMATOR_H_
#pragma once

#include <math.h>
#include <float.h>
#include <vector>
#include <cgmres_lib/model.hpp>
#include <carFollowing.h>
#include <ros/ros.h>

#pragma pack(1)
#include <cacc_msgs/PrarxParam.h>
#pragma pack()

class ModelEstimator{	
protected:
    ros::NodeHandle nh;
    ros::NodeHandle private_nh;
    
    ros::Publisher param_pub;
    ros::Subscriber param_sub;
    std::string param_pub_topic, param_sub_topic;

    double initialTheta[2][4];
    double initialEta[4];
    double initialScale[3];
    double theta[2][4];
    double eta[4];
    double scale[3];

    double delay;
    double envScale;

    std::vector<std::vector<double> > phi;
    std::vector<double> y;
    int maxNumberOfData;

    double alpha;
    double beta;

    void paramCallback(const cacc_msgs::PrarxParam msg){
        for(int i = 0; i < 4; i++){
			theta[0][i] = msg.theta1[i];
			theta[1][i] = msg.theta2[i];
			eta[i] = msg.eta[i];
			if(i != 3) scale[i] = msg.scale[i];			
		}
    };

public:
    ModelEstimator(float _delay, float _envScale):private_nh("~"){
		initialTheta[0][0] = 0.0797;
		initialTheta[0][1] = 0.9301;
		initialTheta[0][2] = -0.0686;
		initialTheta[0][3] = -0.1249;
		initialTheta[1][0] = -0.0754;
		initialTheta[1][1] = 0.6978;
		initialTheta[1][2] = 0.1139;
		initialTheta[1][3] = 0.1247;
		initialEta[0] = 8.6222;
		initialEta[1] = 0.7597;
		initialEta[2] = -1.7087;
		initialEta[3] = -9.8580;
		initialScale[0] = 52.0;
		initialScale[1] = 7.3;
		initialScale[2] = 7.8;

        theta[0][0] = 0.0797;
		theta[0][1] = 0.9301;
		theta[0][2] = -0.0686;
		theta[0][3] = -0.1249;
		theta[1][0] = -0.0754;
		theta[1][1] = 0.6978;
		theta[1][2] = 0.1139;
		theta[1][3] = 0.1247;
		eta[0] = 8.6222;
		eta[1] = 0.7597;
		eta[2] = -1.7087;
		eta[3] = -9.8580;
		scale[0] = 52.0;
		scale[1] = 7.3;
		scale[2] = 7.8;

        delay = _delay;
        envScale = _envScale;
    };

    void init(){
        private_nh.param<std::string>("param_sub_topic", param_sub_topic, "curr_param");
        private_nh.param<std::string>("param_pub_topic", param_pub_topic, "updated_param");
        private_nh.param<int>("maxNumberOfData", maxNumberOfData, 1000);
        private_nh.param<double>("alpha", alpha, 0.01);
        private_nh.param<double>("beta", beta, 0.01);

        param_sub = nh.subscribe(param_sub_topic, 1, &ModelEstimator::paramCallback, this);
        param_pub = nh.template advertise<cacc_msgs::PrarxParam>(param_pub_topic,1);        
    };

    void resetInitialParams(double* _theta1, double* _theta2, double* _eta, double* _scale){
		for(int i = 0; i < 4; i++){
			initialTheta[0][i] = _theta1[i];
			initialTheta[1][i] = _theta2[i];
			initialEta[i] = _eta[i];
			if(i != 3) initialScale[i] = _scale[i];			
		}
    };

    void resetParams(){
		for(int i = 0; i < 4; i++){
			theta[0][i] = initialTheta[0][i];
			theta[1][i] = initialTheta[1][i];
			eta[i] = initialEta[i];
			if(i != 3) scale[i] = initialScale[i];			
		}
    };

	void addData(std::vector<double> _phi, double _y){
        phi.push_back(_phi);
        if(phi.size() > maxNumberOfData){
            while(phi.size() <= maxNumberOfData){
                phi.erase(phi.begin());
            }
        }
        y.push_back(_y);
        if(y.size() > maxNumberOfData){
            while(y.size() <= maxNumberOfData){
                y.erase(y.begin());
            }
        }
    };

    void update(){
        double gradientTheta[2][4], gradientEta[4];
        for(int i = 0; i < 4; i++){
            gradientTheta[0][i] = 0.0;
            gradientTheta[1][i] = 0.0;
            gradientEta[i] = 0.0;
        }
        
        PrarxModel model(&theta[0][0],&theta[1][0],eta,scale,delay,envScale,1.0,-1.0);
        int dataNum = phi.size();
        
        for(int id = 0; id < dataNum; id++){
            double y_est, theta1_phi, theta2_phi, eta_phi, w, P, error;

            //Set phi
            model.setMeasurement(ros::Time::now(), 0, phi[id][2], phi[id][0], phi[id][1]);
            
            //Get model output
            model.getOutput(&y_est, &theta1_phi, &theta2_phi, &eta_phi, &w, &P); 
            error = y[id] - y_est;

            //Calculate gradients
            for(int i = 0; i < 4; i++){
                gradientTheta[0][i] += 2*(1-P)*phi[id][i]*error/(-dataNum);
                gradientTheta[1][i] += 2*P*phi[id][i]*error/(-dataNum);
                gradientEta[i] += gradientTheta[0][i]*(theta1_phi - y_est)/(-dataNum);
            }
        }

        //Update params
        for(int i = 0; i < 4; i++){
            theta[0][i] += -alpha * gradientTheta[0][i];
            theta[1][i] += -alpha * gradientTheta[1][i];
            eta[i] += -beta * gradientEta[i];
        }
        ROS_INFO("PrARX model updated. \nGradient_theta1: [%f, %f, %f, %f]\nGradient_theta2: [%f, %f, %f, %f]\nGradient_eta: [%f, %f, %f, %f]", 
                    gradientTheta[0][0],gradientTheta[0][1],gradientTheta[0][2],gradientTheta[0][3], 
                    gradientTheta[1][0],gradientTheta[1][1],gradientTheta[1][2],gradientTheta[1][3],
                    gradientEta[0],gradientEta[1],gradientEta[2],gradientEta[3]);
        
    };

    void publishParams(){
        cacc_msgs::PrarxParam msg;
        for(int i = 0; i < 4; i++){
			msg.theta1.push_back(theta[0][i]);
			msg.theta2.push_back(theta[1][i]);
			msg.eta.push_back(eta[i]);
			if(i != 3) msg.scale.push_back(scale[i]);		
		}

        param_pub.publish(msg);
    };

};
#endif //MODEL_ESTIMATOR_H_