#pragma once

#define _USE_MATH_DEFINES

#include <SimpleCSVLoader.h>
#include <cmath>
#include <limits>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>

#include <Eigen/Core>


/// Frenet coodinate class
/// This load the point list from csv file 
/// and convert the coodinate from Global to Frenet, 
/// and from Frenet to Global.
//***************************************************
// Create instance
// 
// // create instance from file (loop course)
// FrenetCoordinate2D frenet;
// frenet.LoadPathFromCSV("file.csv", true);
// 
// // create instance from file (non-loop course)
// FrenetCoordinate2D frenet("file.csv", false);
// 
// // create instance from csv loader
// SimpleCSVLoader csv("file.csv");
// FrenetCoordinate2D( csv, true );
//
//***************************************************
// 
// resampling. 
// interpolate long gap points
//
// // resample with euality gap
// FrenetCoordinate2D resampled = frenet.Resample(1);
//
// // resample with smart interpolation  
// // keeping points, but, 
// // interpolate the longer gap than threashold
// FrenetCoordinate2D resampled = frenet.ResampleConservative(1);
//
//
//***************************************************
// CSV file format 
// tags must be written on 1st line.
// data must be written from second line.
// data row is:
// x, y, x, nx, ny, nx, 
// where the position of the points(x,y,z) 
// and up-vector which indicates the direction of top
// (normal of ground surface).
// 
// since this FrenetCoordinate2D can handle 2D Frenet coordinate,
// (x, y, x, nx, ny, nx) => (x, y, 0, 0, 0, 1) is assumed.
// only (x,y) are used and considered.
//
//***************************************************
// how to convert coodinates
// Note that the cache have to be used properly 
// to obtain collect result.
//
//	// define cache for fast computation
//  CacheToGlobal cacheG;
//  CacheToFrenet cacheF;
//
//	// convert Frenet coordinate(u,v) to glocal position(x,y)
//  double u = ...; 
//	double v = ...;
//	double x, y;
//	cacheG = frenet.GetGlobal(u, v, x, y, &cacheG);
//
//	// convert Global coordinate(x,y) to Frenet position(u,v)
//	double re_u;
//	double re_v;
//	cacheF = frenet.GetFrenet(x, y, re_u, re_v, &cacheF);
//

namespace RTCLib {

	struct FrenetPoint2D
	{
		typedef Eigen::Vector2d Vector;
		// global position
		Vector pos;

		FrenetPoint2D* next;
		FrenetPoint2D* prev;

		// u 
		double du;	// distance to next
		double u;	// distance from start along path

		// vector to next
		Vector to_next;
		double to_next_theta;

		// normal vector to next
		Vector t_to_next;
		Vector n_to_next;


		// tangent vector
		Vector t;
		double t_theta;

		// normal vector
		Vector n;
		double n_theta;

		// curvature
		double kappa;


		FrenetPoint2D() : to_next(0,0), t_to_next(0, 0), n_to_next(0, 0),
			t(0, 0), n(0, 0)
		{
			prev = nullptr;
			next = nullptr;
			u = 0; du = std::numeric_limits<double>::infinity();
			to_next_theta = 0;

			t_theta = 0;
			n_theta = 0;
			kappa = 0;
			
		}

		void CalculateU(FrenetPoint2D &_prev)
		{
			//double dx = pos.x - prev.pos.x;
			//double dy = pos.y - prev.pos.y;
			//du = std::sqrt(dx * dx + dy * dy);
			_prev.du = (pos - _prev.pos).norm();
			u = _prev.u + _prev.du;
			prev = &_prev;
		}

		//inline void normalize(double &x, double &y)
		//{
		//	this->normalize();
		//	double l = std::sqrt(x * x + y * y);
		//	x = x / l;
		//	y = y / l;
		//}

		void ConnectToNext(FrenetPoint2D &_next)
		{
			next = &_next;
			to_next = _next.pos - pos;
			t_to_next = to_next.normalized();
			n_to_next.x() = -t_to_next.y();
			n_to_next.y() = t_to_next.x();
			to_next_theta = atan2(t_to_next.y(), t_to_next.x());

			// This is NOT tangent,,,
			//t = (next->pos - prev->pos).normalized();
			//t_theta = std::atan2(t.y(), t.x());

			//n.x() = -t.y();
			//n.y() = t.x();
			//n_theta = atan2(n.y(), n.x());

			// Compute tangent
			if (prev != nullptr)
			{
				double angle_diff = to_next_theta - prev->to_next_theta;
				if (angle_diff > M_PI) angle_diff -= 2 * M_PI;
				if (angle_diff < -M_PI) angle_diff += 2 * M_PI;
				prev->kappa = angle_diff * 2 / (prev->du + du);
			}
		}

		// Compute curvature Kappa from (*_from) until (*_to)
		void ComputeKappa(FrenetPoint2D *_from, FrenetPoint2D *_to)
		{
			double len = 0;
			FrenetPoint2D* cur = _from;
			while ( cur != nullptr && cur != _to)
			{
				len += cur->du;
				cur = cur->next;
			}
			double angle_diff = _to->to_next_theta - _from->to_next_theta;
			if (angle_diff > M_PI) angle_diff -= 2 * M_PI;
			if (angle_diff < -M_PI) angle_diff += 2 * M_PI;
			kappa = angle_diff * 2 / (len);
		}

		void OutputLaneTagsForDebug(std::ofstream &ofs)
		{
			ofs << "x, y, du, u,"
				<< "e_to_next_x, e_to_next_y, to_next_theta,";

			ofs << "tx, ty, t_theta,";
			ofs << "nx, ny, n_theta,";
			ofs << "kappa" << std::endl;
		}

		void OutputLaneForDebug(std::ofstream& ofs)
		{
			ofs << pos.x() << "," << pos.y() << ","
				<< du << "," << u << ","
				<< t_to_next.x() << "," << t_to_next.y() << ","
				<< to_next_theta << ",";

			ofs << t.x() << "," << t.y() << "," << t_theta << ",";
			ofs << n.x() << "," << n.y() << "," << n_theta << ",";
			ofs << kappa << "," << std::endl;
		}

		inline Vector GetLocalPos(Vector target) const
		{
			Vector diff = target - pos;
			double u = t_to_next.x() * diff.x()
				+ t_to_next.y() * diff.y();
			double v = n_to_next.x() * diff.x()
				+ n_to_next.y() * diff.y();
			return Vector(u, v);
		}
	};

	struct CacheToGlobal {
		bool initialized;
		size_t prev_index;
		int lap;
		CacheToGlobal()
			: prev_index(0),lap(0), initialized(0) {};
		CacheToGlobal(size_t val)
			: prev_index(val),lap(0), initialized(0) {};
	};

	struct CacheToFrenet {
		bool initialized;
		size_t prev_index;
		int lap;
		CacheToFrenet()
			: prev_index(0),lap(0), initialized(0){};
		CacheToFrenet(size_t val)
			: prev_index(val),lap(0), initialized(0){};
	};

	class FrenetCoordinate2D
	{
		//const double pi = 3.141592653579793238;
		typedef Eigen::Vector2d Vector2;
	public:

		bool isLooping = false;
		SimpleCSVLoader csvLoader;

		std::vector< FrenetPoint2D> points;
		std::vector<double> u_cache;
		std::vector<size_t> anchors;

		double length;
		size_t size;

		// ---------------------- constructors
		FrenetCoordinate2D()
		{
		}

		FrenetCoordinate2D(std::string fn, bool bLoop)
		{
			LoadPathFromCSV(fn, bLoop);
		}
		FrenetCoordinate2D(const SimpleCSVLoader& csv, bool bLoop)
		{
			LoadPathFromCSV(csv, bLoop);
		}

		// ----------------------- load from csv
		void LoadPathFromCSV(std::string fn, bool bLoop)
		{
			csvLoader.LoadPathFromCSV(fn);
			LoadPathFromCSV(csvLoader, bLoop);
		}
		void LoadPathFromCSV(const SimpleCSVLoader& csv, bool bLoop)
		{
			isLooping = bLoop;

			setXY(csv);
			compute_aux();
		}

		// ----------------------- load from positions array
		void LoadPath(const std::vector<double> &x, const std::vector<double> &y, bool bLoop)
		{
			isLooping = bLoop;
			//if (sizeof(x) != sizeof(y))throw std::exception("Array size is not matched for X and Y");
			if (sizeof(x) != sizeof(y))throw std::runtime_error("Array size is not matched for X and Y");
			size_t N = x.size();
			points.resize(N);

			for (size_t i = 0; i < N; i++)
			{
				points[i].pos.x() = x[i];
				points[i].pos.y() = y[i];
			}
			size = N;
			compute_aux();
		}

		// resample path with delta_u;
		FrenetCoordinate2D Resample(double delta_u)
		{
			FrenetCoordinate2D ret;
			std::vector<double> x;
			std::vector<double> y;
			CacheToGlobal cache;
			size_t estimated_size = std::ceil(length / delta_u);
			x.reserve(estimated_size);
			y.reserve(estimated_size);

			double u;
			for (u = 0; u < length; u+=delta_u)
			{
				double tmpx, tmpy;
				cache = GetGlobal(u, 0, tmpx, tmpy, cache);
				x.push_back(tmpx);
				y.push_back(tmpy);
			}
			if (u != length)
			{
				u = length;
				double tmpx, tmpy;
				cache = GetGlobal(u, 0, tmpx, tmpy, cache);
				x.push_back(tmpx);
				y.push_back(tmpy);
			}
			ret.LoadPath(x, y, isLooping);

			return ret;
		}

		// resample path with keeping anchor points
		FrenetCoordinate2D ResampleConservative(double threashold)
		{
			FrenetCoordinate2D ret;
			std::vector<double> x;
			std::vector<double> y;
			CacheToGlobal cache;
			// so rough guess
			size_t estimated_size = std::ceil(length / threashold);
			x.reserve(estimated_size);
			y.reserve(estimated_size);

			double u;
			for (size_t i = 0; i < size; i++)
			{
				// add current point
				x.push_back(points[i].pos.x());
				y.push_back(points[i].pos.y());

				if (i == size - 1 && isLooping == false)
					break;

				// check the interpolation is needed
				size_t div = std::ceil(points[i].du / threashold) - 1;
				if (div < 1)continue;
				for (size_t j = 0; j < div; j++)
				{	// do interpolation
					u = points[i].u + (j+1) * points[i].du / (div + 1);
					double tmpx, tmpy;
					cache = GetGlobal(u, 0, tmpx, tmpy, cache);
					x.push_back(tmpx);
					y.push_back(tmpy);
				}
			}
			ret.LoadPath(x, y, isLooping);
			return ret;

		}

		// ---------------------------------  coordinate conversion
		// get global position from Frenet coordinate
		CacheToGlobal GetGlobal(double u, double v,
			double &x, double &y, CacheToGlobal prev)
		{
			CacheToGlobal cache = search_u(u, prev);
			size_t index = cache.prev_index;

			u = normalize_u(u, cache.lap);
			double diffu = u - points[index].u;
			double diffv = v;
			//if (u > 2400)
			//{
			//	printf("");
			//}

			Eigen::Vector2d gpos =
				points[index].pos
				+ points[index].t_to_next * diffu
				+ points[index].n_to_next * diffv;

			x = gpos.x();
			y = gpos.y();

			return cache;
		}

		// get global position from Frenet coordinate together with yaw angle
		CacheToGlobal GetGlobal(double u, double v, double theta_e,
			double &x, double &y, double& yaw, CacheToGlobal prev)
		{
			CacheToGlobal cache = GetGlobal(u, v, x, y, prev);
			size_t index = cache.prev_index;

			yaw = points[index].to_next_theta + theta_e;
			if (theta_e > M_PI) theta_e -= 2 * M_PI;
			if (theta_e < -M_PI) theta_e += 2 * M_PI;

			return cache;
		}

		// get Frenet position from global position with yaw difference 
		CacheToFrenet GetFrenet(double x, double y, double yaw,
			double &u, double &v, double &theta_e, CacheToFrenet prev) const
		{
			CacheToFrenet cache = GetFrenet(x, y, u, v, prev);
			size_t index = cache.prev_index;
			theta_e = yaw - points[index].to_next_theta;

			double y_x = cos(yaw);
			double y_y = sin(yaw);
			const Eigen::Vector2d &t = points[index].t_to_next;
			double t_x = t.x();
			double t_y = t.y();
			// get angle by outer prod
			double angle_diff_sin = y_y * t_x - y_x * t_y;
			double angle_diff = asin(angle_diff_sin);

			//if (theta_e > M_PI) 
			//	theta_e -= 2 * M_PI;
			//if (theta_e < -M_PI) 
			//	theta_e += 2 * M_PI;

			theta_e = angle_diff;

			return cache;
		}

		// get Frenet position from global position
		CacheToFrenet GetFrenet(double x, double y,
			double &u, double &v, CacheToFrenet cache) const
		{
			// check whether positive or negative side of prev index
			int index;
			if (cache.initialized)
			{
				index = cache.prev_index;
			}
			else {
				index = find_basepoint(x, y);
			}
			
			// Get local position from base point
			Eigen::Vector2d target(x, y);
			Eigen::Vector2d uv = points[index].GetLocalPos(target);

			// backward search
			while (uv.x() < 0)
			{	// compute inner dot with tangent
				if (isLooping)
				{
					index = index - 1;
					if(index < 0) index = size - 1;
				}
				else
					index = index > 0 ? index-- : 0;

				uv = points[index].GetLocalPos(target);
			}
			// forward search
			// if local u > 0 from next point, go next
			while (uv.x() > 0)
			{
				if (uv.x() <= points[index].du) break;
				// vector from base point to current point
				size_t next = index;
				if (isLooping)
					next = (index + 1) % size;
				else
					next = (index + 1) > (size - 1) ? (size - 1) : index + 1;

				Eigen::Vector2d uv_from_next
					= points[next].GetLocalPos(target);

				if (uv.x() > 0 && uv_from_next.x() < 0)
				{
					break;
				}
				index = next;
				uv = uv_from_next;
			}
			u = uv.x() + points[index].u;
			v = uv.y();
			CacheToFrenet ret;
			ret.prev_index = index;
			ret.lap = cache.lap;
			ret.initialized = true;
			return ret;
		}

		/// return point cached last time
		FrenetPoint2D GetPoint(const CacheToFrenet &cache)
		{
			return points[cache.prev_index];
		}

		/// return point cached last time
		FrenetPoint2D GetPoint(const CacheToGlobal &cache)
		{
			return points[cache.prev_index];
		}

		/// return point cached last time
		FrenetPoint2D GetPoint(double u, const CacheToGlobal* cache)
		{
			CacheToGlobal _cache;
			if (cache != nullptr) _cache = *cache;
			_cache = search_u(u, _cache);
			return points[_cache.prev_index];
		}

		/// return interpolated info
		FrenetPoint2D GetPointLinp(double u, const CacheToGlobal* cache)
		{
			CacheToGlobal _cache;
			if (cache != nullptr) _cache = *cache;
			_cache = search_u(u, _cache);
			FrenetPoint2D prev = points[_cache.prev_index];

			if (points[_cache.prev_index].next == nullptr)
			{
				return points[_cache.prev_index];
			}
			FrenetPoint2D next = *points[_cache.prev_index].next;
			FrenetPoint2D ret = prev;
			double du = u - prev.u;
			ret.kappa = lin_p(prev.u, next.u, prev.kappa, next.kappa, u);
			ret.n_theta = lin_p(prev.u, next.u, prev.n_theta, next.n_theta, u);
			ret.t_theta = lin_p(prev.u, next.u, prev.t_theta, next.t_theta, u);
			ret.to_next_theta = lin_p(prev.u, next.u, prev.to_next_theta, next.to_next_theta, u);

			get_anglevec(ret.n_theta, ret.n);
			get_anglevec(ret.t_theta, ret.t);
			get_anglevec(ret.to_next_theta, ret.to_next);

			return ret;
		}

		void WritePath(std::ofstream ofs)
		{
			ofs << "x, y, z, nx, ny, nz, " << std::endl;
			for (size_t i = 0; i < size; i++)
			{
				ofs << points[i].pos.x() << ", "
					<< points[i].pos.y() << ", 0, "
					<< "0, 0, 1, " << std::endl;
			}
		}

		// just for debugging
		void OutputLaneForDebug(std::string testfn)
		{
			std::ofstream ofs(testfn);
			points[0].OutputLaneTagsForDebug(ofs);

			for (size_t i = 0; i < size; i++)
			{
				points[i].OutputLaneForDebug(ofs);
			}

		}


	private:
		inline void setXY(SimpleCSVLoader csv)
		{
			points.resize(csv.data.size());
			for (size_t i = 0; i < csv.data.size(); i++)
			{
				points[i].pos.x() = csv.data[i][0];
				points[i].pos.y() = csv.data[i][1];
			}
			size = points.size();
		}

		void compute_aux()
		{
			computeU();
			connect();
			make_anchors();
			compute_kappa();
		}

		// this must be called after SetXY
		inline void computeU()
		{
			u_cache.resize(points.size());
			points[0].u = 0;
			points[0].du = 0;
			u_cache[0] = 0;
			for (size_t i = 1; i < points.size(); i++)
			{
				points[i].CalculateU(points[i - 1]);
				u_cache[i] = points[i].u;
			}
			if (isLooping)
			{	// connect last point to first
				points[0].CalculateU(points[size - 1]);
				points[0].u = 0;
			}
			else {
				points[size - 1].du = 10e10;
			}
			// if loop course, add line length from last point to start point
			if (isLooping)
				length = points.back().u + points.back().du;
			else
				length = points.back().u;
		}

		inline void connect()
		{
			for (size_t i = 0; i < points.size() - 1; i++)
			{
				points[i].ConnectToNext(points[i + 1]);
			}
			if (isLooping)
			{	// connect last point to first
				points[size - 1].ConnectToNext(points[0]);
			}
			else {
				FrenetPoint2D &last = points[size-1];
				last.next = nullptr;
				last.to_next = points[size - 2].to_next;
				last.t_to_next = points[size - 2].t_to_next;
				last.n_to_next = points[size - 2].n_to_next;
				last.to_next_theta = points[size - 2].to_next_theta;
				last.t = points[size - 2].t;
				last.t_theta = points[size - 2].t_theta;
				last.n = points[size - 2].n;
				last.n_theta = points[size - 2].n_theta;
				last.kappa = points[size - 2].kappa;
				points[0].kappa = points[1].kappa;
			}
		}

		inline void compute_kappa()
		{
			const int N_kappa = 2;
			for (int c = N_kappa; c < size - N_kappa - 1; c++)
			{
				points[c].ComputeKappa(&points[c - N_kappa], &points[c + N_kappa]);
			}
		}

		CacheToGlobal search_u(double u, CacheToGlobal cache)
		{
			int lap = 0;
			// un-looping 
			u = normalize_u(u, lap);

			size_t index = 0;
			size_t n = u_cache.size();
			if (cache.initialized == false)
			{	// find from all : binary search
				size_t front = 0;
				size_t back = n - 1;
				while (back - front > 3)
				{
					size_t mid = (front + back) / 2;
					if (u_cache[mid] < u)
					{
						front = mid;
					}
					else {
						back = mid;
					}
					index = mid;
				}
			}
			else {
				index = cache.prev_index;
			}

			if (index < 0)index = 0;
			if (index >= n) index = n - 1;
			// search around mid

			// backward search
			while (index > 0 && u < u_cache[index])
			{
				index--;
			}
			// forward search
			while ( index + 1 < size && u > u_cache[index + 1])
			{
				index++;
			}
			CacheToGlobal ret;
			ret.initialized = true;
			ret.prev_index = index;
			ret.lap = lap;
			return ret;
		}

		// make anchor points for quick search of Frenet point
		void make_anchors()
		{
			double len = length;
			const int N = 100;

			double u = 0;
			anchors.push_back(0);
			for (size_t i = 1; i < N; i++)
			{
				u += length / N;
				auto itr = upper_bound(u_cache.begin(), u_cache.end(), u);
				size_t index = itr - u_cache.begin();
				if (anchors.back() != index)
				{
					anchors.push_back(index);
				}
			}
			if (anchors.back() != size - 1)
			{
				anchors.push_back(size - 1);
			}
		}

		// find nearest base point
		size_t find_basepoint(double x, double y) const
		{
			double min_dist = 10e60;
			size_t min_ind = 0;
			for (size_t i = 0; i < anchors.size(); i++)
			{
				double diffx = points[anchors[i]].pos.x() - x;
				double diffy = points[anchors[i]].pos.y() - y;
				double sq_dist = x * x + y * y;
				if (sq_dist < min_dist)
				{
					min_dist = sq_dist;
					min_ind = anchors[i];
				}
			}
			return min_ind;
		}

		// normalize u by unwrapping in looped course.
		// for normal course, return u.
		// for loop course, adjust in range of 0-length
		double normalize_u(double u, int& lap)
		{
			int _lap = lap;
			// un-looping 
			if (isLooping)
			{
				while (u < 0)
				{
					u += length;
					lap--;
				}
				while (u > length)
				{
					u -= length;
					lap++;
				}
			}
			return u;
		}

		int sgn(double val) {
			return (0 < val) - (val < 0);
		}

		double lin_p(double x1, double x2, double y1, double y2, double x)
		{
			double delta = 0;
			if (x2 == x1)
				return 10e20 * sgn(y2-y1);
			delta = (y2 - y1) / (x2 - x1);
			double ret = y1 + delta * (x - x1);
			return ret;
		}

		void get_anglevec(double angle_rad, Vector2 &basisVec)
		{
			basisVec.x() = cos(angle_rad);
			basisVec.y() = sin(angle_rad);
		}

	};

}
