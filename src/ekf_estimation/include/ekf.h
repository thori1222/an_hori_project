#pragma once
#include <Eigen/Core>
#include <tuple>
#include <functional>
#include <vector>
#include <algorithm>
#include <car_model_6D.h>

// ===================================================================
// Reference: An Introduction to the Kalman Filter
// Link: https://www.cs.unc.edu/~welch/media/pdf/kalman_intro.pdf
// BARC project - UC Berkeley
// Link: http://www.barc-project.com/
// and : https://github.com/MPC-Berkeley/barc
// ===================================================================

using namespace std;


// f(x,args,dt) function
Eigen::MatrixXf numerical_jac_fx(std::function<Eigen::MatrixXf(Eigen::MatrixXf, std::vector<Eigen::MatrixXf>, double)>f, 
	Eigen::MatrixXf x, 
	std::vector<Eigen::MatrixXf> args, 
	double dt) 
{
	Eigen::MatrixXf y = f(x, args, dt);
	Eigen::MatrixXf xp(x);
	double eps = 1e-5;

	// create zero matrix
	Eigen::MatrixXf jac(y.cols(), x.cols());
	jac.setZero(y.cols(), x.cols());

	Eigen::MatrixXf yhi, ylo;

	for (int i = 0; i < x.cols(); i++) {
		xp(0, i) = x(0, i) + eps / 2.0;
		yhi = f(xp,args,dt);
		xp(0, i) = x(0, i) - eps / 2.0;
		ylo = f(xp,args,dt);
		xp(0, i) = x(0, i);
		jac.col(i) = (yhi - ylo) / eps;
	}

	return jac;
}


// h(x) function
Eigen::MatrixXf numerical_jac_hx(std::function<Eigen::MatrixXf(Eigen::MatrixXf)>h, 
	Eigen::MatrixXf x)
{
	Eigen::MatrixXf y = h(x);
	Eigen::MatrixXf xp(x);
	double eps = 1e-5;

	// create zero matrix
	Eigen::MatrixXf jac(y.cols(), x.cols());
	jac.setZero(y.cols(), x.cols());

	Eigen::MatrixXf yhi, ylo;

	for (int i = 0; i < x.cols(); i++) {
		xp(0, i) = x(0, i) + eps / 2.0;
		yhi = h(xp);
		xp(0, i) = x(0, i) - eps / 2.0;
		ylo = h(xp);
		xp(0, i) = x(0, i);
		jac.col(i) = (yhi - ylo) / eps;
	}

	return jac;
}

// ekf(f_k, mx_k, P_k, h, y_kp1, Q, R, args, dt);
// return:	posteriori state: f_kp1
//			posteriori error covariance: P_kp1

std::tuple<Eigen::MatrixXf, Eigen::MatrixXf> ekf(std::function<Eigen::MatrixXf(Eigen::MatrixXf, std::vector<Eigen::MatrixXf>, double)> f,
	Eigen::MatrixXf mx_k,
	Eigen::MatrixXf P_k,
	std::function<Eigen::MatrixXf(Eigen::MatrixXf)>h,
	Eigen::MatrixXf y_kp1,
	Eigen::MatrixXf Q,
	Eigen::MatrixXf R,
	std::vector<Eigen::MatrixXf> args,
	double dt)
{
	double dim_x = mx_k.cols();
	Eigen::MatrixXf mx_kp1 = f(mx_k, args, dt);												// (2.14)
	Eigen::MatrixXf A = numerical_jac_fx(f, mx_k, args, dt);
	Eigen::MatrixXf P_kp1 = (A*P_k)*A.transpose() + Q;										// (2.15)
	Eigen::MatrixXf my_kp1 = h(mx_kp1);
	Eigen::MatrixXf H = numerical_jac_hx(h, mx_kp1);
	Eigen::MatrixXf K = P_kp1 * H.transpose()*(H*P_kp1*H.transpose() + R).inverse();		// (2.16)
	mx_kp1 = mx_kp1 + K * (y_kp1 - my_kp1);													// (2.17)

	Eigen::MatrixXf I_dimx = Eigen::MatrixXf::Identity(dim_x,dim_x);

	//P_kp1 = (K*R)*K.transpose()+ ((I_dimx - (K*H)) * P_kp1) * (I_dimx - (K*H).transpose());		// Barc
	P_kp1 = (I_dimx - K * H)*P_kp1;															// (2.18)
	return std::make_tuple(mx_kp1, P_kp1);
}
