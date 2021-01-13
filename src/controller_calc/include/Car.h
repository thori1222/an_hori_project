#ifndef _CAR_H_
#define _CAR_H_

/**
* Created by: TRAN Anh Tuan 2019/09/06
*/

/* =====================================================================
 * Class Low-Pass Filter
 * =====================================================================
 */

class Car {
    private:
        double x;
        double y;
        double z;
        double yaw;
        double vx;
        double vy;
        double vz;

    public:
        Car(double x=0.0, double y = 0.0, double z=0.0, double yaw = 0.0, double vx = 0.0, double vy = 0.0, double vz=0.0);

        double getX() const;
        double getY() const;
        double getZ() const;
        double getYaw() const;
        
        void setX(double x);
        void setY(double y);
        void setZ(double z);
        void setYaw(double yaw);

        double getVx() const;
        double getVy() const;
        double getVz() const;
        
        void setVx(double vx);
        void setVy(double vy);
		void setVz(double vz);
		
        void print() const;

};






#endif
