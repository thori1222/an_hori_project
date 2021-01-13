#ifndef CAR_FOLLOWING_H_
#define CAR_FOLLOWING_H_
#pragma once

#include <math.h>
#include <iostream>
#include <float.h>
#include <ros/ros.h>

class FollowingControl{
protected:
	ros::Time time, time_prev;
	double speed;
	double acceleration;
	double range, range_prev;
	double rangeRate;
	double inversedTTC;
	double THW;

	void setTime(ros::Time _time){
		time_prev = time;
		time = _time;
	};
	void setSpeed(double _speed){speed = _speed;};
	void setAcceleration(double _acceleration){acceleration = _acceleration;};
	void setRange(double _range){
		range_prev = range;
		range = _range;
	};
	void setRangeRate(double _rangeRate){
		rangeRate = _rangeRate;
	};
	void updateState(){
		double tmp;

		// Range rate
		tmp = (time - time_prev).toSec();
		rangeRate = 0.9*rangeRate + 0.1*(range - range_prev)/(tmp<0.001?0.001:tmp);

		// Inversed TTC
		inversedTTC = -1 * rangeRate / (range<0.01?0.01:range);

		// THW
		THW = range / (speed<0.01?0.01:speed);
	};
	void updateState(double _rangeRate){
		setRangeRate(_rangeRate);

		// Inversed TTC
		inversedTTC = -1 * rangeRate / (range<0.01?0.01:range);

		// THW
		THW = range / (speed<0.01?0.01:speed);
	};

public:
	FollowingControl(){};

	double getSpeed(){return speed;};
	double getAcceleration(){return acceleration;};
	double getRange(){return range;};
	double getRangeRate(){return rangeRate;};
	double getInversedTTC(){return inversedTTC;};
	double getTHW(){return THW;};

	void setMeasurement(ros::Time _time, double _speed, double _acceleration, double _range){
		setTime(_time);
		setSpeed(_speed);
		setAcceleration(_acceleration);
		setRange(_range);

		updateState();
	};
	void setMeasurement(ros::Time _time, double _speed, double _acceleration, double _range, double _rangeRate){
		setTime(_time);
		setSpeed(_speed);
		setAcceleration(_acceleration);
		setRange(_range);

		updateState(_rangeRate);
	};
	
	virtual double getOutputSpeed(){};
	virtual double getOutputAcceleration(){};
};

// Jude's model (4-mode model)
class JudeModel : public FollowingControl{
protected:
	double coef[4][5]; //speed, range, TTC^(-1), THW, 1 (offset)
	double scale[4]; //speed, range, TTC^(-1), THW
	double delay;

	double envScale;
	double maxOutput;
	double minOutput;

	double calculateOutput(int mode){
		if(mode < 0 || mode > 3){
			std::cout<<"(Error)JudeModel: mode number is not correct! mode: "<<mode<<std::endl;
			return 0;
		}

		double output = coef[mode][0]*(speed/envScale)/scale[0] 
						+ coef[mode][1]*(range/envScale)/scale[1]
						+ coef[mode][2]*inversedTTC/scale[2] 
						+ coef[mode][3]*THW/scale[3] 
						+ coef[mode][4];
		output = output * scale[0] * envScale;

		if(output > maxOutput) output = maxOutput;
		else if(output < minOutput) output = minOutput;

		return output;
	};

public:
	JudeModel(){
		coef[0][0] = 0.0058;
		coef[0][1] = 0.9590;
		coef[0][2] = 0.0;
		coef[0][3] = 0.0461;
		coef[0][4] = 0.0131;

		coef[1][0] = 0.0036;
		coef[1][1] = 0.9891;
		coef[1][2] = 0.0118;
		coef[1][3] = -0.0647;
		coef[1][4] = -0.0285;

		coef[2][0] = 0.0182;
		coef[2][1] = 0.9940;
		coef[2][2] = 0.0;
		coef[2][3] = -0.0261;
		coef[2][4] = 0.0634;

		coef[3][0] = 0.0203;
		coef[3][1] = 0.0;
		coef[3][2] = 0.0;
		coef[3][3] = 0.9792;
		coef[3][4] = -0.0411;

		scale[0] = 15.8333;
		scale[1] = 39.4108;
		scale[2] = 0.8812;
		scale[3] = 38.7758;

		delay = 0.3;

		envScale = 0.1;
		maxOutput = 2.0;
		minOutput = 0.0;
	};
	JudeModel(double _envScale, double _maxOutput, double _minOutput){
		coef[0][0] = 0.0058;
		coef[0][1] = 0.9590;
		coef[0][2] = 0.0;
		coef[0][3] = 0.0461;
		coef[0][4] = 0.0131;

		coef[1][0] = 0.0036;
		coef[1][1] = 0.9891;
		coef[1][2] = 0.0118;
		coef[1][3] = -0.0647;
		coef[1][4] = -0.0285;

		coef[2][0] = 0.0182;
		coef[2][1] = 0.9940;
		coef[2][2] = 0.0;
		coef[2][3] = -0.0261;
		coef[2][4] = 0.0634;

		coef[3][0] = 0.0203;
		coef[3][1] = 0.0;
		coef[3][2] = 0.0;
		coef[3][3] = 0.9792;
		coef[3][4] = -0.0411;

		scale[0] = 15.8333;
		scale[1] = 39.4108;
		scale[2] = 0.8812;
		scale[3] = 38.7758;

		delay = 0.3;

		envScale = _envScale;
		maxOutput = _maxOutput;
		minOutput = _minOutput;
	};

	double getOutputSpeed(){
		int mode = -1;
		if(range/envScale < 11){
			mode = 0;
		}
		else if(range/envScale < 21){
			mode = 1;
		}
		else if(range/envScale < 31){
			mode = 2;
		}
		else{
			mode = 2;
		}
		double vel_ref = calculateOutput(mode);
		printf("=======================\n");
		printf("Mode: %d\nSpeed: %f\nRefereceSpeed: %f\n", mode, speed, vel_ref);

		return vel_ref;		
	};

	double getOutputAcceleration(){
		double vel_ref = getOutputSpeed();
		return (vel_ref - speed)/0.1;
	};
	double getOutputAcceleration(double dt){
		double vel_ref = getOutputSpeed();
		return (vel_ref - speed)/dt;
	};

};


// PrARX model (2-mode model)
class PrarxModel : public FollowingControl{
protected:
	double theta[2][4];
	double eta[4];
	double scale[3];
	double delay;
	
	double envScale;
	double maxOutput;
	double minOutput;
	double modeProbability;

	double calculateOutput(){
		double theta_phi[2];
		double eta_phi;
		double xc[4];
		double w, P;

        std::cout << range << std::endl;

		xc[0] = (range/envScale) / scale[0];
		xc[1] = (rangeRate/envScale) / scale[1];
		xc[2] = (acceleration/envScale) / scale[2];
		//xc[0] = range;
		//xc[1] = rangeRate;
		//xc[2] = acceleration;
		xc[3] = 1.0;

		for(int i = 0; i < 2; i++){
			theta_phi[i] = 0;
			eta_phi = 0;
			for(int j = 0; j < 4; j++){
				theta_phi[i] += theta[i][j]*xc[j];
				eta_phi += eta[j]*xc[j];
			}
			if(theta_phi[i]*scale[2] > (maxOutput/envScale)) theta_phi[i] = (maxOutput/envScale) / scale[2];
			else if(theta_phi[i]*scale[2] < (minOutput/envScale)) theta_phi[i] = (minOutput/envScale) / scale[2];
			
			double lim = 20.0;
			if(eta_phi > lim) eta_phi = lim;
			else if(eta_phi < lim) eta_phi = lim;
		}

		w = exp(eta_phi);
		P = 1 / (w+1);

		modeProbability = P;

		return envScale * scale[2] * ((1-P)*theta_phi[0] + P*theta_phi[1]);
		//return ((1-P)*theta_phi[0] + P*theta_phi[1]);
	};

	void calculateOutput(double* _y, double* _theta1_phi, double* _theta2_phi, double* _eta_phi, double* _w, double* _P){
		double theta_phi[2];
		double eta_phi;
		double xc[4];

		xc[0] = (range/envScale) / scale[0];
		xc[1] = (rangeRate/envScale) / scale[1];
		xc[2] = (acceleration/envScale) / scale[2];
		xc[3] = 1.0;

		for(int i = 0; i < 2; i++){
			theta_phi[i] = 0;
			eta_phi = 0;
			for(int j = 0; j < 4; j++){
				theta_phi[i] += theta[i][j]*xc[j];
				eta_phi += eta[j]*xc[j];
			}
			if(theta_phi[i]*scale[2] > (maxOutput/envScale)) theta_phi[i] = (maxOutput/envScale) / scale[2];
			else if(theta_phi[i]*scale[2] < (minOutput/envScale)) theta_phi[i] = (minOutput/envScale) / scale[2];
			
			double lim = 20.0;
			if(eta_phi > lim) eta_phi = lim;
			else if(eta_phi < lim) eta_phi = lim;
		}
		

		*_w = exp(eta_phi);
		*_P = 1 / (*_w+1);

		modeProbability = *_P;

		*_y = 0;   //constant speed prediction
		//*_y = envScale * scale[2] * ((1-*_P)*theta_phi[0] + *_P*theta_phi[1]);
		*_theta1_phi = theta_phi[0];
		*_theta2_phi = theta_phi[1];
		*_eta_phi = eta_phi;
	};

public:
	PrarxModel(){
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

		delay = 0.3;

		envScale = 1.0;
		maxOutput = 2.0;
		minOutput = -2.0;
	};
	PrarxModel(double _envScale, double _maxOutput, double _minOutput){
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

		delay = 0.3;

		envScale = _envScale;
		maxOutput = _maxOutput;
		minOutput = _minOutput;
	};
	PrarxModel(double* _theta1, double* _theta2, double* _eta, double* _scale, double _delay, double _envScale, double _maxOutput, double _minOutput){
		theta[0][0] = _theta1[0];
		theta[0][1] = _theta1[1];
		theta[0][2] = _theta1[2];
		theta[0][3] = _theta1[3];
		theta[1][0] = _theta2[0];
		theta[1][1] = _theta2[1];
		theta[1][2] = _theta2[2];
		theta[1][3] = _theta2[3];
		eta[0] = _eta[0];
		eta[1] = _eta[1];
		eta[2] = _eta[2];
		eta[3] = _eta[3];

		scale[0] = _scale[0];
		scale[1] = _scale[1];
		scale[2] = _scale[2];

		delay = _delay;

		envScale = _envScale;
		maxOutput = _maxOutput;
		minOutput = _minOutput;
	};

	double getOutputAcceleration(){
		return calculateOutput();
	};
	void getOutput(double* _y, double* _theta1_phi, double* _theta2_phi, double* _eta_phi, double* _w, double* _P){
		this->calculateOutput(_y, _theta1_phi, _theta2_phi, _eta_phi, _w, _P);
	};
	double getOutputSpeed(){
		return speed + delay * calculateOutput() * 5;
	};
	double getDelay(){
		return delay;
	};
	double getProbability(){
		return modeProbability;
	};
	void getParameters(double* _theta1, double* _theta2, double* _eta, double* _scale){
		_theta1[0] = theta[0][0];
		_theta1[1] = theta[0][1];
		_theta1[2] = theta[0][2];
		_theta1[3] = theta[0][3];
		_theta2[0] = theta[1][0];
		_theta2[1] = theta[1][1];
		_theta2[2] = theta[1][2];
		_theta2[3] = theta[1][3];
		_eta[0] = eta[0];
		_eta[1] = eta[1];
		_eta[2] = eta[2];
		_eta[3] = eta[3];
		_scale[0] = scale[0];
		_scale[1] = scale[1];
		_scale[2] = scale[2];
	};

	void setParameters(double* _theta1, double* _theta2, double* _eta, double* _scale){
		for(int i = 0; i < 4; i++){
			theta[0][i] = _theta1[i];
			theta[1][i] = _theta2[i];
			eta[i] = _eta[i];
			if(i != 3) scale[i] = _scale[i];			
		}
	};
};


// Gipps model
class GippsModel : public FollowingControl{
protected:
	double maxAcceleration;
	double maxBrake;
	double travelSpeed;
	double stopDistance;

	double delay;
	double envScale;

	double calculateOutput(){
		double leadingSpeed = speed + rangeRate;
		printf("===========================================\n");
		printf("Leading speed: %f\nSpeed: %f\nRange: %f\nAcceleration: %f\n", leadingSpeed, speed, range, acceleration);
		// double output = speed/envScale + 2.5*acceleration/envScale*delay*(1-speed/envScale/travelSpeed)*sqrt(0.025+speed/envScale/travelSpeed);
		// double tmp = maxBrake*delay + sqrt(maxBrake*maxBrake*delay*delay - maxBrake*2*(range/envScale-stopDistance) - speed/envScale*delay - leadingSpeed/envScale*leadingSpeed/envScale/maxBrake);
		double output = speed + 2.5*maxAcceleration*delay*(1-speed/(travelSpeed*envScale))*sqrt(0.025+speed/(travelSpeed*envScale));
		double tmp = (maxBrake*envScale)*delay + sqrt((maxBrake*envScale)*(maxBrake*envScale)*delay*delay - maxBrake*envScale*2*(range-(stopDistance*envScale)) - speed*delay - leadingSpeed*leadingSpeed/(maxBrake*envScale));
		printf("Output1: %f\nOutput2: %f\n", output, tmp);
		if(tmp < output) output = tmp;
		return output;
	};

	double calculateOutput(double leadingSpeed){
		double output = speed/envScale + 2.5*acceleration/envScale*delay*(1-speed/envScale/travelSpeed)*sqrt(0.025+speed/envScale/travelSpeed);
		double tmp = maxBrake*delay + sqrt(maxBrake*maxBrake*delay*delay - maxBrake*2*(range/envScale-stopDistance) - speed/envScale*delay - leadingSpeed/envScale*leadingSpeed/envScale/maxBrake);
		if(tmp < output) output = tmp;
		return output*envScale;
	};

public:
	GippsModel(){
		maxAcceleration = 0.8;
		maxBrake = -6.0;
		travelSpeed = 60.0 * 1000.0/3600.0;
		stopDistance = 5.0;

		delay = 0.2;
		envScale = 0.1;
	};
	GippsModel(double _envScale){
		maxAcceleration = 0.8;
		maxBrake = -6.0;
		travelSpeed = 60.0 * 1000.0/3600.0;
		stopDistance = 5.0;

		delay = 0.2;
		envScale = _envScale;
	};

	double getOutputSpeed(){
		return calculateOutput();		
	};

	double getOutputSpeed(double leadingSpeed){
		return calculateOutput(leadingSpeed);		
	};

	double getOutputAcceleration(){
		double vel_ref = calculateOutput();
		return (vel_ref - speed)/delay;
	};
	double getOutputAcceleration(double leadingSpeed){
		double vel_ref = calculateOutput(leadingSpeed);
		return (vel_ref - speed)/delay;
	};

};


#endif