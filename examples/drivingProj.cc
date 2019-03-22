#include <iostream>
#include <chrono>
#include "elma.h"
//#include "ProcessPacket.h"
#include <thread>
#include <sys/select.h>

//! \file
#include<netinet/ip_icmp.h>   //Provides declarations for icmp header
#include<netinet/udp.h>   //Provides declarations for udp header
#include<netinet/tcp.h>   //Provides declarations for tcp header
#include<netinet/ip.h>    //Provides declarations for ip header
#include<sys/socket.h>
#include<arpa/inet.h>
#include<errno.h>
#include<time.h>


using namespace std::chrono;
using std::vector;
using namespace elma;

namespace driving_example {

    //! Example: Another car simulation process. See examples/driving.cc.

    //! See the file examples/driving.cc for usage.
    class Car : public Process {
        public:

        //! Wrap the base process class
        //! \param name The name of the car    
        Car(std::string name) : Process(name) {}

        //! Nothing to do to initialize
        void init() {}

        //! To start a new simulation, this process sets
        //! the car's velocity to zero kph.    
        void start() {
            velocity = 0;
        }

        //! The update method gets the latest force from the 
        //! Throttle Channel, if any. Then it updates the 
        //! car's velocity, and sends it out on the Velocity
        //! Channel.     
        void update() {
            if ( channel("Throttle").nonempty() ) {
                force = channel("Throttle").latest();
            }
            velocity += ( delta() / 1000 ) * ( - k * velocity + force ) / m;
            channel("Velocity").send(velocity);
            std::cout << milli_time() << ","
                    << velocity << " \n";
        }

        //! Nothing to do to stop    
        void stop() {}

        private:
        double velocity;
        double force;
        const double k = 0.02;
        const double m = 1000;
    };  

    //! Example: A cruise controller for a Car process.  See examples/driving.cc.

    //! See the file examples/driving.cc for usage.
    class CruiseControl : public Process {

        public:

        //! Wrap the base process class
        //! \param name The name of the controller      
        CruiseControl(std::string name) : Process(name) {}

        //! Watch for events that change the desired speed.
        void init() {
            watch("desired speed", [this](Event& e) {
                desired_speed = e.value();
            });
        }

        //! Nothing to do to initialize    
        void start() {}

        //! Get the velocity from the Velocity Channel, compute
        //! a simple proportional control law, and send the result
        //! to the Throttle channel.    
        void update() { 
            if ( channel("Velocity").nonempty() ) {
                speed = channel("Velocity").latest();
            }
            channel("Throttle").send(-KP*(speed - desired_speed));
        }

        //! Nothing to do to stop    
        void stop() {}

        private:
        double speed = 0;
        double desired_speed = 0.0;
        const double KP = 314.15;
                    vector<double> _v;
    };

    //! Example: A simulated driver, who keeps cycling between 50 and 60 kph.  See examples/driving.cc.
    class Driver : public Process {

        public: 

        //! Wrap the base process class
        //! \param name The name of the controller       
        Driver(std::string name) : Process(name) {}

        //! initialize the desired speed
        void init() {
            desired_speed = 50;
        }

        //! Nothing to do to start
        void start() {
            std::cout<<"HI THIS is DRIVER :"<< Driver::name();
        }

        //! If the desired speed is 50, change to 60,
        //! otherwise change to 50.
        void update() {
            if ( desired_speed == 50 ) {
                desired_speed = 60;
            } else {
                desired_speed = 50;
            }
            emit(Event("desired speed", desired_speed));
        }

        //! Nothing to do to stop
        void stop() {}

        private:
        double desired_speed;

    };

    class CyberDefence : public Process { 
        public:
        CyberDefence(std::string name):Process(name){}
        void init(){
            //watch(Event("DDos Attack"));
        }
        void start(){}
        void update(){
            //if (CruiseControl.speed > 5)
            ///if Cymonitor channel has values and is greater than 30 then display
            ///warning to the user and halt the car. 

            //void init() {

            watch("DoS Attack", [this](Event& e) {
                icmpcount = e.value();
            });

            ///if ( channel("Velocity").nonempty() ) {
             ///   speed = channel("Velocity").latest();
           /// }
            if (icmpcount>10)
            std::cout<<"\x1B[91mCar Under DDOS ATTACK ! Your car will come to halt soon \033[0m\n";
            //overwrite the velocity channel here so that desired speed is changed. 
            //or increase the throttle hence pushing the car to a halt sooner. 

            //watch(Event("DDos Attack"));
        }
        void stop(){}


        private:
         double speed;
         int icmpcount;
    }; 

    class CyberMonitor : public Process {
        public:
        
        CyberMonitor(std:: string name): Process(name){}
       

         int ProcessPacket(unsigned char* buffer, int &size)
    //void  ProcessPacket(unsigned char* buffer, int &size)
             {
                struct iphdr *iph = (struct iphdr*)buffer;
                
                 switch(iph->protocol) //check the protocol
            // switch(iph.protocol)
                {
                    case 1:
                        ++icmpcount;
                        //printf("The %d th ping request has been received \n",icmpcount);
                        break;

                }

                return icmpcount;
             } 

    void ReceivePackets(int &sock_raw)
    {
       
        int data_size;         
        unsigned char *buffer = new unsigned char[65536];

        int k=0;



       while(1)
       //for(int k=0; k<20;k++)
    
               {
                   saddr_size = sizeof(saddr);

                   if(k<2)
                   {
                   data_size = recvfrom(sock_raw,buffer,65536,0,&saddr,&saddr_size);
                   //if(data_size <0)
                       // std::cout<<"Recvfrom Error, failed to get packages\n";
                    
                   icmpcount =  ProcessPacket(buffer,data_size);
                  //std::cout<<"\x1B[32mRecived the \033[0m" <<icmpcount<<"th\n";
                   //int* icmpcount = int processor(ProcessPacket(buffer, data_size);
                   }

                   else
                    break;
                  
                    k++;
               }

              // return icmpcount;
    }


        void init(){}
        void update(){

            int sock_raw;
            
           sock_raw = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

           if(sock_raw<0){
               perror("Error creating socket: ");
           }

            ReceivePackets(sock_raw);

            if (icmpcount>5)
            {
                emit(Event("DoS Attack", icmpcount));
                std::cout<<"\x1B[95m Denial of Service Attack!  \033[0m" <<icmpcount<<"\x1B[95m invalid packets arrived\033[0m\n";
            }
            
            

        }
        void start(){}
      
        void stop(){}

        private:
           int icmpcount=0; 
           socklen_t saddr_size;
           struct sockaddr saddr;
          


    };


}

int main() {

    Manager m;

    driving_example::Car car("Car");
    driving_example::CruiseControl cc("Control");
    driving_example::Driver driver("Steve");
    driving_example::CyberDefence cyde("DDoSPatrol");
    driving_example::CyberMonitor cymon("CYMon");
    Channel throttle("Throttle");
    Channel velocity("Velocity");
    m.schedule(car, 100_ms)
    .schedule(cc, 100_ms)
    .schedule(driver, 5_s)
    .schedule(cyde, 2_s)
    .schedule(cymon,2_s)
    .add_channel(throttle)
    .add_channel(velocity)
    .init()
    .run(60_s) ;

    

}