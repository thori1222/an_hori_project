#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

// state equations
Eigen::MatrixXf f_6D(Eigen::MatrixXf state, std::vector<Eigen::MatrixXf> args, double dt)
{
	double dim_x = state.cols();
	double X		= state(0, 0);
	double Y		= state(0, 1);
	double theta		= state(0, 2);
	double vx		= state(0, 3);
	double vy		= state(0, 4);
	double r		= state(0, 5);

	// control input u
	double steer = (args.at(0))(0, 0);
	double FxR	 = (args.at(0))(0, 0);
	double FxF   = FxR;						// this RC car is 4 wheel drive --> FxF = FxR

	// vehicle model - physical parameters
	double lf = (args.at(1))(0, 0);
	double lr = (args.at(1))(0, 1);
	double m  = (args.at(1))(0, 2);
	double Iz = (args.at(1))(0, 3);

	// Tire model
	double Kf = (args.at(2))(0, 0);
	double Kr = (args.at(2))(0, 1);
	double mu = (args.at(2))(0, 2);

	// External forces
	double c_air = (args.at(3))(0, 0);
	double F_fric = (args.at(3))(0, 1);

	double g = 9.81;
	double Fn = m * g;	// normal force

	if (FxR >= mu * Fn) {	// slip
		FxR = mu * Fn;
		FxF = FxR;
	}

	double beta_f = atan((vy + lf * r) / vx);	// slip angle of front wheel
	double beta_r = atan((vy - lr * r) / vx);	// slip angle of rear wheel

	double FyF = -Kf * beta_f;
	double FyR = -Kr * beta_r;

	// state equations
	double X_next = X + dt * (vx*cos(theta) - vy * sin(theta));
	double Y_next = Y + dt * (vx*sin(theta) + vy * cos(theta));
	double theta_next = theta + dt * r;

	double vx_next = vx + dt * (r*vy + 1 / m * (FxR - FyF * sin(steer) + FxF * cos(steer) - c_air * pow(vx,2) - F_fric));
	double vy_next = vy + dt * (-r * vx + 1 / m * (FyF*cos(steer) + FxF * sin(steer) + FyR));
	double r_next  = r + dt / Iz * (lf *(FyF*cos(steer) + FxF * sin(steer) - FyR * lr));

	Eigen::MatrixXf temp(6, 1);
	temp(0, 0) = X_next;
	temp(1, 0) = Y_next;
	temp(2, 0) = theta_next;
	temp(3, 0) = vx_next;
	temp(4, 0) = vy_next;
	temp(5, 0) = r_next;

	return temp;	// state next step
}

// measurements are X, Y, theta (from OptiTrack) and r (from IMU)
Eigen::MatrixXf h_6D(Eigen::MatrixXf x)
{
	Eigen::MatrixXf C(4, 6);
	C.setZero(4, 6);
	C(0, 0) = 1;
	C(1, 1) = 1;
	C(2, 2) = 1;
	C(3, 5) = 1;
	return C * x;
}

