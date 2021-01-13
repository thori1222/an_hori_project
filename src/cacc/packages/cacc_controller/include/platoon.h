#ifndef PLATOON_H_
#define PLATOON_H_
#pragma once

#include <math.h>
#include <float.h>
#include <cgmres_lib/model.hpp>
#include <packetHandler.h>
#include <predictionModel.h>

template<int NCAR, class DRIVERMODEL>
class Platoon : public Model<3*(2*NCAR-1), 1*(2*NCAR-1)>{
public:
	using model_t = Model<3*(2*NCAR-1), 1*(2*NCAR-1)>;
	using driver_t = DRIVERMODEL;

	static const int NCar = (2*NCAR-1);
	bool    manual[(2*NCAR-1)]; // true  => manual car   x[0]=range x[1]=velocity x[2]=model output
	                      // false => auto   car   x[0]=range x[1]=velocity                   u[0]=control input
	int		refmode;
	double  cal_lim;

	driver_t*	driver_model[NCAR-1];

	bool	activated[NCAR-1]; // true => real manual car
								// false => ghost manual car
	
	float  	a;		    // Acceleration of the leading car
	float	v;			// Velocity of the leading car

	float	Ds;			// Standstill reference distance
	float  	Dmin;		// Minimum distance for distance constraints
	float  	thw[(2*NCAR-1)];	// Time headway for the reference distance
	float   alpha[(2*NCAR-1)];	// parameter on vehicle model based on 1st order system (G(s) = beta/(s+alpha), a(t+1) = (1/dt - alpha)*a(t) + beta*dt*u(t))
	float	beta[(2*NCAR-1)];	// parameter on vehicle model based on 1st order system (a(t+1) = (1/dt - 1/tau)*a(t) + dt*tau*K*u(t), a_dot(t) = -1/tau*a(t) + tau*K*u(t) ,tau = 1/alpha, K = beta/alpha)
	float  	umax;		// Maximum of control input
	float	umin;		// Minimum of control input

	int		sf    [(2*NCAR-1)*3];	// Coefficient matrix on final cost
	int		q     [(2*NCAR-1)*3]; // Coefficient matrix on process cost
	int		r     [(2*NCAR-1)];	// Coefficient matrix on control input
	int		su	  [(2*NCAR-1)];   // Coefficient on constraint of control input
	int		sd	  [(2*NCAR-1)];	// Coefficient on constraint of distance

	Platoon(){
		init();
	}
	Platoon(driver_t* const in_base_model){
		init();
		for(int i = 0; i < NCAR-1; i++){
			driver_model[i] = &in_base_model[i];
		}
	}

	void init(){
		refmode = 1;
		cal_lim = pow(10.0, 50.0);
		
		a         = 0.0;
		v		  = 0.0;

		MpcParameter param;

		Ds        = param.Ds;
		Dmin	  = param.Dmin;
		umax	  = param.umax;
		umin	  = param.umin;
	
		for(int i = 0; i < NCar; i++){
			if(i%2 == 1){ //manual
				thw[i]        = 0.0;
				sf[3 * i + 0] = 0;
				sf[3 * i + 1] = 0;
				sf[3 * i + 2] = 0;
				q[3*i+0]      = 0;
				q[3*i+1]      = 0;
				q[3*i+2]      = 0;
				r[i] 		  = 0;
				su[i]		  = 0;
				sd[i]		  = 0;
				manual[i]	  = true;
				activated[(int)((i-1)/2)] = false;
				delete driver_model[(int)((i-1)/2)];
				driver_model[(int)((i-1)/2)] = NULL;

				this->x0[3*i+0] = Ds;
				this->x0[3*i+1] = 0.0;
				this->x0[3*i+2] = 0.0;
				this->u0[i] = 0.0;
			}
			else{
				thw[i]        = 1.0;
				sf[3 * i + 0] = param.sf*param.q[0];
				sf[3 * i + 1] = param.sf*param.q[1];
				sf[3 * i + 2] = param.sf*param.q[2];
				q[3*i+0]      = param.q[0];
				q[3*i+1]      = param.q[1];
				q[3*i+2]      = param.q[2];
				r[i] 		  = param.r;
				su[i]		  = param.su;
				sd[i]		  = param.sd;
				manual[i]	  = false;

				this->x0[3*i + 0] =  Ds;
				this->x0[3*i + 1] =  0.0;
				this->x0[3*i + 2] =  0.0;
				this->u0[i]       =  0.000001;
			}
			alpha[i] = 10.0;
			beta[i] = 10.0;
		}

		this->x = this->x0;
		this->x1 = this->x0;
	}

	void set_param(const MpcParameter& _param){
		Ds 		= _param.Ds;
		Dmin 	= _param.Dmin;

		umax	= _param.umax;
		umin	= _param.umin;

		for(int ic = 0; ic < NCar; ic++){
			if(!manual[ic]){
				sf[3*ic+0] = _param.sf*_param.q[0];
				sf[3*ic+1] = _param.sf*_param.q[1];
				sf[3*ic+2] = _param.sf*_param.q[2];
				q[3*ic+0]  = _param.q[0];
				q[3*ic+1]  = _param.q[1];
				q[3*ic+2]  = _param.q[2];
				r[ic] 	   = _param.r;
				su[ic]     = _param.su;
				sd[ic]     = _param.sd;
			}
		}
	}


	/*-------------- dPhi/dx -------------- */
	// Partial derivative of the final cost term with respect to the state x
	// (x1: range、x2: velocity、x3: acceleration of manual car)
	void phix(double t, const typename model_t::x_t& x, typename model_t::x_t& phx1)
	{
		for(int i = 0; i < NCar; i++){
			if(manual[i]&&!activated[(int)((i-1)/2)]){
				phx1[3*i+0] = 0;
				phx1[3*i+1] = 0;
				phx1[3*i+2] = 0;
			}
			else{
				phx1[3*i+0] = sf[3*i+0] * (x[3*i+0] - (Ds + thw[i]*x[3*i+1]));	//< Partial derivative in range
				phx1[3*i+1] = phx1[3*i+0] * (-thw[i]) + sf[3*i+1]*(x[3*i+1]-(i==0 ? v : (refmode==0?v:x[3*(i-1)+1]))) - (refmode==0?0:sf[3*(i+1)+1]*(i == NCar-1 ? 0 : x[3*(i+1)+1]-x[3*i+1]));			//< Partial derivative in velocity
				phx1[3*i+2] = sf[3*i+2] * (x[3*i+2] - (i==0 ? 0 : (refmode==0 ? 0 : x[3*(i-1)+2]))) + refmode==0 ? 0 : (i==NCar-1 ? 0 : -sf[3*(i+1)+1]*(x[3*(i+1)+2]-x[3*i+2]));	//< Partial derivative in driver model output
			}
		}
		
	}

	/*-------------- State Equation -------------- */
	//void xpfunc(double t, const x_t& x, const u_t& u, x_t& xprime)
	void xpfunc(double t, const typename model_t::x_t& x, const typename model_t::u_t& u, typename model_t::x_t& xprime)
	{
		for(int i = 0; i < NCar; i++){
			// manual car
			if(manual[i]){
				if(activated[(int)((i-1)/2)]){
					// Time derivative of range = relative velocity
					xprime[3*i+0] = x[3*(i-1)+1] - x[3*i+1];
					// Time derivative of velocity = accleration
					xprime[3*i+1] = x[3*i+2];
					// Time derivative of driver model 
					double dt;
					driver_model[(int)((i-1)/2)]->cal_dt(x, &dt);
					xprime[3*i+2] = dt;
				}
				else{
					xprime[3*i+0] = x[3*(i-1)+1] - x[3*i+1];
					xprime[3*i+1] = x[3*i+2];
					//xprime[3*i+0] = 0;
					//xprime[3*i+1] = x[3*(i-1)+2];
					xprime[3*i+2] = -alpha[i-1]*x[3*i+2]+beta[i-1]*u[i-1];
					//xprime[3*i+2] = alpha[i-1]*x[3*(i-1)+2]-beta[i-1]*u[i-1];
				}
			}
			// auto car
			else{
				xprime[3*i+0] = (i==0 ? v : x[3*(i-1)+1]) - x[3*i+1];
				xprime[3*i+1] = x[3*i+2];
				//xprime[3*i+2] = beta[i]*(x[3*i+2]-u[i]);
				xprime[3*i+2] = -alpha[i]*x[3*i+2]+beta[i]*u[i];
				//xprime[3*i+2] = alpha[i]*x[3*i+2]-beta[i]*u[i];	
			}
		}
	}

	/*-------------- Costate Equation -------------- */
	//void lpfunc(double t, const x_t& lmd, const xu_t& linp, x_t& lprime){
	void lpfunc(double t, const typename model_t::x_t& lmd, const typename model_t::xu_t& linp, typename model_t::x_t& lprime)
	{
		typename model_t::x_t    _x;
		typename model_t::u_t    _u;
 
		_x = linp.x();
		_u = linp.u();
		
		// ==============================================
		std::cout << " " << lmd.size(); // ｺﾚｦｶｸﾄﾅｾﾞｶｳｺﾞｸ
		// ===============================================
		
		// -H_x
		for(int i = 0; i < NCar; i++){
			// manual
			if(manual[i]){
				int j = (int)((i-1)/2);
				if(activated[j]){
					lprime[3*i+0] = -(q[3*i+0]*(_x[3*i+0]-(Ds+thw[i]*_x[3*i+1])));
					lprime[3*i+1] = -(q[3*i+0]*(_x[3*i+0]-(Ds+thw[i]*_x[3*i+1]))*(-thw[i]) 
										+q[3*i+1]*(_x[3*i+1]-(i==0 ? v : (refmode==0?v:_x[3*(i-1)+1]))) 
										+(refmode==0?0:q[3*(i+1)+1]*(_x[3*i+1]-_x[3*(i+1)+1])));
					lprime[3*i+1]+= -(-lmd[3*i+0] + lmd[3*(i+1)+0]);
						
				
					////lprime[3*i+0] += -(sd[i] * -10*exp(-10*(_x[3*i+0]-Dmin))); //車間距離の制約
					//double tmp;
					//try{
					//	tmp = -(sd[i] * -10*exp(-10*(_x[3*i+0]-Dmin)));
					//	if(tmp>cal_lim || tmp<-cal_lim)
					//		throw((tmp>0?1:-1)*cal_lim);
					//}
					//catch(double _tmp){
					//	tmp = _tmp;
					//}
					//lprime[3*i+0] += tmp;

					
					lprime[3*i+2] = -(q[3*i+2]*(_x[3*i+2]-(i==0?0:refmode==0?0:_x[3*(i-1)+2])) + (refmode==0?0:q[3*(i+1)+2]*(_x[3*i+2]-_x[3*(i+1)+2])));
					lprime[3*i+2]+= -(lmd[3*i+1]);

					typename model_t::x_t    M; //df3/dx
					driver_model[(int)((i-1)/2)]->cal_dfdx(_x, &M);
					lprime += -lmd[3*i+2]*M;
				}
				else{
					lprime[3*i+0] = 0;
					lprime[3*i+1] = -(-lmd[3*i+0] + lmd[3*(i+1)+0]); //->lambda*f?
					lprime[3*i+2] = -(lmd[3*i+1] + lmd[3*i+2]*(-alpha[i-1]));				
				}
			}
			// auto
			else{
				lprime[3*i+0] = -(q[3*i+0]*(_x[3*i+0]-(Ds+thw[i]*_x[3*i+1])));
				lprime[3*i+1] = -(q[3*i+0]*(_x[3*i+0]-(Ds+thw[i]*_x[3*i+1]))*(-thw[i]) 
									+q[3*i+1]*(_x[3*i+1]-(i==0 ? v : (refmode==0?v:_x[3*(i-1)+1]))) 
									+(refmode==0?0:q[3*(i+1)+1]*(i==NCar-1?0:_x[3*i+1] - _x[3*(i+1)+1])));
				lprime[3*i+1]+= -(-lmd[3*i+0] + (i==NCar-1?0:lmd[3*(i+1)+0]));

				double tmp = 0;
				int gain = 10;
				if (_x[3 * i + 0] < Dmin + 2.0) {
						try {
						tmp = -(sd[i] * -gain * exp(-gain * (_x[3 * i + 0] - Dmin))); //Exponential function
						//tmp = -(sd[i] * (_x[3*i+0]<Dmin?-gain:0)); //Piece-wise linear function
						//tmp = -(sd[i] * (_x[3*i+0]<Dmin?4*(_x[3*i+0]-Dmin)*(_x[3*i+0]-Dmin)*(_x[3*i+0]-Dmin):0)); //4th polynomial function

						if (tmp > cal_lim || tmp < -cal_lim)
							throw((tmp > 0 ? 1 : -1)*cal_lim);
					}
					catch (double _tmp) {
						tmp = _tmp;
					}
					lprime[3 * i + 0] += tmp;
				}
				lprime[3*i+2] = -(q[3*i+2]*(_x[3*i+2]-(i==0?0:refmode==0?0:_x[3*(i-1)+2]))
								 +(refmode==0?0:q[3*(i+1)+2]*(i==NCar-1?0:_x[3*i+2]-_x[3*(i+1)+2])));
				//lprime[3*i+2]+= -(lmd[3*i+1] + lmd[3*i+2]*(beta[i]) + (i==NCar-1?0:(activated[(int)(i/2)]?0:lmd[3*(i+1)+2]*(beta[i]))));
				lprime[3*i+2]+= -(lmd[3*i+1] + lmd[3*i+2]*(-alpha[i]));
			}
		}
	}

	/*-------------- Error in Optimality Condition, Hu -------------- */
	//void hufunc(double t, const x_t& x, const x_t& lmd, const u_t& u, u_t& hui){
	void hufunc(double t,
            const typename model_t::x_t& x,
            const typename model_t::x_t& lmd,
            const typename model_t::u_t& u,
            typename model_t::u_t& hui)
	{
		for(int i = 0; i < NCar; i++){
			if(manual[i]){
				// none
				hui[i] = 0.0;
			}
			else{
				//hui[i] = r[i]*u[i] + lmd[3*i+2]*(-beta[i]);
				hui[i] = r[i]*u[i] + lmd[3*i+2]*(beta[i]);
				if(i < NCar-1 && !activated[(int)(i/2)])
					//hui[i] += lmd[3*(i+1)+2]*(-beta[i]);
					hui[i] += lmd[3*(i+1)+2]*(beta[i]); 

				double tmp = 0;
				int gain = 10;
				try{
					tmp = su[i]*(gain*exp(gain*(u[i]-umax))-gain*exp(-gain*(u[i]-umin))); //Exponential function
					//tmp = su[i]*(u[i]>umax?gain:(u[i]<-umax?-gain:0)); //Piece-wise linear function
					//tmp = su[i]*4*u[i]*u[i]*u[i]*gain; //4th polynomial function
					//tmp = su[i]*(u[i]>umax?4*u[i]*u[i]*u[i]:(u[i]>0?gain:(u[i]>-umax?-gain:4*u[i]*u[i]*u[i]))); //Conditional polynimial function
					if(tmp>cal_lim || tmp<-cal_lim)
						throw((tmp>0?1:-1)*cal_lim);
				}
				catch(double _tmp){
					tmp = _tmp;
				}
				hui[i] += tmp;
			}
		}
	}

	void set_activation(int i, driver_t* _model){
		//int j = (int)((i-1)/2);
		int j = i;
		if(j >= NCar-1){
			std::cout<<"Input index is bigger than its limitation."<<std::endl;
			j = NCar-2;
		}
		activated[j] = true;
		driver_model[j] = _model;
		if(driver_model[j]->getIdx() != (2*j+1)){
			std::cout<<"!!!!!!ERROR!!!!!! Index of the manual car doesn't match!!!!!"<<std::endl;
		}

		int k = 2*i+1;
		this->x[3*k+0] = Ds + thw[k-1]*this->x[3*(k-1)+1];
		this->x[3*k+1] = this->x[3*(k-1)+1];
		this->x[3*k+2] = 0;
	}

	void set_deactivation(int i){
		//int j = (int)((i-1)/2);
		int j = i;
		if(j >= NCar-1){
			std::cout<<"Input index is bigger than its limitation."<<std::endl;
			j = NCar-2;
		}

		activated[j] = false;
		delete driver_model[j];
		driver_model[j] = NULL;

		int k = 2*i+1;
		this->x[3*k+0] = 0;
		this->x[3*k+1] = this->x[3*(k-1)+1];
		this->x[3*k+2] = this->x[3*(k-1)+2];
	}
};

template<int NCAR, class DRIVERMODEL>
class PlatoonController : public Controller< Platoon<NCAR, DRIVERMODEL>, 200, 10>{
public:
	PlatoonController(){
		this->tf     = 2.0;
		this->ht     = 0.01;
		this->alpha  = 1.5;
		this->zeta   = 100;
		this->hdir   = 1.e-8;//0.002;
		this->rtol   = 1.e-6;
		this->dstep  = 1;
	}
};

#endif