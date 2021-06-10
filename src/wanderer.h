#ifndef __WANDERER_AGENT__H
#define __WANDERER_AGENT__H

#include <string>
#include <math.h>
#include "enviro.h"
#include <string.h>

namespace
{

    using namespace enviro;

    
    class Forward : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) {
            std:: cout << "Forward : \n ";
            initialFront =sensor_value(0);
            initialSide =sensor_value(1);
            
            }
        void during()
        {
            track_velocity(1,0);
            if (sensor_value(0)>11.0 && sensor_value(1)> 11.0){
                emit(Event("slighty"));
            }

            if (sensor_value(0)<11.0 && sensor_value(1)>11.0){
                emit(Event("hardy"));
            }

            if(sensor_value(0)<11.0 && sensor_value(1)<11.0){
                emit(Event("corny"));
            }
            if(sensor_value(0)>11.0 && sensor_value(1)<11.0){
                emit(Event("lslighty"));
            }
        }
         
        void exit(const Event &e) {};
        double initialFront;
        double initialSide ;
        double initialBack;
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;
    };

    class Hardleft : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) {
            std:: cout << "Hardleft : \n ";
            initialFront =sensor_value(0);
            initialSide =sensor_value(1);
            
         }
        void during()
        {
            std:: cout << "Side Sensor: " << sensor_value(1) << "\n";
           track_velocity(0,-0.5);
           if(sensor_value(1)<11.0){
               emit(Event("straight"));
           }

        }
        void exit(const Event &e) {}
        double rate;
        double initialFront;
        double initialSide ;
        double initialBack;
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;
    };

    class Corner : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) {
            std:: cout << "Corner: \n ";
            initialFront =sensor_value(0);
            initialSide =sensor_value(1);
            
         }
        void during()
        {
           track_velocity(0,-.5);
           if (sensor_value(1)< 11.0){
               emit(Event("straight"));
           }
           

        }
        void exit(const Event &e) {}
        double rate;
        double initialFront;
        double initialSide ;
        double initialBack;
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;
    };

    class SlightRight : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) {
            std:: cout << "Slight Right : \n ";
            initialFront =sensor_value(0);
            initialSide =sensor_value(1);
            
         }
        void during()
        {
           track_velocity(0.5,0.15);
           if(sensor_value(0)<11.0 || sensor_value(1)<11.0){
               emit(Event("straight"));
           }

        }
        void exit(const Event &e) {}
        double rate;
        double initialFront;
        double initialSide ;
        double initialBack;
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;
    };
    class SlightLeft : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) {
            std:: cout << "Slight Left : \n ";
        
            initialFront =sensor_value(0);
            initialSide =sensor_value(1);
            
         }
        void during()
        {
           track_velocity(0.5,-0.2);
           std:: cout << "Side Sensor: " << sensor_value(1) << "\n";
           if(sensor_value(0)<11.0 || sensor_value(1)>initialSide*0.9){
               emit(Event("straight"));
           }

        }
        void exit(const Event &e) {}
        double rate;
        double initialFront;
        double initialSide ;
        double initialBack;
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;
    };

    class FindWall : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) {
            std:: cout << "Find Wall : \n ";
        
            initialFront =sensor_value(0);
            initialSide =sensor_value(1);
            
         }
        void during()
        {
           track_velocity(1,0);
           std:: cout << "Front Sensor: " << sensor_value(0) << "\n";
           if(sensor_value(0)<11.0 ){
               emit(Event("rotate"));
           }

        }
        void exit(const Event &e) {}
        double rate;
        double initialFront;
        double initialSide ;
        double initialBack;
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;
    };



    
    class WandererController : public StateMachine, public AgentInterface
    {

    public:
        WandererController() : StateMachine()
        {

            set_initial(findwall);
            tick_name = "tick_" + std::to_string(rand() % 1000); // use an agent specific generated
                                                                 // event name in case there are
                                                                 // multiple instances of this class
                                                  
            add_transition("hardy", forward, hardleft);
            add_transition("corny", forward, corner);
            add_transition("slighty", forward, slightright);
            add_transition("lslighty", forward, slightleft);
            add_transition("rotate",findwall,corner);

            add_transition("straight", hardleft, forward);
            add_transition("straight", corner, forward);
            add_transition("straight", slightright, forward);
            add_transition("straight", slightleft, forward);
  

        }

        //void update()
        //{
        //    if (rand() % 100 <= 5)
         //   {
         //       emit(Event("tick"));
         //   }
         //   StateMachine::update();
        //}

        Forward forward;
        Hardleft hardleft;
        Corner corner;
        SlightRight slightright;
        SlightLeft slightleft;
        FindWall findwall;

        //DoNot donot;
        std::string tick_name;
    };

    class Wanderer : public Agent
    {

    public:
        Wanderer(json spec, World &world) : Agent(spec, world)
        {
            add_process(wc);
        }

        WandererController wc;
    };

    DECLARE_INTERFACE(Wanderer);

}

double round(double var)

{

  

               double value = (int)(var * 100 +0.5);

               return (double)value / 100;

}


#endif