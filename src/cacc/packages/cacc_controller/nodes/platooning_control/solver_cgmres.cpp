#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <ros/ros.h>
#include <platoon.h>
#include <predictionModel.h>
#include <packetHandler.h>

#include <dynamic_reconfigure/server.h>
#include <cacc_controller/MpcParamConfig.h>

using namespace std;

#define NCAR 1 //The number of automated cars
#define NCARMAX 2*NCAR //The maximum number of whole cars in the platoon 
                  //(should be double of the number of the automated cars)
int ncar;      //DETECTION: the number of automated cars
               //LOCALIZATION: the number of linked cars (including active manual cars)
               //COMBINED: the number of linked cars (including active manual cars)
int manual_sum = 0; //The number of manual cars counted from the flags
 
void MpcParamConfigCallback(cacc_controller::MpcParamConfig &config, uint32_t level);

// Variables for communication
int id[NCARMAX];
bool manual[NCARMAX];
unsigned int checksum = 0;

StatePacketListener* state_packet_listener[NCARMAX];
StatePacketSpeaker* predicted_state_packet_speaker[NCARMAX];
StatePacketSpeaker* curr_state_packet_speaker[NCARMAX];
StatePacketSpeaker* state_error_packet_speaker[NCARMAX];
ControlPacketSpeaker* control_packet_speaker[NCARMAX];
cacc_msgs::CaccStatePacket cacc_state_packet_msg[NCARMAX];
cacc_msgs::CaccStatePacket cacc_predicted_state_packet_msg[NCARMAX];
cacc_msgs::CaccStatePacket cacc_curr_state_packet_msg[NCARMAX];
cacc_msgs::CaccStatePacket cacc_state_error_packet_msg[NCARMAX];
cacc_msgs::CaccControlPacket cacc_control_packet_msg[NCARMAX];

// For MPC
MpcParameter                                    mpc_parameter;
cacc_msgs::CaccMpcParam                         cacc_mpc_param_msg;
ros::Publisher                                  cacc_mpc_param_pub;

cacc_msgs::CaccMpcState                         cacc_mpc_state_msg;
ros::Publisher                                  cacc_mpc_state_pub;

// CACC Controller
Prarx<2*NCAR-1>*                                prarx[NCAR-1];
Platoon<NCAR, Prarx<2*NCAR-1> >                 platoon;
PlatoonController<NCAR, Prarx<2*NCAR-1> >       controller;

// Relative velocity
double                                          range_rate_front[NCARMAX];
double                                          range_rate_back[NCARMAX];

// Flags
bool                                            using_sensor_flag = false; //true: use speed info from communication / false: calculate speed from rage (leading car, manual car)
bool                                            cutin_flag = false; //true: consider the activated manual cars as cutin cars and use speed info from preceding automated car

// CSV output
bool                                            Flag_csv_output = false;
std::string                                     output_csv_folder;


// Cruise control reference velocity
double                                          vel_ref;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "cacc_solver_cgmres");
    //THW dynamic reconfigurer
    dynamic_reconfigure::Server<cacc_controller::MpcParamConfig> server;
    dynamic_reconfigure::Server<cacc_controller::MpcParamConfig>::CallbackType f;

    f = boost::bind(&MpcParamConfigCallback, _1, _2);
    server.setCallback(f);

    //Initialize pointers
    for(int i=0; i<NCARMAX; i++){
        state_packet_listener[i] = NULL;
        predicted_state_packet_speaker[i] = NULL;
        curr_state_packet_speaker[i] = NULL;
        state_error_packet_speaker[i] = NULL;
        control_packet_speaker[i] = NULL;
    }
    for(int i=0; i<NCARMAX; i++){
        range_rate_front[i] = 0;
        range_rate_back[i] = 0;
    }
    for(int i=0; i<NCAR-1; i++){
        delete prarx[i];
        prarx[i] = NULL;
    }

    //Node handles
    ros::NodeHandle nh;
    ros::NodeHandle private_nh("~");

    PositionType position_type;
    std::string position_type_str;

    private_nh.param<std::string>("position_type_str", position_type_str, "detection");
    private_nh.param<int>("number_of_car", ncar, 2);

    private_nh.param<bool>("using_sensor_flag", using_sensor_flag, false);
    private_nh.param<bool>("cutin_flag", cutin_flag, false);

    private_nh.param<bool>("Flag_csv_output", Flag_csv_output, false);
    private_nh.param<std::string>("output_csv_folder", output_csv_folder, "data_exp");

    // Open CSV file
    std::ofstream myfile;
    time_t now = time(NULL);
    tm* now_local = localtime(&now);

    if(Flag_csv_output){
        char str[256];
        strftime(str,sizeof(str)-1,"%Y%m%d_%H%M%S",now_local);    
        string date_str(str);
        string filename = output_csv_folder + "/data_cgmres_" + date_str + ".csv";
        myfile.open (filename);
        myfile << "Time,range0-1,range1-2,range2-3,input1,input2\n";
    }
    
    if(position_type_str == "detection"){
        position_type = DETECTION;
        ROS_INFO("platooning controller: Position_type has been set as detection mode.");
    }
    else if(position_type_str == "localization"){
        position_type = LOCALIZATION;
         ROS_INFO("platooning controller: Position_type has been set as localization mode.");
    }
    else if(position_type_str == "combined"){
        position_type = COMBINED;
         ROS_INFO("platooning controller: Position_type has been set as combined mode.");
    }
    else{
        ROS_ERROR("platooning controller: platooning controller: Position_type has been set with wrong type.");
        return -1;
    }
    
    // if(ncar > NCARMAX/2){
    //     ROS_ERROR("platooning controller: The number of car has not to be exceed the maximum number, %d. ", ncar);
    //     ncar = NCARMAX/2;
    // }
    // else{
        switch(position_type){
        case DETECTION:
            ROS_INFO("platooning controller: Solver position_type has been set DETECTION: using distance and position of only automated cars.");
            if(ncar < 1){
                ROS_ERROR("platooning controller: The number of car has to be bigger than 0.");
            return -1;
            }
            else if(ncar != NCAR){
                ROS_ERROR("THE GIVEN NUMBER OF CAR IS NOT SUPPORTED. YOU HAVE TO REBUILD THE PROGRAM WITH THE NUMBER.");
                return -1;
            }
            break;
        case LOCALIZATION:
            ROS_INFO("platooning controller: Solver position_type has been set LOCALIZATION: using localization of whole cars.");
            if(ncar < 2){
                ROS_ERROR("platooning controller: The number of car has to be bigger than 1.");
                return -1;
            }
            break;
        case COMBINED:
            ROS_INFO("platooning controller: Solver position_type has been set COMBINED: using both localization and detection of whole cars.");
            if(ncar < 1){
                ROS_ERROR("platooning controller: The number of car has to be bigger than 0.");
                return -1;
            }
            break;
        default:
            ROS_ERROR("platooning controller: The mode has been set with wrong number.");
            return -1;
        }
    // }
    
    //In case of detection, check the manual flag (all cars should be automated)
    ROS_INFO("platooning controller: !!!! CHECKING THE CONSISTENCY IN THE FLAGS... !!!!");
    if(position_type == DETECTION){
        for(int ic = 0; ic < ncar; ic++){
            //Get the flag
            private_nh.param<bool>("manual_"+std::to_string(ic), manual[ic], false);
            if(manual[ic]){
                ROS_ERROR("platooning controller: The car must be an automated car.");
                return -1;
            }
        }
    }
    //In case of localization, check the manual flag
    else if(position_type == LOCALIZATION){
        for(int ic = 0; ic < ncar; ic++){
            //Get the flag
            private_nh.param<bool>("manual_"+std::to_string(ic), manual[ic], false);
            //Leading car (Car 0) must be manual
            if(ic == 0 && !manual[ic]){
                ROS_ERROR("platooning controller: The leading car must be a manual car.");
                return -1;
            } 
            //First car (Car 1) must be automated
            if(ic == 1 && manual[ic]){
                ROS_ERROR("platooning controller: Car 1 must be an automated car.");
                return -1;
            } 
            //Last car (Car N) must be automated
            if(ic == ncar-1 && manual[ic]){
                ROS_ERROR("platooning controller: The last car must be an automated car.");
                return -1;
            } 
            //Front and rear of a manual car must be automated cars
            if(ic > 0 && manual[ic] && manual[ic-1]){
                ROS_ERROR("platooning controller: Manual cars cannot be continuous.");
                return -1;
            }
            if(manual[ic]){
                manual_sum++;
            }
        }

        //Check the number of cars and manual cars with the set NCAR
        if(ncar - manual_sum != NCAR){
            ROS_ERROR("platooning controller: The number of cars is not matched with NCAR set in the solver. Please check the launch file or rebuild the solver with correct number.");
            ROS_ERROR("platooning controller: NCAR: %d, \nNCARMAX: %d, \nncar: %d, \nmanual_sum: %d", NCAR, NCARMAX, ncar, manual_sum);
            return -1;
        }
    }
    //In case of combined, check the manual flag
    else if(position_type == COMBINED){
        for(int ic = 0; ic < ncar; ic++){
            //Get the flag
            private_nh.param<bool>("manual_"+std::to_string(ic), manual[ic], false);
            // //Leading car (Car 0) must be manual
            // if(ic == 0 && !manual[ic]){
            //     ROS_ERROR("The leading car must be a manual car.");
            //     return -1;
            // } 
            // //First car (Car 1) must be automated
            // if(ic == 1 && manual[ic]){
            //     ROS_ERROR("Car 1 must be an automated car.");
            //     return -1;
            // } 
            //Last car (Car N) must be automated
            if(ic == ncar-1 && manual[ic]){
                ROS_ERROR("platooning controller: The last car must be an automated car.");
                return -1;
            } 
            //Front and rear of a manual car must be automated cars
            if(ic > 0 && manual[ic] && manual[ic-1]){
                ROS_ERROR("platooning controller: Manual cars cannot be continuous.");
                return -1;
            }
            if(manual[ic]){
                manual_sum++;
            }
        }
    }

    //Set up id, listener, and speaker
    //bool prediction = true;
    int iac = 0;
    switch(position_type){
    case DETECTION:
        for(int ic = 0; ic < ncar; ic++){
            private_nh.param<int>("id_"+std::to_string(ic+1), id[ic*2+1], ic+1);
            state_packet_listener[ic*2+1] = new StatePacketListener(ic*2+1, id[ic*2+1], "CACC");
            curr_state_packet_speaker[ic*2+1] = new StatePacketSpeaker(ic*2+1, id[ic*2+1], "CACC", StatePacketType::CURRENT);
            state_error_packet_speaker[ic*2+1] = new StatePacketSpeaker(ic*2+1, id[ic*2+1], "CACC", StatePacketType::ERROR);
            predicted_state_packet_speaker[ic*2+1] = new StatePacketSpeaker(ic*2+1, id[ic*2+1], "CACC", StatePacketType::PREDICT);
            control_packet_speaker[ic] = new ControlPacketSpeaker(ic+1, id[ic*2+1]);
            
            id[ic*2] = 500 + id[ic*2+1];
            state_packet_listener[ic*2] = new StatePacketListener(ic*2, id[ic*2], "CACC"); 
            curr_state_packet_speaker[ic*2] = new StatePacketSpeaker(ic*2, id[ic*2], "CACC", StatePacketType::CURRENT);
            state_error_packet_speaker[ic*2] = new StatePacketSpeaker(ic*2, id[ic*2], "CACC", StatePacketType::ERROR);
            predicted_state_packet_speaker[ic*2] = new StatePacketSpeaker(ic*2, id[ic*2], "CACC", StatePacketType::PREDICT); 
        }
        break;

    case LOCALIZATION:
        iac = 0;
        for(int ic = 0; ic < ncar; ic++){
            if(!manual[ic]){
                private_nh.param<int>("id_"+std::to_string(ic), id[iac*2+1], ic);
                control_packet_speaker[ic] = new ControlPacketSpeaker(ic, id[2*iac+1]);
                state_packet_listener[2*iac+1] = new StatePacketListener(2*iac+1, id[2*iac+1], "CACC"); 
                curr_state_packet_speaker[2*iac+1] = new StatePacketSpeaker(2*iac+1, id[2*iac+1], "CACC", StatePacketType::CURRENT); 
                state_error_packet_speaker[2*iac+1] = new StatePacketSpeaker(2*iac+1, id[2*iac+1], "CACC", StatePacketType::ERROR); 
                predicted_state_packet_speaker[2*iac+1] = new StatePacketSpeaker(2*iac+1, id[2*iac+1], "CACC", StatePacketType::PREDICT); 

                if(manual[ic-1]){
                    private_nh.param<int>("id_"+std::to_string(ic-1), id[2*iac], ic-1);
                    if(iac!=0){
                        prarx[iac-1] = new Prarx<2*NCAR-1>(2*iac-1, new PrarxModel(0.1, 2.0, -2.0));
                        platoon.set_activation(iac-1, prarx[iac-1]);
                    }
                }    
                else{
                    id[2*iac] = 500 + id[2*iac+1];
                }  
                state_packet_listener[2*iac] = new StatePacketListener(2*iac, id[2*iac], "CACC");
                curr_state_packet_speaker[2*iac] = new StatePacketSpeaker(2*iac, id[2*iac], "CACC", StatePacketType::CURRENT);
                state_error_packet_speaker[2*iac] = new StatePacketSpeaker(2*iac, id[2*iac], "CACC", StatePacketType::ERROR);
                predicted_state_packet_speaker[2*iac] = new StatePacketSpeaker(2*iac, id[2*iac], "CACC", StatePacketType::PREDICT);

                iac++;
            }
        }
        break;
    case COMBINED:
        iac = 0;
        for(int ic = 0; ic < ncar; ic++){
            if(!manual[ic]){
                private_nh.param<int>("id_"+std::to_string(ic), id[iac*2+1], ic);
                control_packet_speaker[ic] = new ControlPacketSpeaker(ic, id[2*iac+1]);
                state_packet_listener[2*iac+1] = new StatePacketListener(2*iac+1, id[2*iac+1], "CACC"); 
                curr_state_packet_speaker[2*iac+1] = new StatePacketSpeaker(2*iac+1, id[2*iac+1], "CACC", StatePacketType::CURRENT); 
                state_error_packet_speaker[2*iac+1] = new StatePacketSpeaker(2*iac+1, id[2*iac+1], "CACC", StatePacketType::ERROR); 
                predicted_state_packet_speaker[2*iac+1] = new StatePacketSpeaker(2*iac+1, id[2*iac+1], "CACC", StatePacketType::PREDICT); 

                if(manual[ic-1]){
                    private_nh.param<int>("id_"+std::to_string(ic-1), id[2*iac], ic-1);
                    prarx[iac] = new Prarx<2*NCAR-1>(2*iac+1, new PrarxModel(0.1, 2.0, -2.0));
                    platoon.set_activation(iac, prarx[iac]);
                }    
                else{
                    id[2*iac] = 500 + id[2*iac+1];
                }  
                state_packet_listener[2*iac] = new StatePacketListener(2*iac, id[2*iac], "CACC");
                curr_state_packet_speaker[2*iac] = new StatePacketSpeaker(2*iac, id[2*iac], "CACC", StatePacketType::CURRENT);
                state_error_packet_speaker[2*iac] = new StatePacketSpeaker(2*iac, id[2*iac], "CACC", StatePacketType::ERROR);
                predicted_state_packet_speaker[2*iac] = new StatePacketSpeaker(2*iac, id[2*iac], "CACC", StatePacketType::PREDICT);

                iac++;
            }
        }
        break;
    }

    //Initialization
    controller.init(&platoon);

    //Parameter publisher
    cacc_mpc_param_pub = nh.advertise<cacc_msgs::CaccMpcParam>("cacc_mpc_param", 1);
    cacc_mpc_state_pub = nh.advertise<cacc_msgs::CaccMpcState>("cacc_mpc_state", 1);

    //ROS loop
    ros::Rate loop_rate(100);
    ROS_INFO("platooning controller: !!!! LOOP START !!!!");
    ROS_INFO("platooning controller: Car 0: %d\nCar1: %d\nCar2: %d\nCar3: %d", id[0], id[1], id[2], id[3]);
    ROS_INFO("===== INITIAL OPTIMIZATION PROBLEM =====");
    ROS_INFO("---------\nDs: %f\nDmin: %f\nUmax: %f\nUmin: %f", 
                platoon.Ds, platoon.Dmin, platoon.umax, platoon.umin);
    for(int ic = 0; ic < ncar-1; ic++){
        ROS_INFO("---------\nx[%d]: %f\nx[%d]: %f\nx[%d]: %f", 
                    3*ic+0, platoon.x[3*ic+0],
                    3*ic+1, platoon.x[3*ic+1],
                    3*ic+2, platoon.x[3*ic+2]);
    }
    for(int ic = 0; ic < ncar-1; ic++){
        ROS_INFO("---------\nx1[%d]: %f\nx1[%d]: %f\nx1[%d]: %f", 
                    3*ic+0, platoon.x1[3*ic+0],
                    3*ic+1, platoon.x1[3*ic+1],
                    3*ic+2, platoon.x1[3*ic+2]);
    }
    ROS_INFO("===============================");

    double time_exp_start;
    time_exp_start = ros::Time::now().toSec();
            
    while(ros::ok()){
        //Get sensor info
        ros::spinOnce();    
        switch(position_type){
        case DETECTION:
            for(int ic = 0; ic < 2*ncar; ic++){
                state_packet_listener[ic]->get_cacc_state_packet_msg(&cacc_state_packet_msg[ic]);

                //Set the states
                if(ic != 0){
                    platoon.x1[3*(ic-1)+0] = cacc_state_packet_msg[ic].distance;
                    platoon.x1[3*(ic-1)+1] = cacc_state_packet_msg[ic].speed;
                    platoon.thw[ic-1] = cacc_state_packet_msg[ic].thw;
                    platoon.alpha[ic-1] = cacc_state_packet_msg[ic].alpha;
                    platoon.beta[ic-1] = cacc_state_packet_msg[ic].beta;
                    //platoon.beta[ic-1] = (platoon.alpha[ic-1]-1)/controller.ht;
                    if(platoon.manual[ic-1]){
                        platoon.x1[3*(ic-1)+2] = cacc_state_packet_msg[ic].acceleration;
                        //platoon.u[ic-1] = 0;
                    }
                    else{
                        platoon.x1[3*(ic-1)+2] = cacc_state_packet_msg[ic].acceleration;
                        //platoon.u[ic-1] = cacc_state_packet_msg[ic].acceleration;
                    }
                }  
                            
                //Set the states of the leading car
                platoon.v = cacc_state_packet_msg[ic].speed;
                platoon.a = 0.0; //Constant speed model
            }
            break;
        case LOCALIZATION:
            for(int ic = 0; ic < 2*NCAR; ic++){
                state_packet_listener[ic]->get_cacc_state_packet_msg(&cacc_state_packet_msg[ic]);
                if(cacc_state_packet_msg[ic].id==0 && cacc_state_packet_msg[ic].distance==0 && cacc_state_packet_msg[ic].speed==0 && cacc_state_packet_msg[ic].acceleration==0) 
                    continue;
                //Set the states
                if(ic != 0){
                    if(platoon.manual[ic-1]){
                        platoon.activated[(ic-2)/2] = cacc_state_packet_msg[ic].activated;
                        platoon.x1[3*(ic-1)+0] = cacc_state_packet_msg[ic].distance;
                        platoon.thw[ic-1] = cacc_state_packet_msg[ic].thw;
                        platoon.alpha[ic-1] = cacc_state_packet_msg[ic].alpha;
                        platoon.beta[ic-1] = cacc_state_packet_msg[ic].beta;
                        //platoon.beta[ic-1] = (platoon.alpha[ic-1]-1)/controller.ht;
                        
                        if(platoon.activated[(ic-2)/2]){
                            if(cutin_flag){
                                platoon.x1[3*(ic-1)+1] = cacc_state_packet_msg[ic-1].speed;
                                platoon.x1[3*(ic-1)+2] = cacc_state_packet_msg[ic-1].acceleration;
                            }
                            else{
                                if(using_sensor_flag){
                                    platoon.x1[3*(ic-1)+1] = cacc_state_packet_msg[ic].speed;
                                    platoon.x1[3*(ic-1)+2] = cacc_state_packet_msg[ic].acceleration;
                                }
                                else{
                                    range_rate_front[ic] = 0.9*range_rate_front[ic] + 0.1*(platoon.x1[3*(ic-1)+0] - platoon.x[3*(ic-1)+0])/controller.ht;
                                    range_rate_back[ic] = 0.9*range_rate_back[ic] + 0.1*(cacc_state_packet_msg[ic+1].distance - platoon.x[3*(ic)+0])/controller.ht;
                                    //range_rate_back[ic] = 0.9*range_rate_back[ic] + 0.1*(platoon.x1[3*(ic)+0] - platoon.x[3*(ic)+0])/controller.ht;
                                    platoon.x1[3*(ic-1)+1] = 0.9*platoon.x[3*(ic-1)+1] + 0.1*(0.5*(platoon.x1[3*(ic-2)+1]-range_rate_front[ic])+0.5*(range_rate_back[ic]+cacc_state_packet_msg[ic+1].speed));
                                    //platoon.x1[3*(ic-1)+1] = 0.5*cacc_state_packet_msg[ic].speed + 0.5*(0.5*(platoon.x1[3*(ic-2)+1]-range_rate_front[ic])+0.5*(range_rate_back[ic]+cacc_state_packet_msg[ic+1].speed));
                                    platoon.x1[3*(ic-1)+2] = 0.9*platoon.x[3*(ic-1)+2] + 0.1*(platoon.x1[3*(ic-1)+1] - platoon.x[3*(ic-1)+1])/controller.ht;
                                    //platoon.x1[3*(ic-1)+2] = cacc_state_packet_msg[ic].acceleration;
                                }
                            }
                        }
                        else{
                            platoon.x1[3*(ic-1)+1] = cacc_state_packet_msg[ic].speed;
                            platoon.x1[3*(ic-1)+2] = cacc_state_packet_msg[ic].acceleration;
                        }
                    }
                    else{
                        platoon.x1[3*(ic-1)+0] = cacc_state_packet_msg[ic].distance;
                        platoon.x1[3*(ic-1)+1] = cacc_state_packet_msg[ic].speed;
                        platoon.x1[3*(ic-1)+2] = cacc_state_packet_msg[ic].acceleration;
                        platoon.thw[ic-1] = cacc_state_packet_msg[ic].thw;
                        platoon.alpha[ic-1] = cacc_state_packet_msg[ic].alpha;
                        platoon.beta[ic-1] = cacc_state_packet_msg[ic].beta;
                    }
                }  

                //Set the states of the leading car
                else{
                    if(using_sensor_flag){
                        platoon.a = 0.0;
                        platoon.v = cacc_state_packet_msg[ic].speed; 
                    }
                    else{
                        range_rate_back[0] = 0.9*range_rate_back[0] + 0.1*(platoon.x1[0] - platoon.x[0])/controller.ht;
                        platoon.v = 0.9*platoon.v + 0.1*(platoon.x1[1] + range_rate_back[0]); 
                        platoon.a = 0.0; //Constant speed model
                    }                    
                }
            }
            break; 
        case COMBINED:
            for(int ic = 0; ic < 2*NCAR; ic++){
                state_packet_listener[ic]->get_cacc_state_packet_msg(&cacc_state_packet_msg[ic]);
            
                //Set the states
                if(ic != 0){
                    if(platoon.manual[ic-1]){
                        platoon.activated[(ic-2)/2] = cacc_state_packet_msg[ic].activated;
                        platoon.x1[3*(ic-1)+0] = cacc_state_packet_msg[ic].distance;
                        platoon.thw[ic-1] = cacc_state_packet_msg[ic].thw;
                        platoon.alpha[ic-1] = cacc_state_packet_msg[ic].alpha;
                        platoon.beta[ic-1] = cacc_state_packet_msg[ic].beta;
                        //platoon.beta[ic-1] = (platoon.alpha[ic-1]-1)/controller.ht;
                        
                        if(platoon.activated[(ic-2/2)]){
                            if(cutin_flag){
                                platoon.x1[3*(ic-1)+1] = cacc_state_packet_msg[ic-1].speed;
                                platoon.x1[3*(ic-1)+2] = cacc_state_packet_msg[ic-1].acceleration;
                            }
                            else{
                                if(using_sensor_flag){
                                    platoon.x1[3*(ic-1)+1] = cacc_state_packet_msg[ic].speed;
                                    platoon.x1[3*(ic-1)+2] = cacc_state_packet_msg[ic].acceleration;
                                }
                                else{
                                    range_rate_front[ic] = 0.9*range_rate_front[ic] + 0.1*(platoon.x1[3*(ic-1)+0] - platoon.x[3*(ic-1)+0])/controller.ht;
                                    range_rate_back[ic] = 0.9*range_rate_back[ic] + 0.1*(cacc_state_packet_msg[ic+1].distance - platoon.x[3*(ic)+0])/controller.ht;
                                    //range_rate_back[ic] = 0.9*range_rate_back[ic] + 0.1*(platoon.x1[3*(ic)+0] - platoon.x[3*(ic)+0])/controller.ht;
                                    platoon.x1[3*(ic-1)+1] = 0.9*platoon.x[3*(ic-1)+1] + 0.1*(0.5*(platoon.x1[3*(ic-2)+1]-range_rate_front[ic])+0.5*(range_rate_back[ic]+cacc_state_packet_msg[ic+1].speed));
                                    //platoon.x1[3*(ic-1)+1] = 0.5*cacc_state_packet_msg[ic].speed + 0.5*(0.5*(platoon.x1[3*(ic-2)+1]-range_rate_front[ic])+0.5*(range_rate_back[ic]+cacc_state_packet_msg[ic+1].speed));
                                    platoon.x1[3*(ic-1)+2] = 0.9*platoon.x[3*(ic-1)+2] + 0.1*(platoon.x1[3*(ic-1)+1] - platoon.x[3*(ic-1)+1])/controller.ht;
                                    //platoon.x1[3*(ic-1)+2] = cacc_state_packet_msg[ic].acceleration;
                                }
                            }
                        }
                    }
                    else{
                        platoon.x1[3*(ic-1)+0] = cacc_state_packet_msg[ic].distance;
                        platoon.x1[3*(ic-1)+1] = cacc_state_packet_msg[ic].speed;
                        platoon.x1[3*(ic-1)+2] = cacc_state_packet_msg[ic].acceleration;
                        platoon.thw[ic-1] = cacc_state_packet_msg[ic].thw;
                        platoon.alpha[ic-1] = cacc_state_packet_msg[ic].alpha;
                        platoon.beta[ic-1] = cacc_state_packet_msg[ic].beta;
                    }
                }  

                //Set the states of the leading car
                else{
                    if(using_sensor_flag){
                        platoon.a = 0.0;
                        platoon.v = cacc_state_packet_msg[ic].speed; 
                    }
                    else{
                        range_rate_back[0] = 0.9*range_rate_back[0] + 0.1*(platoon.x1[0] - platoon.x[0])/controller.ht;
                        platoon.v = 0.9*platoon.v + 0.1*(platoon.x1[1] + range_rate_back[0]); 
                        platoon.a = 0.0; //Constant speed model
                    }                    
                }
            }
            break;    
        }

        //Cruise control mode (when the distance is bigger than 50)
        if(platoon.x1[0] > 50){
            platoon.v = vel_ref;
            platoon.q[0] = 0;
            platoon.sf[0] = 0;
        }
        //Set the states of the leading car
        else{
            platoon.set_param(mpc_parameter);
        } 

        //Calculate the control inputs
        double t = 0;
        ROS_WARN("platooning controller: SOLVING OPTIMIZATION PROBLEM...");
        ROS_WARN("===== OPTIMIZATION PROBLEM =====");
        //for(int ic = 0; ic < ncar-1; ic++){
        for(int ic = 0; ic < 2*NCAR-1; ic++){
            ROS_WARN("---------\nx[%d]: %f\nx[%d]: %f\nx[%d]: %f", 
                        3*ic+0, platoon.x1[3*ic+0],
                        3*ic+1, platoon.x1[3*ic+1],
                        3*ic+2, platoon.x1[3*ic+2]);
        }
        ROS_WARN("===============================");
        controller.unew(t, platoon.x, platoon.x1, platoon.u);
        if(std::isnan(platoon.u.norm())){
            controller.init(&platoon);
            ROS_WARN("platooning controller: The CACC controller has failed to converge and been initialized.");
        }
        platoon.x = platoon.x1;

        // std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
        // std::cout << platoon.u << std::endl;
        // std::cout << platoon.x << std::endl;

        ROS_WARN("platooning controller: SOLVED.");
        ROS_WARN("===== OPTIMAL =====");
        //for(int ic = 0; ic < ncar-1; ic++){
        for(int ic = 0; ic < 2*NCAR-1; ic++){
            ROS_WARN("---------\nu[%d]: %f", ic, platoon.u[ic]);
        }
        ROS_WARN("---------\nF: %f", controller.hutau1.norm());
        ROS_WARN("===============================");

        //Publish the results
        switch(position_type){
        case DETECTION:
            for(int ic = 0; ic < ncar; ic++){
                // Control input
                cacc_control_packet_msg[ic].id = control_packet_speaker[ic]->id;
                cacc_control_packet_msg[ic].acc_ref = std::isnan(platoon.u[2*ic])?platoon.umin:platoon.u[2*ic];
                cacc_control_packet_msg[ic].vel_ref = platoon.x[3*2*ic+1] + cacc_control_packet_msg[ic].acc_ref*controller.ht
                                                *(cacc_control_packet_msg[ic].acc_ref<0?cacc_state_packet_msg[ic+1].vel_gain_dec:(platoon.x[3*2*ic+1]<1.0?cacc_state_packet_msg[ic+1].vel_gain_low:cacc_state_packet_msg[ic+1].vel_gain));
                cacc_control_packet_msg[ic].checksum = checksum;

                // //Fake acceleration input
                // cacc_control_packet_msg[ic].acc_ref = 1.0;
                // cacc_control_packet_msg[ic].vel_ref = platoon.x[3*2*ic+1] + cacc_control_packet_msg[ic].acc_ref*0.5;//*controller.ht;
                
                // //Fake velocity input
                // cacc_control_packet_msg[ic].acc_ref = 0.0;
                // cacc_control_packet_msg[ic].vel_ref = 0.0;

                control_packet_speaker[ic]->publish_cacc_control_packet_msg(cacc_control_packet_msg[ic]);             

                // Current state   
                cacc_curr_state_packet_msg[2*ic+1] = cacc_state_packet_msg[2*ic+1];
                cacc_curr_state_packet_msg[2*ic+1].distance = controller.xtau.elem(0)[3*(2*ic)+0];
                cacc_curr_state_packet_msg[2*ic+1].speed = controller.xtau.elem(0)[3*(2*ic)+1];
                cacc_curr_state_packet_msg[2*ic+1].acceleration = controller.xtau.elem(0)[3*(2*ic)+2];
                curr_state_packet_speaker[2*ic+1]->publish_cacc_state_packet_msg(cacc_curr_state_packet_msg[2*ic+1]);
                
                if(ic==0){
                    cacc_curr_state_packet_msg[2*ic] = cacc_state_packet_msg[2*ic]; 
                    cacc_curr_state_packet_msg[2*ic].speed = platoon.v;
                    cacc_curr_state_packet_msg[2*ic].acceleration = platoon.a;
                }               
                else{
                    cacc_curr_state_packet_msg[2*ic] = cacc_state_packet_msg[2*ic];
                    cacc_curr_state_packet_msg[2*ic].distance = controller.xtau.elem(0)[3*(2*ic-1)+0];
                    cacc_curr_state_packet_msg[2*ic].speed = controller.xtau.elem(0)[3*(2*ic-1)+1];
                    cacc_curr_state_packet_msg[2*ic].acceleration = controller.xtau.elem(0)[3*(2*ic-1)+2];
                }
                curr_state_packet_speaker[2*ic]->publish_cacc_state_packet_msg(cacc_curr_state_packet_msg[2*ic]);

                // State error 
                cacc_state_error_packet_msg[2*ic+1] = cacc_state_packet_msg[2*ic+1];
                cacc_state_error_packet_msg[2*ic+1].distance = controller.xtau.elem(0)[3*(2*ic)+0] - (platoon.Ds+platoon.thw[2*ic]*controller.xtau.elem(0)[3*(2*ic)+1]);
                cacc_state_error_packet_msg[2*ic+1].speed = controller.xtau.elem(0)[3*(2*ic)+1] - (ic==0 ? platoon.v : controller.xtau.elem(0)[3*(2*ic-1)+1]);
                cacc_state_error_packet_msg[2*ic+1].acceleration = controller.xtau.elem(0)[3*(2*ic)+2] - (ic==0 ? platoon.a : controller.xtau.elem(0)[3*(2*ic-1)+2]);
                state_error_packet_speaker[2*ic+1]->publish_cacc_state_packet_msg(cacc_state_error_packet_msg[2*ic+1]);
                
                if(ic==0){
                    cacc_state_error_packet_msg[2*ic] = cacc_state_packet_msg[2*ic]; 
                    cacc_state_error_packet_msg[2*ic+1].distance = 0.0;
                    cacc_state_error_packet_msg[2*ic].speed = 0.0;
                    cacc_state_error_packet_msg[2*ic].acceleration = 0.0;
                }               
                else{
                    cacc_state_error_packet_msg[2*ic] = cacc_state_packet_msg[2*ic];
                    cacc_state_error_packet_msg[2*ic].distance = controller.xtau.elem(0)[3*(2*ic-1)+0] - (platoon.Ds+platoon.thw[2*ic-1]*controller.xtau.elem(0)[3*(2*ic-1)+1]);
                    cacc_state_error_packet_msg[2*ic].speed = controller.xtau.elem(0)[3*(2*ic-1)+1] - controller.xtau.elem(0)[3*(2*ic-2)+1];
                    cacc_state_error_packet_msg[2*ic].acceleration = controller.xtau.elem(0)[3*(2*ic-1)+2] - controller.xtau.elem(0)[3*(2*ic-2)+2];
                }
                state_error_packet_speaker[2*ic]->publish_cacc_state_packet_msg(cacc_state_error_packet_msg[2*ic]);

                // Predicted state   
                cacc_predicted_state_packet_msg[2*ic+1] = cacc_state_packet_msg[2*ic+1];
                cacc_predicted_state_packet_msg[2*ic+1].distance = controller.xtau.elem(1)[3*(2*ic)+0];
                cacc_predicted_state_packet_msg[2*ic+1].speed = controller.xtau.elem(1)[3*(2*ic)+1];
                cacc_predicted_state_packet_msg[2*ic+1].acceleration = controller.xtau.elem(1)[3*(2*ic)+2];
                predicted_state_packet_speaker[2*ic+1]->publish_cacc_state_packet_msg(cacc_predicted_state_packet_msg[2*ic+1]);
                
                if(ic==0)
                    cacc_predicted_state_packet_msg[2*ic] = cacc_state_packet_msg[2*ic];                
                else{
                    cacc_predicted_state_packet_msg[2*ic] = cacc_state_packet_msg[2*ic];
                    cacc_predicted_state_packet_msg[2*ic].distance = controller.xtau.elem(1)[3*(2*ic)+0];
                    cacc_predicted_state_packet_msg[2*ic].speed = controller.xtau.elem(1)[3*(2*ic)+1];
                    cacc_predicted_state_packet_msg[2*ic].acceleration = controller.xtau.elem(1)[3*(2*ic)+2];
                }
                predicted_state_packet_speaker[2*ic]->publish_cacc_state_packet_msg(cacc_predicted_state_packet_msg[2*ic]);
            }
            break;
        case LOCALIZATION:
            iac = 0;
            for(int ic = 0; ic < ncar; ic++){
                if(!manual[ic]){
                    // Control input
                    cacc_control_packet_msg[ic].id = id[2*iac+1];
                    cacc_control_packet_msg[ic].acc_ref = std::isnan(platoon.u[2*iac])?cacc_control_packet_msg[ic].acc_ref:platoon.u[2*iac];
                    cacc_control_packet_msg[ic].vel_ref = platoon.x[3*2*iac+1] + cacc_control_packet_msg[ic].acc_ref*controller.ht
                                                *(cacc_control_packet_msg[ic].acc_ref<0?cacc_state_packet_msg[2*iac+1].vel_gain_dec:(platoon.x[3*2*iac+1]<1.0?cacc_state_packet_msg[2*iac+1].vel_gain_low:cacc_state_packet_msg[2*iac+1].vel_gain));
                    cacc_control_packet_msg[ic].checksum = checksum;

                    std::cout << "-----------------" << ic << "===" << iac << "----------------------" << std::endl;
                    
                    // //Fake acceleration input
                    // cacc_control_packet_msg[ic].acc_ref = 1.0;
                    // cacc_control_packet_msg[ic].vel_ref = platoon.x[3*2*iac+1] + cacc_control_packet_msg[ic].acc_ref*0.5;//*controller.ht;
                    
                    // //Fake velocity input
                    // cacc_control_packet_msg[ic].acc_ref = 0.0;
                    // cacc_control_packet_msg[ic].vel_ref = 0.0;

                    control_packet_speaker[ic]->publish_cacc_control_packet_msg(cacc_control_packet_msg[ic]);                

                    // Current state
                    cacc_curr_state_packet_msg[2*iac+1] = cacc_state_packet_msg[2*iac+1];
                    cacc_curr_state_packet_msg[2*iac+1].distance = controller.xtau.elem(0)[3*(2*iac)+0];
                    cacc_curr_state_packet_msg[2*iac+1].speed = controller.xtau.elem(0)[3*(2*iac)+1];
                    cacc_curr_state_packet_msg[2*iac+1].acceleration = controller.xtau.elem(0)[3*(2*iac)+2];
                    curr_state_packet_speaker[2*iac+1]->publish_cacc_state_packet_msg(cacc_curr_state_packet_msg[2*iac+1]);
                
                    if(iac==0){
                        cacc_curr_state_packet_msg[2*iac] = cacc_state_packet_msg[2*iac]; 
                        cacc_curr_state_packet_msg[2*iac].speed = platoon.v;
                        cacc_curr_state_packet_msg[2*iac].acceleration = platoon.a;
                    }               
                    else{
                        cacc_curr_state_packet_msg[2*iac] = cacc_state_packet_msg[2*iac];
                        cacc_curr_state_packet_msg[2*iac].distance = controller.xtau.elem(0)[3*(2*iac-1)+0];
                        cacc_curr_state_packet_msg[2*iac].speed = controller.xtau.elem(0)[3*(2*iac-1)+1];
                        cacc_curr_state_packet_msg[2*iac].acceleration = controller.xtau.elem(0)[3*(2*iac-1)+2];
                    }
                    curr_state_packet_speaker[2*iac]->publish_cacc_state_packet_msg(cacc_curr_state_packet_msg[2*iac]);

                    // State error
                    cacc_state_error_packet_msg[2*iac+1] = cacc_state_packet_msg[2*iac+1];
                    cacc_state_error_packet_msg[2*iac+1].distance = controller.xtau.elem(0)[3*(2*iac)+0] - (platoon.Ds+platoon.thw[2*iac]*controller.xtau.elem(0)[3*(2*iac)+1]);
                    cacc_state_error_packet_msg[2*iac+1].speed = controller.xtau.elem(0)[3*(2*iac)+1] - (iac==0 ? platoon.v : controller.xtau.elem(0)[3*(2*iac-1)+1]);
                    cacc_state_error_packet_msg[2*iac+1].acceleration = controller.xtau.elem(0)[3*(2*iac)+2] - (iac==0 ? platoon.a : controller.xtau.elem(0)[3*(2*iac-1)+2]);
                    state_error_packet_speaker[2*iac+1]->publish_cacc_state_packet_msg(cacc_state_error_packet_msg[2*iac+1]);
                
                    if(iac==0){
                        cacc_state_error_packet_msg[2*iac] = cacc_state_packet_msg[2*iac]; 
                        cacc_state_error_packet_msg[2*iac].distance = 0.0;
                        cacc_state_error_packet_msg[2*iac].speed = 0.0;
                        cacc_state_error_packet_msg[2*iac].acceleration = 0.0;
                    }               
                    else{
                        cacc_state_error_packet_msg[2*iac] = cacc_state_packet_msg[2*iac];
                        cacc_state_error_packet_msg[2*iac].distance = controller.xtau.elem(0)[3*(2*iac-1)+0] - (platoon.Ds+platoon.thw[2*iac-1]*controller.xtau.elem(0)[3*(2*iac-1)+1]);
                        cacc_state_error_packet_msg[2*iac].speed = controller.xtau.elem(0)[3*(2*iac-1)+1] - controller.xtau.elem(0)[3*(2*iac-2)+1];
                        cacc_state_error_packet_msg[2*iac].acceleration = controller.xtau.elem(0)[3*(2*iac-1)+2] - controller.xtau.elem(0)[3*(2*iac-2)+2];
                    }
                    state_error_packet_speaker[2*iac]->publish_cacc_state_packet_msg(cacc_state_error_packet_msg[2*iac]);

                    // Predicted state
                    cacc_predicted_state_packet_msg[2*iac+1] = cacc_state_packet_msg[2*iac+1];
                    cacc_predicted_state_packet_msg[2*iac+1].distance = controller.xtau.elem(1)[3*(2*iac)+0];
                    cacc_predicted_state_packet_msg[2*iac+1].speed = controller.xtau.elem(1)[3*(2*iac)+1];
                    cacc_predicted_state_packet_msg[2*iac+1].acceleration = controller.xtau.elem(1)[3*(2*iac)+2];
                    predicted_state_packet_speaker[2*iac+1]->publish_cacc_state_packet_msg(cacc_predicted_state_packet_msg[2*iac+1]);
                
                    if(iac==0)
                        cacc_predicted_state_packet_msg[2*iac] = cacc_state_packet_msg[2*iac];                
                    else{
                        cacc_predicted_state_packet_msg[2*iac] = cacc_state_packet_msg[2*iac];
                        cacc_predicted_state_packet_msg[2*iac].distance = controller.xtau.elem(1)[3*(2*iac-1)+0];
                        cacc_predicted_state_packet_msg[2*iac].speed = controller.xtau.elem(1)[3*(2*iac-1)+1];
                        cacc_predicted_state_packet_msg[2*iac].acceleration = controller.xtau.elem(1)[3*(2*iac-1)+2];
                    }
                    predicted_state_packet_speaker[2*iac]->publish_cacc_state_packet_msg(cacc_predicted_state_packet_msg[2*iac]);
                    iac++;
                }
            }
            break;
        case COMBINED:
            iac = 0;
            for(int ic = 0; ic < ncar; ic++){
                if(!manual[ic]){
                    // Control input
                    cacc_control_packet_msg[ic].id = id[2*iac+1];
                    cacc_control_packet_msg[ic].acc_ref = std::isnan(platoon.u[2*iac])?cacc_control_packet_msg[ic].acc_ref:platoon.u[2*iac];
                    cacc_control_packet_msg[ic].vel_ref = platoon.x[3*2*iac+1] + cacc_control_packet_msg[ic].acc_ref*controller.ht
                                                *(cacc_control_packet_msg[ic].acc_ref<0?cacc_state_packet_msg[iac+1].vel_gain_dec:(platoon.x[3*2*iac+1]<1.0?cacc_state_packet_msg[iac+1].vel_gain_low:cacc_state_packet_msg[iac+1].vel_gain));
                    cacc_control_packet_msg[ic].checksum = checksum;
                
                    // //Fake acceleration input
                    // cacc_control_packet_msg[ic].acc_ref = 1.0;
                    // cacc_control_packet_msg[ic].vel_ref = platoon.x[3*2*iac+1] + cacc_control_packet_msg[ic].acc_ref*0.5;//*controller.ht;
                    
                    // //Fake velocity input
                    // cacc_control_packet_msg[ic].acc_ref = 0.0;
                    // cacc_control_packet_msg[ic].vel_ref = 0.0;

                    control_packet_speaker[ic]->publish_cacc_control_packet_msg(cacc_control_packet_msg[ic]);                

                    // Current state
                    cacc_curr_state_packet_msg[2*iac+1] = cacc_state_packet_msg[2*iac+1];
                    cacc_curr_state_packet_msg[2*iac+1].distance = controller.xtau.elem(0)[3*(2*iac)+0];
                    cacc_curr_state_packet_msg[2*iac+1].speed = controller.xtau.elem(0)[3*(2*iac)+1];
                    cacc_curr_state_packet_msg[2*iac+1].acceleration = controller.xtau.elem(0)[3*(2*iac)+2];
                    curr_state_packet_speaker[2*iac+1]->publish_cacc_state_packet_msg(cacc_curr_state_packet_msg[2*iac+1]);
                
                    if(iac==0){
                        cacc_curr_state_packet_msg[2*iac] = cacc_state_packet_msg[2*iac]; 
                        cacc_curr_state_packet_msg[2*iac].speed = platoon.v;
                        cacc_curr_state_packet_msg[2*iac].acceleration = platoon.a;
                    }               
                    else{
                        cacc_curr_state_packet_msg[2*iac] = cacc_state_packet_msg[2*iac];
                        cacc_curr_state_packet_msg[2*iac].distance = controller.xtau.elem(0)[3*(2*iac)+0];
                        cacc_curr_state_packet_msg[2*iac].speed = controller.xtau.elem(0)[3*(2*iac)+1];
                        cacc_curr_state_packet_msg[2*iac].acceleration = controller.xtau.elem(0)[3*(2*iac)+2];
                    }
                    curr_state_packet_speaker[2*iac]->publish_cacc_state_packet_msg(cacc_curr_state_packet_msg[2*iac]);

                    // State error
                    cacc_state_error_packet_msg[2*iac+1] = cacc_state_packet_msg[2*iac+1];
                    cacc_state_error_packet_msg[2*iac+1].distance = controller.xtau.elem(0)[3*(2*iac)+0] - (platoon.Ds+platoon.thw[2*iac]*controller.xtau.elem(0)[3*(2*iac)+1]);
                    cacc_state_error_packet_msg[2*iac+1].speed = controller.xtau.elem(0)[3*(2*iac)+1] - (iac==0 ? platoon.v : controller.xtau.elem(0)[3*(2*iac-1)+1]);
                    cacc_state_error_packet_msg[2*iac+1].acceleration = controller.xtau.elem(0)[3*(2*iac)+2] - (iac==0 ? platoon.a : controller.xtau.elem(0)[3*(2*iac-1)+2]);
                    state_error_packet_speaker[2*iac+1]->publish_cacc_state_packet_msg(cacc_state_error_packet_msg[2*iac+1]);
                
                    if(iac==0){
                        cacc_state_error_packet_msg[2*iac] = cacc_state_packet_msg[2*iac]; 
                        cacc_state_error_packet_msg[2*iac].distance = 0.0;
                        cacc_state_error_packet_msg[2*iac].speed = 0.0;
                        cacc_state_error_packet_msg[2*iac].acceleration = 0.0;
                    }               
                    else{
                        cacc_state_error_packet_msg[2*iac] = cacc_state_packet_msg[2*iac];
                        cacc_state_error_packet_msg[2*iac].distance = controller.xtau.elem(0)[3*(2*iac-1)+0] - (platoon.Ds+platoon.thw[2*iac-1]*controller.xtau.elem(0)[3*(2*iac-1)+1]);
                        cacc_state_error_packet_msg[2*iac].speed = controller.xtau.elem(0)[3*(2*iac-1)+1] - controller.xtau.elem(0)[3*(2*iac-2)+1];
                        cacc_state_error_packet_msg[2*iac].acceleration = controller.xtau.elem(0)[3*(2*iac-1)+2] - controller.xtau.elem(0)[3*(2*iac-2)+2];
                    }
                    state_error_packet_speaker[2*iac]->publish_cacc_state_packet_msg(cacc_state_error_packet_msg[2*iac]);

                    // Predicted state
                    cacc_predicted_state_packet_msg[2*iac+1] = cacc_state_packet_msg[2*iac+1];
                    cacc_predicted_state_packet_msg[2*iac+1].distance = controller.xtau.elem(1)[3*(2*iac)+0];
                    cacc_predicted_state_packet_msg[2*iac+1].speed = controller.xtau.elem(1)[3*(2*iac)+1];
                    cacc_predicted_state_packet_msg[2*iac+1].acceleration = controller.xtau.elem(1)[3*(2*iac)+2];
                    predicted_state_packet_speaker[2*iac+1]->publish_cacc_state_packet_msg(cacc_predicted_state_packet_msg[2*iac+1]);
                
                    if(iac==0)
                        cacc_predicted_state_packet_msg[2*iac] = cacc_state_packet_msg[2*iac];                
                    else{
                        cacc_predicted_state_packet_msg[2*iac] = cacc_state_packet_msg[2*iac];
                        cacc_predicted_state_packet_msg[2*iac].distance = controller.xtau.elem(1)[3*(2*iac)+0];
                        cacc_predicted_state_packet_msg[2*iac].speed = controller.xtau.elem(1)[3*(2*iac)+1];
                        cacc_predicted_state_packet_msg[2*iac].acceleration = controller.xtau.elem(1)[3*(2*iac)+2];
                    }
                    predicted_state_packet_speaker[2*iac]->publish_cacc_state_packet_msg(cacc_predicted_state_packet_msg[2*iac]);
                    iac++;
                }
            }
            break;
        }

        //Publish the MPC parameters
        cacc_mpc_param_msg.Ds = platoon.Ds;
        cacc_mpc_param_msg.Dmin = platoon.Dmin;
        cacc_mpc_param_msg.umax = platoon.umax;
        cacc_mpc_param_msg.umin = platoon.umin;
        cacc_mpc_param_msg.sf0 = platoon.sf[0];
        cacc_mpc_param_msg.sf1 = platoon.sf[1];
        cacc_mpc_param_msg.sf2 = platoon.sf[2];
        cacc_mpc_param_msg.q0 = platoon.q[0];
        cacc_mpc_param_msg.q1 = platoon.q[1];
        cacc_mpc_param_msg.q2 = platoon.q[2];
        cacc_mpc_param_msg.r = platoon.r[0];
        cacc_mpc_param_msg.su = platoon.su[0];
        cacc_mpc_param_msg.sd = platoon.sd[0];
        
        cacc_mpc_param_msg.tf = controller.tf;
        cacc_mpc_param_msg.ht = controller.ht;
        cacc_mpc_param_msg.dv = controller.dv;
        cacc_mpc_param_msg.zeta = controller.zeta;
        cacc_mpc_param_msg.kmax = controller.kmax;
        
        cacc_mpc_param_pub.publish(cacc_mpc_param_msg);

        //Publish the MPC state
        cacc_mpc_state_msg.F = controller.hutau1.norm();
        cacc_mpc_state_pub.publish(cacc_mpc_state_msg);

        //Pulbish prediction model parameters
        for(int ic = 0; ic < NCAR-1; ic++){
            if(prarx[ic] != NULL){
                prarx[ic]->publishParams();
            }
        }

        if(Flag_csv_output){
            myfile <<ros::Time::now().toSec()-time_exp_start<<","<<platoon.x[0]<<endl;   
            // myfile <<ros::Time::now().toSec()-time_exp_start<<","<<cacc_control_packet_msg[1].vel_ref<<","<<platoon.x[1]<<","<<cacc_control_packet_msg[1].acc_ref<<","<<controller.ht<<","<<(cacc_control_packet_msg[1].acc_ref<0?cacc_state_packet_msg[1].vel_gain_dec:(platoon.x[1]<1.0?cacc_state_packet_msg[1].vel_gain_low:cacc_state_packet_msg[1].vel_gain))<<endl;   
        }

        // //print out
        // std::cout<<"///////////////////////////////////////////////"<<std::endl;
        // for(int ic = 0; ic < 2*NCAR-1; ic++){
        //     std::cout<<"------Car "<<ic<<"-----------"<<std::endl
        //             <<"x0 = "<<platoon.x[3*ic+0]<<std::endl
        //             <<"x1 = "<<platoon.x[3*ic+1]<<std::endl
        //             <<"x2 = "<<platoon.x[3*ic+2]<<std::endl
        //             <<"u = "<<platoon.u[ic]<<std::endl
        //             <<"--------------------------"<<std::endl;

        // }

        bool com_flag = true;
        for(int ic = 0; ic < 2*NCAR-1; ic++){
            if(std::isnan(platoon.u[ic]))
                com_flag = false;
        }

        if(!com_flag) controller.init(&platoon);


        checksum++;

        loop_rate.sleep();
    }

    
    //Delete pointers
    for(int i=0; i<NCARMAX; i++){
        if(state_packet_listener[i] != NULL){
            delete state_packet_listener[i];
            state_packet_listener[i] = NULL;
        }
        if(control_packet_speaker[i] != NULL){
            delete control_packet_speaker[i];
            control_packet_speaker[i] = NULL;
        }
        if(predicted_state_packet_speaker[i] != NULL){
            delete predicted_state_packet_speaker[i];
            predicted_state_packet_speaker[i] = NULL;
        }
        if(curr_state_packet_speaker[i] != NULL){
            delete curr_state_packet_speaker[i];
            curr_state_packet_speaker[i] = NULL;
        }
    }

    for(int i=0; i<NCAR-1; i++){
        delete prarx[i];
        prarx[i] = NULL;
    }
    
    return 0;
}

void MpcParamConfigCallback(cacc_controller::MpcParamConfig &config, uint32_t level){
    mpc_parameter.Ds = config.ds;
    mpc_parameter.Dmin = config.dmin;

    mpc_parameter.umax = config.umax;
    mpc_parameter.umin = -1 * config.umin;
    
    mpc_parameter.q[0] = config.q0;
    mpc_parameter.q[1] = config.q1;
    mpc_parameter.q[2] = config.q2;
    mpc_parameter.r = config.r;
    mpc_parameter.sf = config.sf;
    mpc_parameter.su = config.su;
    mpc_parameter.sd = config.sd;

    platoon.set_param(mpc_parameter);

    vel_ref = config.vel_ref;
};
