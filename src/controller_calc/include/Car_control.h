#ifndef _CAR_CONTROL_H_
#define _CAR_CONTROL_H_

#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>


using namespace std;

/**
* Created by: TRAN Anh Tuan 2019/09/06
*/

/* =====================================================================
 * Class Low-pass filter
 * =====================================================================
 */
class LowPassFilter {
    private:
        double input;
        double Ts;
        double dt;
        double output;

    public:
        LowPassFilter(double input=0.0, double Ts = 0.1, double dt = 0.01);

        // Output update
        void calculate();

        // Set filter's params
        void set_input(double input);
        void set_Ts(double Ts);
        void set_dt(double dt);
        void set_init(double output);
        // Getter
        double get_output() const ;

        void print() const ;

};

/* =====================================================================
 * Class derivative filter
 * =====================================================================
 */
class DerivativeFilter {
    private:
        double input;
        double Ts;
        double dt;
        double output;

    public:
        DerivativeFilter(double input=0.0, double Ts = 0.1, double dt = 0.01);

        // Output update
        void calculate(double &x);

        // Set filter's params
        void set_input(double input);
        void set_Ts(double Ts);
        void set_dt(double dt);

        // Getter
        double get_output() const ;

        void print() const ;

};


/* =====================================================================
 * Modulus function
 * =====================================================================
 */

template <typename T>
T mod(T a, T b) {
    return a-b*round(a/b);
}


/* =====================================================================
 * Class PID
 * =====================================================================
 */
class PID {
    private:
        double Kp;
        double Ki;
        double Kd;

        double error;
        double error_integration;
        double error_derivative;
        double error_integration_max;
        double error_integration_min;
    public:

        // Constructor
        PID(double Kp = 0.0, double Ki = 0.0, double Kd = 0.0, double error_integration_max = 100, double error_integration_min = 100);

        // Setter
        void set_Kp(double Kp);
        void set_Ki(double Ki);
        void set_Kd(double Kd);
        void set_Kp_variant (double Kp_max, double Kp_min, double error_small, double error_large);

        void reset_error_integration();

        // Getter
        double get_Kp() const;
        double get_Ki() const;
        double get_Kd() const;

        double get_error() const;
        double get_error_integration() const;
        double get_error_derivative() const;

        double calculate(double output, double setpoint, double &x, double dt, int flag);
        double calculate_Kp_variant(double output, double setpoint, double &x, double Kp_max, double Kp_min, double error_small, double error_large, double dt, int flag);
};



/* =====================================================================
 * Lane keeping State Feedback controller
 * Created by: H. Okuda
 * =====================================================================
 */
struct StateFBControlParameter
{
    double PFLLook;
    double PFSpeed;

    double PFKspeed;
    double PFKangle;

    double SFBK1;
    double SFBK2;
    double SFBK3;
    double SFBK4;

    double SFBLLook;

    StateFBControlParameter();

    void ReadFromMap(std::map<std::string, double> param);
    void TryGetVal(std::map<std::string, double> &param, std::string key, double &val);
};




#endif
