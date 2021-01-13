#ifndef _CAR_H_
#define _CAR_H_

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

#define DEG2RAD M_PI/180.0

class Car {
protected:
    double x;
    double y;
    double yaw;
    
    double v;
    double w;

public:
    Car(){
        x = 0;
        y = 0;
        yaw = 0;

        v = 0;
        w = 0;
    };
    Car(double _x, double _y, double _yaw){
        x = _x;
        y = _y;
        yaw = _yaw;

        v = 0;
        w = 0;
    };

    double getX(){return x;};
    double getY(){return y;};
    double getYaw(){return yaw;};
    
    void setX(double _x){x = _x;};
    void setY(double _y){y = _y;};
    void setYaw(double _yaw){yaw = _yaw;};

    double getV(){return v;};
    double getW(){return w;};
    
    void setV(double _v){v = _v;};
    void setW(double _w){w = _w;};

    void update(double dt){
        double dx = v * cos(yaw);
        double dy = v * sin(yaw);
        x += dx*dt;
        y += dy*dt;

        yaw += w*dt;
    };
};

class BicycleCar : public Car{
protected:
    float lf;
    float lr;

    double slip;
    double acceleration;
    double steer;

public:
    BicycleCar():Car(){
        lf = 1.5;
        lr = 1.5;

        slip = 0;
        acceleration = 0;
        steer = 0; 
    };
    BicycleCar(float _lf, float _lr):Car(){
        lf = _lf;
        lr = _lr;

        slip = 0;
        acceleration = 0;
        steer = 0; 
    };
    BicycleCar(double _x, double _y, double _yaw):Car(_x, _y, _yaw){
        lf = 1.5;
        lr = 1.5;

        slip = 0;
        acceleration = 0;
        steer = 0; 
    };
    BicycleCar(float _lf, float _lr, double _x, double _y, double _yaw):Car(_x, _y, _yaw){
        lf = _lf;
        lr = _lr;

        slip = 0;
        acceleration = 0;
        steer = 0; 
    };

    float getLf(){return lf;};
    float getLr(){return lr;};
    
    void setLf(float _lf){lf = _lf;};
    void setLr(float _lr){lr = _lr;};

    double getAcceleration(){return acceleration;};
    double getSteer(){return steer;};
    double getSlip(){return slip;};

    void setAcceleration(double _acceleration){acceleration = _acceleration;};
    void setSteer(double _steer){steer = _steer;};

    void update(double dt){
        slip = atan(tan(steer)*lr/(lf+lr));
        
        double dx = v*cos(yaw+slip);
        double dy = v*sin(yaw+slip);
        double dv = acceleration;
        w = v*sin(slip)/lr;

        x += dx*dt;
        y += dy*dt;
        v += dv*dt;
        yaw += w*dt;
        if(yaw >= M_PI) yaw -= 2*M_PI;
        else if(yaw <= -M_PI) yaw += 2*M_PI;
    };
};

class RCcar : public BicycleCar{
protected:	
    float motor;
    float PWM_max_motor;
    float PWM_min_motor;
    float motor_offset;

    float servo;
	float PWM_max_servo;
	float PWM_min_servo;
    float servo_offset;

    float max_v;
    float min_v;
    float max_steer;
    float min_steer;

    double steer_rate;

    double v_dt;
    double steer_dt;

    void limit_signal_PWM(float &signal_PWM, float PWM_max, float PWM_min){
        if(PWM_max > PWM_min){
            if(signal_PWM > PWM_max){
                signal_PWM = PWM_max;
            }
            else if(signal_PWM < PWM_min){
                signal_PWM = PWM_min;
            }
        }
        else{
            if(signal_PWM < PWM_max){
                signal_PWM = PWM_max;
            }
            else if(signal_PWM > PWM_min){
                signal_PWM = PWM_min;
            }
        }
    };

public:
    RCcar():BicycleCar(0.15, 0.11){
        motor_offset = 1475;
        motor = motor_offset;
        PWM_max_motor = 1000;
        PWM_min_motor = 2000;

        servo_offset = 1500;
        servo = servo_offset;
        PWM_max_servo = 2000;
        PWM_min_servo = 1000;

        max_v = 3.0;
        min_v = -3.0;
        max_steer = 20*DEG2RAD;
        min_steer = -20*DEG2RAD;

        steer_rate = 0.0;

        v_dt = 2.0;
        steer_dt = 0.01;
    };
    // RCcar(float _lf, float _lr):BicycleCar(_lf, _lr){
    //     motor_offset = 1475;
    //     motor = motor_offset;
    //     PWM_max_motor = 2000;
    //     PWM_min_motor = 1000;

    //     servo_offset = 1500;
    //     servo = servo_offset;
    //     PWM_max_servo = 2000;
    //     PWM_min_servo = 1000;

    //     max_v = 2.0;
    //     min_v = -2.0;
    //     max_steer = 45*DEG2RAD;
    //     min_steer = -45*DEG2RAD;

    //     steer_rate = 0.0;
    // };
    // RCcar(float _lf, float _lr, float _motor_offset, float _PWM_max_motor, float _PWM_min_motor, 
    //         float _servo_offset, float _PWM_max_servo, float _PWM_min_servo):BicycleCar(_lf, _lr){
    //     motor_offset = _motor_offset;
    //     motor = motor_offset;
    //     PWM_max_motor = _PWM_max_motor;
    //     PWM_min_motor = _PWM_min_motor;

    //     servo_offset = _servo_offset;
    //     servo = servo_offset;
    //     PWM_max_servo = _PWM_max_servo;
    //     PWM_min_servo = _PWM_min_servo;

    //     max_v = 2.0;
    //     min_v = -2.0;
    //     max_steer = 45*DEG2RAD;
    //     min_steer = -45*DEG2RAD;

    //     steer_rate = 0.0;
    // };
    // RCcar(float _lf, float _lr, float _motor_offset, float _PWM_max_motor, float _PWM_min_motor, 
    //         float _servo_offset, float _PWM_max_servo, float _PWM_min_servo, 
    //         float _max_v, float _min_v, float _max_steer, float _min_steer):BicycleCar(_lf, _lr){
    //     motor_offset = _motor_offset;
    //     motor = motor_offset;
    //     PWM_max_motor = _PWM_max_motor;
    //     PWM_min_motor = _PWM_min_motor;

    //     servo_offset = _servo_offset;
    //     servo = servo_offset;
    //     PWM_max_servo = _PWM_max_servo;
    //     PWM_min_servo = _PWM_min_servo;

    //     max_v = _max_v;
    //     min_v = _min_v;
    //     max_steer = _max_steer*DEG2RAD;
    //     min_steer = _min_steer*DEG2RAD;

    //     steer_rate = 0.0;
    // };

    float getMotor(){return motor;};
    float getServo(){return servo;};

    void setMotor(float delta_motor){
        float _motor = motor_offset - delta_motor;
        limit_signal_PWM(_motor, PWM_max_motor, PWM_min_motor);
        motor = _motor;
    };
    void setServo(float delta_servo){
        float _servo = servo_offset - delta_servo;
        limit_signal_PWM(_servo, PWM_max_servo, PWM_min_servo);
        servo = _servo;
    }

    void updateControlInput(){
        //Simple PWM model
        // float delta_motor = motor_offset - motor;
        // double v_ref = (delta_motor>=0 ? max_v/(motor_offset-PWM_max_motor) : 
        //                                  min_v/(motor_offset-PWM_min_motor)) * delta_motor;
        double v_ref = 0.0;
        if(motor < 1475){
            v_ref = (motor_offset - motor)/1.0;
            if(v_ref > max_v) v_ref = max_v;
            acceleration = (v_ref - v) / v_dt;
            printf("Vel_ref_1: %f \n", v_ref);
        }
        else if(motor >= 1475 && motor <= 1500){
            v_ref = 0.0;
            acceleration = -0.5;
        }
        else{
            v_ref = min_v - min_v*(PWM_min_motor - motor)/(PWM_min_motor-1500);
            if(v_ref < min_v) v_ref = min_v;
            acceleration = (v_ref - v) / v_dt;
        }
        // double v_ref = max_v - (max_v - min_v)/(PWM_max_motor - PWM_min_motor)*(PWM_max_motor - motor);
        // if(v_ref > max_v) v_ref = max_v;
        // else if(v_ref < min_v) v_ref = min_v;

        // acceleration = (v_ref - v) / v_dt;
 
        float delta_servo = servo_offset - servo;
        double steer_ref = (delta_servo>=0 ? max_steer/(servo_offset-PWM_max_servo) : 
                                         min_steer/(servo_offset-PWM_min_servo)) * delta_servo;

        steer_rate = (steer_ref - steer) / steer_dt;
        printf("//////////////////////////\n");
        printf("Motor_offset: %f, \n Motor: %f \n", motor_offset, motor);
        printf("Vel: %f, \n Vel_ref: %f \n", v, v_ref);
        printf("Acc: %f, \n Vel_err: %f \n", acceleration, v_ref-v);
        printf("//////////////////////////\n");
    };
    
    void updateSteer(double dt){
        steer += steer_rate * dt;
        if(steer > max_steer) steer = max_steer;
        else if(steer < min_steer) steer = min_steer;
    }
};






#endif
