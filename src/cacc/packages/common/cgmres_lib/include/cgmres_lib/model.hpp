#pragma once

#include "Base/TQuaternion.h"

#include <boost/bind.hpp>

#include "vector.hpp"
#include "gmres.hpp"
#include "integrate.hpp"

template<int DIMX, int DIMUC>
class Model{
public:
	static const int DimX = DIMX;
	static const int DimU = DIMUC;

	using x_t = vector_t<DIMX>;		///< Vector for a state vector
    using u_t =  vector_t<DIMUC>;	///< Vector for a control input
	struct xu_t : vector_t<DIMX + DIMUC>{	///< Integrated structure for x and u
	x_t& x(){ return *(x_t*)this; }
	u_t& u(){ return *(u_t*)((double*)this + DIMX); }
	const x_t& x()const{ return *(const x_t*)this; }
	const u_t& u()const{ return *(const u_t*)((const double*)this + DIMX); }
	};

	x_t    x0;		///< Initial state
	u_t    u0;		///< Initial input

	x_t    x;		///< Current state
	x_t    x1;		///< State in next step
	u_t    u;		///< Control input

	/*-------------- dPhi/dx -------------- */
	virtual void phix(double t, const x_t& x, x_t& phx1) = 0;

	/*-------------- State Equation -------------- */
	virtual void xpfunc(double t, const x_t& x, const u_t& u, x_t& xprime) = 0;

	/*-------------- Costate Equation -------------- */
	virtual void lpfunc(double t, const x_t& lmd, const xu_t& linp, x_t& lprime) = 0; 

	/*-------------- Error in Optimality Condition, Hu -------------- */
	virtual void hufunc(double t, const x_t& x, const x_t& lmd, const u_t& u, u_t& hui) = 0;
};

template<class MODEL, int N, int KMAX>
class Controller{
public:
	static const int DimX = MODEL::DimX;	//< Dimension of state vector
	static const int DimU = MODEL::DimU;	//< Dimension of control input
	static const int dv   = N;				//< Number of steps in prediction horizon
	static const int kmax = KMAX;			//< Iteration number of FDGMRES

	using controller_t = Controller<MODEL, N, KMAX>;
	using model_t = MODEL;
    using x_t = typename MODEL::x_t;
    using u_t = typename MODEL::u_t;
    using xu_t = typename MODEL::xu_t;

	/// State sequence
	struct X_t : vector_t<DimX * (N+1)>{	
		template<class T> X_t& operator=(const T& v){ assign(v); return *this; }
		x_t& elem(int i){ return ((x_t*)this)[i]; }
		const x_t& elem(int i)const{ return ((const x_t*)this)[i]; }
	};
	/// Control input sequence
	struct U_t : vector_t<DimU * N>{
		template<class T> U_t& operator=(const T& v){ this->assign(v); return *this; }
		u_t& elem(int i){ return ((u_t*)this)[i]; }
		const u_t& elem(int i)const { return ((const u_t*)this)[i]; }
	};

	double tf;		//< Prediction time
	double ht;		//< Control period
	double alpha;	//< Time constant in case of time-dependent horizon(?)
	double zeta;	//< Feedback gain in Eq.9
	double hdir;	//< h in Eq.11
	double rtol;	//< Tolerance on r for calculating the initial control input
	int    dstep;	//< ?

	double htau;	//< Period in prediction horizon (=tf/dv)
	double onemhdir;	//< 1-hdir
	double hdirbht;		//< hdir/ht
	double onemzetahdir; 	//< 1-zeta*hdir
	double ts;		//< t+hdir
	double tauf;	//< Compensated prediction time in prediction horizon

	x_t x1s;
	x_t	lmd0;
	u_t hu0;
	X_t xtau;
	X_t xtau1;
	X_t ltau;
	U_t duvec;
	U_t utau;
	U_t utau1;
	U_t hutau;
	U_t hutau1;
	U_t hutau2;
	U_t bvec;
	//U_t dutmp;
	U_t utautmp;
	//U_t ptau; //< PrARXモデルのモード出力用　@2018.07.13
	
	vector_t<dv  +1> tau; 
	vector_t<kmax+1> errvec;

	model_t*	model;

public:
	// Constructor
	Controller(){}
	Controller(
               double in_ht,
               double in_zeta,
               double in_hdir,
               double in_tf,
               double in_alpha,
               double in_rtol,
               int in_dstep):
            ht(in_ht), tf(in_tf), alpha(in_alpha),
            zeta(in_zeta), hdir(in_hdir),
            rtol(in_rtol), dstep(in_dstep) {}

	/*-------------- Initial Conditions -------------- */
	/*struct dhu0func{
		void operator()(const u_t& du0, u_t& dhu){
			u_t u;
			u_t hu;

			u = *(u_t*)u0 + hdir * du0;
			hufunc(tsim0, x0, lmd0, u, hu);
			dhu = (hu - hu0) / hdir;
		}
	};*/

	void init(model_t* m){
		model = m;

		onemhdir     = 1 - hdir / ht;
		hdirbht      = hdir / ht;
		onemzetahdir = 1 - zeta * hdir;
	
		int i;
		//double r;
		vector_t<DimU>   b;
		vector_t<DimU>   du0;
		vector_t<DimU+1> erru0;
		model->x = model->x0;
		// phi_x(x, t)
		model->phix(tsim0, model->x0, lmd0);
		// Hu( 
		model->hufunc(tsim0, model->x0, lmd0, model->u0, hu0);
		/*
		du0.clear();
		r = hu0.norm();
		i = 0;

		// 0ステップの最適化問題を解き，最適入力u0を求める
		while( r > rtol && i < 100 ){
			b = -hu0;
			nfgmres<dhu0func, u_t, DIMUC>(b, du0, erru0);
			*(u_t*)u0 += du0;
			hufunc(tsim0, x0, lmd0, u0, hu0);
			r = hu0.norm();
			i++;
		}
		*/
		// 全時刻のuをu0で埋める
		model->u = model->u0;
		for(i=0; i<dv; i++){
			utau .elem(i) = model->u;
			hutau.elem(i) = hu0;
		}
		duvec.clear();
	}


	/*-------------- Control Update -------------- */

	// F(U,x,t)
	void errfunc(double t, const x_t& x, const U_t& u, U_t& hu)
	{
		int i;
		double taut;
		xu_t linp;

		// Time period in prediction horizon
		//tauf = tf * (1.0 - exp(-alpha * t));
		tauf = tf;
		htau = tauf / dv;

		// Fill the initial state with x given
		xtau.elem(0) = x;
	
		// Calculate state sequence by recursive forward difference calculation(Eq.(1)）
		x_t xd;
		//u_t pd;
		for(taut = t, i=0; i < dv; taut += htau, i++){
			model->xpfunc(taut, xtau.elem(i), u.elem(i), xd);
			//model->xpfunc(taut, xtau.elem(i), u.elem(i), xd, pd);
			xtau.elem(i+1) = xtau.elem(i) + htau * xd;
			tau[i] = taut; 
			//ptau.elem(i) = pd;
		}
		tau[i] = taut; 

		// Final condition on the costate lambda（Eq.(7)）
		model->phix(taut, xtau.elem(dv), ltau.elem(dv));

		// Calculate costate sequence by recursive backward difference calculation（Eq.(6)）
		x_t ld;
		for(i = dv-1; i >= 0; i--){
			linp.x() = xtau.elem(i);
			linp.u() = u.elem(i);
			model->lpfunc(taut, ltau.elem(i+1), linp, ld);
			ltau.elem(i) = ltau.elem(i+1) - htau * ld; 
			taut -= htau; 
			// Calculate Hu from predicted x and lambda（Eq.(5)）
			model->hufunc(taut, xtau.elem(i), ltau.elem(i+1), ((U_t&)u).elem(i), hu.elem(i)); 
		}
	}

	void adufunc(const U_t& du, U_t& adu){
		// U + h dU
		utau1 = utau + du * hdir;
		// F(U + hdU, x + h xd, t + h)
		errfunc(ts, x1s, utau1, hutau2);
		// F_U dU approx [F(U + h dU, x + h xd, t + h) - F(U, x + h xd, t + h)] / h
		adu = (hutau2 - hutau1) / hdir;
	}
	struct call_adufunc{
		controller_t* ctrl;
		void operator()(const U_t& du, U_t& adu){
			ctrl->adufunc(du, adu);
		}
		call_adufunc(controller_t* c):ctrl(c){}
	};

	void unew(double t, const x_t& x, const x_t& x1, u_t& u){
		// t + h
		ts = t + hdir;
		
		 //前進差分計算のためにxの時間微分xdが必要だが，実際の計算ではxdを求めないため，ここで差分で近似している
		 //xd = (x1 - x) / dt
		 //x1s = x + h xd = x + (x1 - x) * (h/dt) = (h/dt) x1 + (1 - h/dt) x
		x1s = hdirbht * x1 + x * onemhdir;
		
		// F(t, x, u)
		errfunc(t, x, utau, hutau);

		// F(t + h, x + h xd, u)
		errfunc(ts, x1s, utau, hutau1);
		
		////< x1s = x1 + h xd = x1 + (x1 - x) * (h/dt) = -(h/dt)x + (1 + h/dt)x1 
		//x1s = -hdirbht * x + x1 * onephdir;

		//// F(t, x1, u)
		//errfunc(ts, x1, utau, hutau);

		//// F(t + h, x1 + h xd, u)
		//errfunc(t, x1s, utau, hutau1);

		// b on Eq.(11)
		// b = As F(U,x,t) - DhF(U,x,t:0,xd,1),
		// From DhF(U,x,t:0,xd,1) = (F(U, x + h xd, t+h) - F(U,x,t))/h,
		// b = [(1 + h As) F(U,x,t) - F(U, x + h xd, t+h)] / h
		bvec = (hutau * onemzetahdir - hutau1) / hdir;

		// Solve F_U Ud = b by GMRES
		// adufunc is a function that gives A*dU while A is F_U here.
		nfgmres<call_adufunc, U_t, kmax>(call_adufunc(this), bvec, duvec, errvec);
		
		// U += dU * ht;
		utau += ht * duvec;

		// Limit the control inputs with upper and lower bound
		for(int i = 0; i < N; i++)for(int j = 0; j < model->NCar; j++){
			if(utau.elem(i)[j] > model->umax){
					utau.elem(i)[j] = model->umax;
			}
			else if(utau.elem(i)[j] < model->umin){
					utau.elem(i)[j] = model->umin;
			}
			duvec = (utau - utautmp)/ht;
		}
		errfunc(t,x1,utau,hutau1);
		
		//double lim = 1000;
		//if(abs(hutau1.norm()) > lim){
		//for(int i = 0; i < N; i++)for(int j = 0; j < modeltmp.NCar; j++){
		//	if(xtau.elem(i)[3*j+0] <= modeltmp.Dmin+0.1){
		//		utau.elem(i)[j] *= utau.elem(i)[j]>0?0.1:1.5;
		//		//if(utau.elem(i)[j] < modeltmp.umin[j]) utau.elem(i)[j] = modeltmp.umin[j];
		//		//utau.elem(i)[j] = modeltmp.umin[j];
		//	}
		//	if(xtau.elem(i)[3*j+0] >= modeltmp.Dmin && abs(utau.elem(i)[2*modeltmp.NCar + j])>lim){
		//		utau.elem(i)[1*modeltmp.NCar+j] = sqrt(xtau.elem(i)[3*j+0]-modeltmp.Dmin);	
		//		utau.elem(i)[2*modeltmp.NCar+j] = modeltmp.s1[j]/(2*modeltmp.sc[j]*utau.elem(i)[1*modeltmp.NCar+j]);
		//	}
		//}
		//duvec = (utau - utautmp)/ht;
		//errfunc(t,x1,utau,hutau1);
		//}

		//// もし更新したutauでのhutauが更新前より悪化した場合は戻す
		//if(hutau1.norm() > hutau.norm()){
		//	utau = utautmp;
		//	duvec = (utau-utautmp)/ht;
		//	errfunc(t,x1,utau,hutau1);
		//}

		// Apply the first elements of U as actual input u
		u = utau.elem(0);
		utautmp = utau;
		//dutmp = duvec;
	}

	private:
        const double tsim0 = 0.0;
};
