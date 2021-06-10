#ifndef __OMNI_AGENT__H
#define __OMNI_AGENT__H 

#include "enviro.h"

using namespace enviro;

class FindWall : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) {
            std:: cout << "Find Wall : \n ";


            std:: cout << "Initial Position : \n ";
            
         }
        void during()
        {
    
            if(sensor_value(2)>11.0){
                omni_track_velocity(-5,0);
            }else if(sensor_value(3)>11.0){
                omni_track_velocity(0,-5);
            }else {
                omni_track_velocity(0,0);
                emit(Event("rotate"));
                }

        }
        void exit(const Event &e) {}

    };
    class GoDown : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) {
            std:: cout << "Entering Down\n";
            dist = sensor_value(2);
            //std:: cout << "Initial left: "<<sensor_value(2)<< "\n";
         }
        void during()
        {
            //std:: cout << "Right: "<<sensor_value(0)<< " Up: "<< sensor_value(3) << " Left: " << sensor_value(2) << " Down: "<<sensor_value(1)<<"\n ";
            if(sensor_value(1)>11.0){
                omni_track_velocity(0,5);
            }else{
                omni_track_velocity(0,0);
                emit(Event("righty"));
            }

            if(sensor_reflection_type(0) == "EndPoint" ||sensor_reflection_type(1) == "EndPoint"||sensor_reflection_type(2) == "EndPoint" ||sensor_reflection_type(3) == "EndPoint"){ //Check all primary sensor if target is in sight, regardless of direction
                omni_track_velocity(0,0);
                emit(Event("goaly"));
            }
            
            if(sensor_value(2)>sensor_value(6)+2.0){ //note: the +2.0 is due to the sensor sometimes not being accurate;
                omni_track_velocity(0,0);
                std:: cout << "Down Holey \n";
                emit(Event("holey"));
            }
            
        }
        void exit(const Event &e) {}
        double dist;
    };
    class GoRight : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) {
            std:: cout << "Entering Right\n";
         }
        void during()
        {
            //std:: cout << "Right: "<<sensor_value(0)<< " Up: "<< sensor_value(3) << " Left: " << sensor_value(2) << " Down: "<<sensor_value(1)<<"\n ";
            //std::cout << sensor_reflection_type(3) << "\n";
            if(sensor_value(0)>11.0){
                omni_track_velocity(5,0);
            }else{
                omni_track_velocity(0,0);
                emit(Event("uppy"));
            }

            if(sensor_reflection_type(0) == "EndPoint" ||sensor_reflection_type(1) == "EndPoint"||sensor_reflection_type(2) == "EndPoint" ||sensor_reflection_type(3) == "EndPoint"){ //Check all primary sensor if target is in sight, regardless of direction
                omni_track_velocity(0,0);
                emit(Event("goaly"));
            }

                        
            if(sensor_value(1)>sensor_value(5)+2.0){//note: the +2.0 is due to the sensor sometimes not being accurate;
                omni_track_velocity(0,0);
                emit(Event("holey"));
            }

            
        }
        void exit(const Event &e) {}

    };
    class GoUp : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) {
            std:: cout << "Entering Up\n";
            dist = sensor_value(0);
         }
        void during()
        {
            //std:: cout << "Right: "<<sensor_value(0)<< " Up: "<< sensor_value(3) << " Left: " << sensor_value(2) << " Down: "<<sensor_value(1)<<"\n ";
            if(sensor_value(3)>11.0 ){
                omni_track_velocity(0,-5);
            }else{
                omni_track_velocity(0,0);
                emit(Event("lefty"));
            }
            
            if(sensor_reflection_type(0) == "EndPoint" || sensor_reflection_type(1) == "EndPoint"||sensor_reflection_type(2) == "EndPoint" ||sensor_reflection_type(3) == "EndPoint"){ //Check all primary sensor if target is in sight, regardless of direction
                omni_track_velocity(0,0);
                emit(Event("goaly"));
            }
            if(sensor_value(0)>sensor_value(4)+2.0){//note: the +2.0 is due to the sensor sometimes not being accurate;
                omni_track_velocity(0,0);
                emit(Event("holey"));
            }

            
        }
        void exit(const Event &e) {}
        double dist;

    };

    class GoLeft : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) {
            std:: cout << "Entering Left\n";
         }
        void during()
        {
            //std:: cout << "Right: "<<sensor_value(0)<< " Up: "<< sensor_value(3) << " Left: " << sensor_value(2) << " Down: "<<sensor_value(1)<<"\n ";

            if(sensor_value(2)>11.0 ){
                omni_track_velocity(-5,0);
            }else{
                omni_track_velocity(0,0);
                emit(Event("downy"));
            }

            
            if(sensor_reflection_type(0) == "EndPoint" ||sensor_reflection_type(1) == "EndPoint"||sensor_reflection_type(2) == "EndPoint" ||sensor_reflection_type(3) == "EndPoint"){ //Check all primary sensor if target is in sight, regardless of direction
                omni_track_velocity(0,0);
                emit(Event("goaly"));
            }

            if(sensor_value(3)>sensor_value(7)+2.0){ //note: the +2.0 is due to the sensor sometimes not being accurate;
                omni_track_velocity(0,0);
                emit(Event("holey"));
            }

            
        }
        void exit(const Event &e) {}

    };

    
    class Hole : public State, public AgentInterface // This state is entered anytime the robot senses a hole.
    {
    public:
        void entry(const Event &e) {
            //when entering this state, we want to know which primary sensor is not the same as the secondary sensor. The sensor that is off means the hole is on the side of the sensor
            std:: cout << "Entering Hole\n";
            std:: cout << "Recording initial sensor distances\n";
            past = false;
            right0 = sensor_value(0);
            right4 = sensor_value(4);
            down1 = sensor_value(1);
            down5 = sensor_value(5);
            left2 = sensor_value(2);
            left6 = sensor_value(6);
            up3 = sensor_value(3);
            up7 = sensor_value(7);
        }

            
        void during()
        {

            if(right0 >right4+2.0){ //if the hole is to the right of the robot, note: the +2.0 is due to the sensor sometimes not being accurate;
                std::cout <<"Inside Right\n";
                if(sensor_value(1) < down1 + 13.0 && past == false){ //move the robot past the hole 
                    omni_track_velocity(0,-5);
                }else if(sensor_value(2) < left2+47.0){
                    past = true;
                    omni_track_velocity(5,0);
                }else { // once robot is past the hole, determine if the next wall is within 11.0,reset past flag
                    if(sensor_value(1)<11.0){
                        past = false;
                        emit(Event("righty"));
                    }else{
                        omni_track_velocity(0,0);
                        past = false;
                        emit(Event("downy"));
                    }
                }
            

            }
            if(down1 >down5+2.0){ //if the hole is below the robot
                std::cout <<"Inside down\n";
                if(sensor_value(2) < left2 + 13.0 && past == false){
                    omni_track_velocity(5,0);
                }else if(sensor_value(3) < up3+47.0){
                    past = true;
                    omni_track_velocity(0,5);
                }else{
                    if(sensor_value(2)<11.0){
                        emit(Event("downy"));
                        past = false;
                    }
                    omni_track_velocity(0,0);
                    past = false;
                    emit(Event("lefty"));
                }

            }
            if(left2 > left6+2.0){ //if the hole is to the left of the robot
                std::cout <<"Inside left\n";
                if(sensor_value(3) < up3 + 13.0 && past == false){
                    omni_track_velocity(0,5);
                }else if(sensor_value(0) < right0+47.0){
                    past = true;
                    omni_track_velocity(-5,0);
                }else{
                    if(sensor_value(3)<11.0){
                        emit(Event("lefty"));
                        past = false;
                    }
                    omni_track_velocity(0,0);
                    past = false;
                    emit(Event("uppy"));
                }

            }
            if(up3 > up7+2.0){ //if the hole is above the robot
                std::cout <<"Inside up\n";
                if(sensor_value(0) < right0 + 13.0 && past == false){
                    omni_track_velocity(-5,0);
                }else if(sensor_value(1) < down1+47.0){
                    past = true;
                    omni_track_velocity(0,-5);
                }else{
                    if(sensor_value(0)<11.0){
                        emit(Event("uppy"));
                        past = false;
                    }
                    omni_track_velocity(0,0);
                    past = false;
                    emit(Event("righty"));
                }

            }
            
        }
        void exit(const Event &e) {}
        bool past = false;
        double right0;
        double right4;
        double down1;
        double down5;
        double left2;
        double left6;
        double up3;
        double up7;


    };

    
    class Goal : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) {
            std:: cout << "Entering Goal\n";
            if(sensor_reflection_type(0) == "EndPoint"){ //if right sensor sees the endpoint
                rightdist = sensor_value(0);
            }else if(sensor_reflection_type(1) == "EndPoint"){//endpoint is below robot
                downdist= sensor_value(1);
            }else if(sensor_reflection_type(3) == "EndPoint"){//endpoint is above robot
                updist =sensor_value(3);
            }else if(sensor_reflection_type(2)== "EndPoint"){
                leftdist = sensor_value(2);

            }
        }
        
        void during()
        {    
            
            if(updist>0){
                if(sensor_value(3)>11.0){
                    omni_move_toward(x(),y()-updist,0.2);
                }else{
                    omni_track_velocity(0,0);
                }
              
            }else if (rightdist>0){
                if(sensor_value(0)>11.0){
                    omni_move_toward(x()-rightdist,y(),0.2);
                }else{
                    omni_track_velocity(0,0);
                }

            }else if(downdist>0){
                if(sensor_value(1)>11.0){
                    omni_move_toward(x(),y()-downdist,0.2);
                }else{
                    omni_track_velocity(0,0);
                }
            }else if(leftdist>0){
                if(sensor_value(2)>11.0){
                    omni_move_toward(x()-leftdist,y(),0.2);
                }else{
                    omni_track_velocity(0,0);
                }
            }
         
            
        }  
        
        void exit(const Event &e) {}
        double updist=0;
        double rightdist=0;
        double downdist=0;
        double leftdist = 0;



    };


class OmniController :public StateMachine, public AgentInterface
{
    public:
    OmniController():StateMachine()
    {
        set_initial(findwall);
        add_transition("rotate",findwall,godown);
        
        add_transition("righty",godown,goright);
        add_transition("righty",hole,goright);

        add_transition("uppy",goright,goup);
        add_transition("uppy",hole,goup);


        add_transition("lefty",goup,goleft);
        add_transition("lefty",hole,goleft);

        add_transition("holey",goup,hole);
        add_transition("holey",godown,hole);
        add_transition("holey",goleft,hole);
        add_transition("holey",goright,hole);


        add_transition("downy",goleft,godown);
        add_transition("downy",hole,godown);


        add_transition("goaly",goright,goal);
        add_transition("goaly",goleft,goal);
        add_transition("goaly",goup,goal);
        add_transition("goaly",godown,goal);

           }

    FindWall findwall;
    GoDown godown;
    GoRight goright;
    GoUp goup;
    GoLeft goleft;
    Hole hole;
    Goal goal;

};

class omni : public Agent {
    public:
    omni(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    OmniController c;
};

DECLARE_INTERFACE(omni)

#endif