#include <string>
#include <ros/ros.h>
#include <platoon.h>
#include <packetHandler.h>
#include <FrenetCoordinate.h>
#include <Course.h>

#define NCARMAX 10
#define FRENET

int id[NCARMAX];
bool manual[NCARMAX];
int manual_sum = 0;
SensorPacketListener* sensor_packet_listener[NCARMAX];
StatePacketSpeaker*   state_packet_speaker[NCARMAX];
cacc_msgs::CaccSensorPacket cacc_sensor_packet_msg[NCARMAX];
cacc_msgs::CaccStatePacket cacc_state_packet_msg[NCARMAX];

RTCLib::FrenetCoordinate2D lane_center;
RTCLib::CacheToFrenet cache_to_g;
double length;    
CarManagement::Course* course;
std::string course_file;
bool direction;
std::string control_type;

bool flag_cutin = false;


int main(int argc, char** argv)
{
    ros::init(argc, argv, "state_estimator");

    //Initialize pointers
    for(int i=0; i<NCARMAX; i++){
        sensor_packet_listener[i] = NULL;
        state_packet_speaker[i] = NULL;
    }

    //Node handles
    ros::NodeHandle nh;
    ros::NodeHandle private_nh("~");

    PositionType position_type;
    std::string position_type_str;

    int ncar; //In mode 1: 0, 1, 2, ..., N; mode 2: 1, 2, ..., N
    private_nh.param<int>("number_of_car", ncar, 2);
    private_nh.param<std::string>("position_type_str", position_type_str, "detection");
    private_nh.param<std::string>("control_type", control_type, "default");
    private_nh.param<bool>("flag_cutin", flag_cutin, "false");

    float distance_radar_gain;
    private_nh.param<float>("distance_radar_gain", distance_radar_gain, 1.0f);
    
    //Set course
    private_nh.param<std::string>("course_file", course_file, "course.txt");
    private_nh.param<bool>("direction", direction, true);
    try{
    #ifdef FRENET
        lane_center.LoadPathFromCSV(course_file, true);
        lane_center = lane_center.ResampleConservative(0.01);
        length = lane_center.length;
        ROS_INFO("length: %f", length);
    #else
        course = new CarManagement::Course(course_file);
        length = course->length;
    #endif
    }
    catch(std::exception e){
        ROS_ERROR("Exception occured during loading course file.");
    #ifndef FRENET
        delete course;
    #endif
        ros::shutdown();
    }

    //Get mode
    if(position_type_str == "detection"){
        position_type = DETECTION;
        ROS_INFO("Position_type has been set as detection mode.");
    }
    else if(position_type_str == "localization"){
        position_type = LOCALIZATION;
         ROS_INFO("Position_type has been set as localization mode.");
    }
    else if(position_type_str == "combined"){
        position_type = COMBINED;
         ROS_INFO("Position_type has been set as combined mode.");
    }
    else{
        ROS_ERROR("Position_type has been set with wrong type.");
        return -1;
    }

    //Get the number of car
    if(ncar > NCARMAX/2){
        ncar = NCARMAX/2;
        ROS_ERROR("The number of car has not to be exceed the maximum number, %d. ", ncar);
    }
    else{
        switch(position_type){
        case DETECTION:
            ROS_INFO("State estimator type has been set DETECTION: using distance and position of only automated cars.");
            if(ncar < 1){
                ROS_ERROR("The number of car has to be bigger than 0.");
            return -1;
            }
            break;
        case LOCALIZATION:
            ROS_INFO("State estimator type has been set LOCALIZATION: using localization of whole cars.");
            if(ncar < 2){
                ROS_ERROR("The number of car has to be bigger than 1.");
                return -1;
            }
            break;
        case COMBINED:
            ROS_INFO("State estimator type has been set COMBINED: using both localization and detection of whole cars.");
            if(ncar < 1){
                ROS_ERROR("The number of car has to be bigger than 0.");
                return -1;
            }
            break;
        default:
            ROS_ERROR("The type has been set with wrong number.");
            return -1;
        }
    }

    //In case of detection, check the manual flag (all cars should be automated)
    if(position_type == DETECTION){
        for(int ic = 0; ic < ncar; ic++){
            //Get the flag
            private_nh.param<bool>("manual_"+std::to_string(ic), manual[ic], false);
            if(manual[ic]){
                ROS_ERROR("The car must be an automated car.");
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
                ROS_ERROR("The leading car must be a manual car.");
                return -1;
            } 
            //First car (Car 1) must be automated
            if(ic == 1 && manual[ic]){
                ROS_ERROR("Car 1 must be an automated car.");
                return -1;
            } 
            //Last car (Car N) must be automated
            if(ic == ncar-1 && manual[ic]){
                ROS_ERROR("The last car must be an automated car.");
                return -1;
            } 
            //Front and rear of a manual car must be automated cars
            if(ic > 0 && manual[ic] && manual[ic-1]){
                ROS_ERROR("Manual cars cannot be continuous.");
                return -1;
            }
            if(manual[ic])  manual_sum++;
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
                ROS_ERROR("The last car must be an automated car.");
                return -1;
            } 
            //Front and rear of a manual car must be automated cars
            if(ic > 0 && manual[ic] && manual[ic-1]){
                ROS_ERROR("Manual cars cannot be continuous.");
                return -1;
            }
            if(manual[ic])  manual_sum++;
        }
    }

    //Set up id, listener, and speaker
    int iac = 0;
    switch(position_type){
    case DETECTION: //Create ncar of listener and 2*ncar of speaker
        for(int ic = 0; ic < ncar; ic++){
            private_nh.param<int>("id_"+std::to_string(ic+1), id[ic*2+1], ic+1);
            sensor_packet_listener[ic] = new SensorPacketListener(ic+1, id[ic*2+1]);
            state_packet_speaker[ic*2+1] = new StatePacketSpeaker(ic*2+1, id[ic*2+1], control_type);

            id[ic*2] = 500 + id[ic*2+1];
            state_packet_speaker[ic*2] = new StatePacketSpeaker(ic*2, id[ic*2], control_type);
        }
        break;
    case LOCALIZATION: //Create ncar of listener and 2*(ncar-manual_sum) of speaker
        for(int ic = 0; ic < ncar; ic++){
            if(!manual[ic]){
                private_nh.param<int>("id_"+std::to_string(ic), id[iac*2+1], ic);
                sensor_packet_listener[ic] = new SensorPacketListener(ic, id[iac*2+1]);
                state_packet_speaker[iac*2+1] = new StatePacketSpeaker(iac*2+1, id[iac*2+1], control_type);

                if(manual[ic-1]){
                    private_nh.param<int>("id_"+std::to_string(ic-1), id[iac*2], ic-1);
                    sensor_packet_listener[ic-1] = new SensorPacketListener(ic-1, id[iac*2]);
                }
                else{
                    id[iac*2] = 500 + id[iac*2+1];
                }
                state_packet_speaker[iac*2] = new StatePacketSpeaker(iac*2, id[iac*2], control_type);

                iac++;
            }
        }
        break; 
    case COMBINED: //Create ncar of listener and 2*(ncar-manual_sum) of speaker
        for(int ic = 0; ic < ncar; ic++){
            if(!manual[ic]){
                private_nh.param<int>("id_"+std::to_string(ic), id[iac*2+1], ic);
                sensor_packet_listener[ic] = new SensorPacketListener(ic, id[iac*2+1]);
                state_packet_speaker[iac*2+1] = new StatePacketSpeaker(iac*2+1, id[iac*2+1], control_type);

                if(manual[ic-1]){
                    private_nh.param<int>("id_"+std::to_string(ic-1), id[iac*2], ic-1);
                    sensor_packet_listener[ic-1] = new SensorPacketListener(ic-1, id[iac*2]);
                }
                else{
                    id[iac*2] = 500 + id[iac*2+1];
                }
                state_packet_speaker[iac*2] = new StatePacketSpeaker(iac*2, id[iac*2], control_type);

                iac++;
            }
        }
        break;   
    }

    ros::Rate loop_rate(100);
    ros::Time t_now = ros::Time::now(), t_prev = ros::Time::now();
    ros::Duration time_diff;
    double dt;

    double range[ncar];
    double range_rate[ncar];
    double speed[ncar];
    for(int ic = 0; ic < ncar; ic++){
        range[ic] = 50.0;
        range_rate[ic] = 0.0;
        speed[ic] = 0.0;
    }

    while(ros::ok()){
        //Subscribe
        ros::spinOnce();

        //Time difference
        t_now = ros::Time::now();
        time_diff = t_now - t_prev;
        dt = time_diff.toSec();
        //if(dt == 0) dt = 0.0001;
        if(dt >= 0.005){
            //Gather the msgs
            for(int ic = 0; ic < ncar; ic++){
                sensor_packet_listener[ic]->get_cacc_sensor_packet_msg(&cacc_sensor_packet_msg[ic]);
                if(position_type == LOCALIZATION && manual[ic] != cacc_sensor_packet_msg[ic].manual){
                    if (!flag_cutin)
                    ROS_ERROR("Manual flag on the sensor packet is not matched with the flag set in the estimator.");
                }
            }

            //Calculate the order (TBD)
            
            //Pack the states
            switch(position_type){
            case DETECTION:
                //Automated
                for(int iac = 0; iac < ncar; iac++){
                    int ic = 2*iac+1;
                    cacc_state_packet_msg[ic].id = state_packet_speaker[ic]->id;
                    cacc_state_packet_msg[ic].manual = false;
                    //Determine the activation status (TBD)
                    cacc_state_packet_msg[ic].activated = false;
                    //////////////////////////////////////////
                    cacc_state_packet_msg[ic].thw = cacc_sensor_packet_msg[(ic-1)/2].thw;
                    cacc_state_packet_msg[ic].alpha = cacc_sensor_packet_msg[(ic-1)/2].alpha;
                    cacc_state_packet_msg[ic].beta = cacc_sensor_packet_msg[(ic-1)/2].beta;
                    cacc_state_packet_msg[ic].vel_gain = cacc_sensor_packet_msg[(ic-1)/2].vel_gain;
                    cacc_state_packet_msg[ic].vel_gain_low = cacc_sensor_packet_msg[(ic-1)/2].vel_gain_low;
                    cacc_state_packet_msg[ic].vel_gain_dec = cacc_sensor_packet_msg[(ic-1)/2].vel_gain_dec;
                    cacc_state_packet_msg[ic].distance = 0.9*cacc_state_packet_msg[ic].distance + 0.1*cacc_sensor_packet_msg[(ic-1)/2].front_distance;
                    cacc_state_packet_msg[ic].speed = 0.9*cacc_state_packet_msg[ic].speed + 0.1*cacc_sensor_packet_msg[(ic-1)/2].speed;
                    cacc_state_packet_msg[ic].acceleration = 0.9*cacc_state_packet_msg[ic].acceleration + 0.1*cacc_sensor_packet_msg[(ic-1)/2].acceleration;
                }
                //Human-driven (ghost except the leading car)
                for(int iac = 0; iac < 2*ncar; iac++){
                    int ic = 2*iac;
                    cacc_state_packet_msg[ic].id = state_packet_speaker[ic]->id;
                    cacc_state_packet_msg[ic].manual = true;
                    //Determine the activation status (TBD)
                    cacc_state_packet_msg[ic].activated = false;
                    //////////////////////////////////////////
                    cacc_state_packet_msg[ic].thw = 2.0;
                    cacc_state_packet_msg[ic].alpha = 10.0;
                    cacc_state_packet_msg[ic].beta = 10.0;
                    cacc_state_packet_msg[ic].vel_gain = 0;
                    cacc_state_packet_msg[ic].vel_gain_low = 0;
                    cacc_state_packet_msg[ic].vel_gain_dec = 0;
                    cacc_state_packet_msg[ic].distance = (ic==0?0:0.9*cacc_state_packet_msg[ic].distance + 0.1*(cacc_state_packet_msg[ic].activated?cacc_sensor_packet_msg[ic/2-1].rear_distance:0));
                    
                    range_rate[iac] = 0.95*range_rate[iac] + 0.05*(cacc_state_packet_msg[ic+1].distance - range[iac])/dt;
                    range[iac] = cacc_state_packet_msg[ic+1].distance;

                    cacc_state_packet_msg[ic].speed = ic==0?0.95*cacc_state_packet_msg[ic].speed + 0.05*(cacc_state_packet_msg[ic+1].speed + range_rate[iac]):cacc_state_packet_msg[ic-1].speed; 
                    cacc_state_packet_msg[ic].acceleration = ic==0?0.95*cacc_state_packet_msg[ic].acceleration + 0.05*(cacc_state_packet_msg[ic].speed - speed[iac])/dt:cacc_state_packet_msg[ic-1].acceleration;
                    speed[iac] = cacc_state_packet_msg[ic].speed;
                }
                break;
            case LOCALIZATION:
                iac = 0;
                for(int ic = 0; ic < ncar; ic++){
                    if(!manual[ic]){ //Automated
                        cacc_state_packet_msg[2*iac+1].id = cacc_sensor_packet_msg[ic].id;
                        cacc_state_packet_msg[2*iac+1].manual = false;
                        cacc_state_packet_msg[2*iac+1].activated = false;
                        //cacc_state_packet_msg[2*iac+1].order = iac+1;
                        cacc_state_packet_msg[2*iac+1].thw = cacc_sensor_packet_msg[ic].thw;
                        cacc_state_packet_msg[2*iac+1].alpha = cacc_sensor_packet_msg[ic].alpha;
                        cacc_state_packet_msg[2*iac+1].beta = cacc_sensor_packet_msg[ic].beta;
                        cacc_state_packet_msg[2*iac+1].vel_gain = cacc_sensor_packet_msg[ic].vel_gain;
                        cacc_state_packet_msg[2*iac+1].vel_gain_low = cacc_sensor_packet_msg[ic].vel_gain_low;
                        cacc_state_packet_msg[2*iac+1].vel_gain_dec = cacc_sensor_packet_msg[ic].vel_gain_dec;
                        double tmp_distance = (cacc_sensor_packet_msg[ic-1].u-cacc_sensor_packet_msg[ic-1].sensor2rearbumper) - (cacc_sensor_packet_msg[ic].u+cacc_sensor_packet_msg[ic].sensor2frontbumper);
                        if(direction && tmp_distance < 0){
                            tmp_distance += length;
                        }
                        else if(!direction){
                            if(tmp_distance > 0)
                                tmp_distance -= length;
                            tmp_distance *= -1;
                        }
                        //tmp_distance *= 100;
                        cacc_state_packet_msg[2*iac+1].distance = 0.9*cacc_state_packet_msg[2*iac+1].distance + 0.1*tmp_distance;
                        cacc_state_packet_msg[2*iac+1].speed = 0.9*cacc_state_packet_msg[2*iac+1].speed + 0.1*cacc_sensor_packet_msg[ic].speed;
                        cacc_state_packet_msg[2*iac+1].acceleration = 0.9*cacc_state_packet_msg[2*iac+1].acceleration + 0.1*cacc_sensor_packet_msg[ic].acceleration;
                        
                        if(manual[ic-1]){ //Human-driven
                            cacc_state_packet_msg[2*iac].id = cacc_sensor_packet_msg[ic-1].id;
                            cacc_state_packet_msg[2*iac].manual = true;
                            cacc_state_packet_msg[2*iac].activated = true;
                            //cacc_state_packet_msg[2*iac].order = 2*iac;
                            cacc_state_packet_msg[2*iac].thw = cacc_sensor_packet_msg[ic-1].thw;
                            cacc_state_packet_msg[2*iac].alpha = cacc_sensor_packet_msg[ic-1].alpha;
                            cacc_state_packet_msg[2*iac].beta = cacc_sensor_packet_msg[ic-1].beta;
                            double tmp_distance = (ic-1==0?0:(cacc_sensor_packet_msg[ic-2].u-cacc_sensor_packet_msg[ic-2].sensor2rearbumper) - (cacc_sensor_packet_msg[ic-1].u+cacc_sensor_packet_msg[ic-1].sensor2frontbumper));
                            if(direction && tmp_distance < 0){
                                tmp_distance += length;
                            }
                            else if(!direction){
                                if(tmp_distance > 0)
                                    tmp_distance -= length;
                                tmp_distance *= -1;
                            }
                            //tmp_distance *= 100;
                            cacc_state_packet_msg[2*iac].distance = 0.9*cacc_state_packet_msg[2*iac].distance + 0.1*tmp_distance;
                            cacc_state_packet_msg[2*iac].speed = 0.9*cacc_state_packet_msg[2*iac].speed + 0.1*cacc_sensor_packet_msg[ic-1].speed;
                            cacc_state_packet_msg[2*iac].acceleration = 0.9*cacc_state_packet_msg[2*iac].acceleration + 0.1*cacc_sensor_packet_msg[ic-1].acceleration;
                        }

                        else{ //Ghost manual
                            cacc_state_packet_msg[2*iac].id = id[2*iac];
                            cacc_state_packet_msg[2*iac].manual = true;
                            cacc_state_packet_msg[2*iac].activated = false;
                            //cacc_state_packet_msg[2*iac].order = 2*iac;
                            cacc_state_packet_msg[2*iac].thw = 0;
                            cacc_state_packet_msg[2*iac].alpha = 10.0;
                            cacc_state_packet_msg[2*iac].beta = 10.0;
                            cacc_state_packet_msg[2*iac].distance = 0;
                            cacc_state_packet_msg[2*iac].speed = cacc_sensor_packet_msg[ic-1].speed;
                            cacc_state_packet_msg[2*iac].acceleration = cacc_sensor_packet_msg[ic-1].acceleration;
                        }

                        iac ++;
                    }
                    
                }
                break;
            case COMBINED:
                iac = 0;
                for(int ic = 0; ic < ncar; ic++){
                    if(!manual[ic]){ //Automated
                        cacc_state_packet_msg[2*iac+1].id = cacc_sensor_packet_msg[ic].id;
                        cacc_state_packet_msg[2*iac+1].manual = false;
                        cacc_state_packet_msg[2*iac+1].activated = false;
                        //cacc_state_packet_msg[2*iac+1].order = iac+1;
                        cacc_state_packet_msg[2*iac+1].thw = cacc_sensor_packet_msg[ic].thw;
                        cacc_state_packet_msg[2*iac+1].alpha = cacc_sensor_packet_msg[ic].alpha;
                        cacc_state_packet_msg[2*iac+1].beta = cacc_sensor_packet_msg[ic].beta;
                        cacc_state_packet_msg[2*iac+1].vel_gain = cacc_sensor_packet_msg[ic].vel_gain;
                        cacc_state_packet_msg[2*iac+1].vel_gain_low = cacc_sensor_packet_msg[ic].vel_gain_low;
                        cacc_state_packet_msg[2*iac+1].vel_gain_dec = cacc_sensor_packet_msg[ic].vel_gain_dec;
                        double gps_distance = 0.9*cacc_state_packet_msg[2*iac+1].distance + 0.1*((cacc_sensor_packet_msg[ic-1].u-cacc_sensor_packet_msg[ic-1].sensor2rearbumper) - (cacc_sensor_packet_msg[ic].u+cacc_sensor_packet_msg[ic].sensor2frontbumper));
                        double radar_distance = 0.9*cacc_state_packet_msg[2*iac+1].distance + 0.1*cacc_sensor_packet_msg[ic].front_distance;
                        cacc_state_packet_msg[2*iac+1].distance = (1-distance_radar_gain)*gps_distance + distance_radar_gain*radar_distance;
                        cacc_state_packet_msg[2*iac+1].speed = 0.9*cacc_state_packet_msg[2*iac+1].speed + 0.1*cacc_sensor_packet_msg[ic].speed;
                        cacc_state_packet_msg[2*iac+1].acceleration = 0.9*cacc_state_packet_msg[2*iac+1].acceleration + 0.1*cacc_sensor_packet_msg[ic].acceleration;
                        
                        if(manual[ic-1]){ //Human-driven
                            cacc_state_packet_msg[2*iac].id = cacc_sensor_packet_msg[ic-1].id;
                            cacc_state_packet_msg[2*iac].manual = true;
                            cacc_state_packet_msg[2*iac].activated = true;
                            //cacc_state_packet_msg[2*iac].order = 2*iac;
                            cacc_state_packet_msg[2*iac].thw = cacc_sensor_packet_msg[ic-1].thw;
                            cacc_state_packet_msg[2*iac].alpha = cacc_sensor_packet_msg[ic-1].alpha;
                            cacc_state_packet_msg[2*iac].beta = cacc_sensor_packet_msg[ic-1].beta;
                            double tmp_distance = (ic-1==0?0:(cacc_sensor_packet_msg[ic-2].u-cacc_sensor_packet_msg[ic-2].sensor2rearbumper) - (cacc_sensor_packet_msg[ic-1].u+cacc_sensor_packet_msg[ic-1].sensor2frontbumper));
                            cacc_state_packet_msg[2*iac].distance = 0.9*cacc_state_packet_msg[2*iac].distance + 0.1*tmp_distance;
                            cacc_state_packet_msg[2*iac].speed = 0.9*cacc_state_packet_msg[2*iac].speed + 0.1*cacc_sensor_packet_msg[ic-1].speed;
                            cacc_state_packet_msg[2*iac].acceleration = 0.9*cacc_state_packet_msg[2*iac].acceleration + 0.1*cacc_sensor_packet_msg[ic-1].acceleration;
                        }

                        else{ //Ghost manual
                            cacc_state_packet_msg[2*iac].id = id[2*iac];
                            cacc_state_packet_msg[2*iac].manual = true;
                            cacc_state_packet_msg[2*iac].activated = false;
                            //cacc_state_packet_msg[2*iac].order = 2*iac;
                            cacc_state_packet_msg[2*iac].thw = 0;
                            cacc_state_packet_msg[2*iac].alpha = 10.0;
                            cacc_state_packet_msg[2*iac].beta = 10.0;
                            cacc_state_packet_msg[2*iac].distance = 0;
                            if(iac == 0){
                                range_rate[0] = 0.95*range_rate[0] + 0.05*(cacc_state_packet_msg[1].distance - range[0])/dt;
                                range[0] = cacc_state_packet_msg[1].distance;

                                cacc_state_packet_msg[0].speed = 0.95*cacc_state_packet_msg[0].speed + 0.05*(cacc_state_packet_msg[1].speed + range_rate[0]); 
                                cacc_state_packet_msg[0].acceleration = 0.95*cacc_state_packet_msg[0].acceleration + 0.05*(cacc_state_packet_msg[0].speed - speed[0])/dt;
                                speed[0] = cacc_state_packet_msg[0].speed;
                            }
                            else{
                                cacc_state_packet_msg[2*iac].speed = cacc_sensor_packet_msg[ic-1].speed;
                                cacc_state_packet_msg[2*iac].acceleration = cacc_sensor_packet_msg[ic-1].acceleration;
                            }
                        }

                        iac ++;
                    }
                    
                }
                break;
            }

            //for cutin
            if (flag_cutin)
            {
                if (-0.2 < cacc_sensor_packet_msg[3].v && cacc_sensor_packet_msg[3].v < 0.1)
                    cacc_state_packet_msg[3].distance = 13.808 - cacc_state_packet_msg[5].distance - 0.52;
            }

            //Publish
            switch(position_type){
            case DETECTION:
                for(int ic = 0; ic < 2*ncar; ic++){
                    state_packet_speaker[ic]->publish_cacc_state_packet_msg(cacc_state_packet_msg[ic]);
                }
                break;
            case LOCALIZATION:
                for(int is = 0; is < 2*(ncar-manual_sum); is++){
                    state_packet_speaker[is]->publish_cacc_state_packet_msg(cacc_state_packet_msg[is]);
                }
                break;
            case COMBINED:
                for(int is = 0; is < 2*(ncar-manual_sum); is++){
                    state_packet_speaker[is]->publish_cacc_state_packet_msg(cacc_state_packet_msg[is]);
                }
                break;
            }
            t_prev = t_now;
        }
        
        loop_rate.sleep();
    }

    
    //Delete pointers
    for(int i=0; i<NCARMAX; i++){
        if(sensor_packet_listener[i] != NULL){
            delete sensor_packet_listener[i];
            sensor_packet_listener[i] = NULL;
        }
        if(state_packet_speaker[i] != NULL){
            delete state_packet_speaker[i];
            state_packet_speaker[i] = NULL;
        }
    }
    
    return 0;
}