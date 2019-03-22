Securing Elam's Cruise Control from Cyber Attack
===

ELMA
----
[Elma](http://klavinslab.org/elma/) is an event loop and process manager for embedded and reactive systems. Elma is structured as a C++ library of classes on top of which you build your own C++ project. It keeps track of processes, finite state machines, events, and communication channels, executing them at specified frequencies. Elma was developed as part of the University of Washington's [ECE P 520 course](https://github.com/klavins/ECEP520) on advanced embedded systems programming. More information on how Elma was designed can be found in the links below:
- [Event loop management](https://github.com/klavins/ECEP520/tree/master/week_6)
- [Events and finite state machines](https://github.com/klavins/ECEP520/tree/master/week_7)
- [HTTP in event loops](https://github.com/klavins/ECEP520/blob/master/week_8)


 

About This Project
--------
With the widespread adaptation of Autonomous vehicles, cyber security is  of utmost value. This is a fun project intended to extend ELMA's functionality. This project is based on [Elma](http://klavinslab.org/elma/). The Repo is forked from ELMA. In the project I'll demonstrate how to implement a cyber defence mechanism against commonly known network layer attacks. We'll specifically implement defense and protection mechanism against DoS and D-DoS attacks. 

**Installation**
-------
[Elma](http://klavinslab.org/elma/) source code along with the driving example is used for this project. Follow the steps below for the installation. 

    git clone https://github.com/mulugetakem/elma.git
    cd elma
    docker run -v $PWD:/source -it klavins/elma:latest bash
    make
    cd finalproject
    make



**Execution**
--
To simulate a DoS attack, you would need to start another instance of the same docker image. This second container will be used to simulate a DoS attacker. You can add more instances to emulate a DDoS attack. 

    docker run -v $PWD:/source -it klavins/elma:latest bash
on the primary docker image run the following code to get the IP address of the docker so that you can send ping (ICMP Flood) from the secodary docker image. 

    ip a | grep -oE "\b([0-9]{1,3}\.){3}[0-9]{1,3}\b" | grep 172.17

notice the IP address you get here. it usally starts with 172.17.x.x 

Go to the main(primary) container and run the following command

    ./bin/driving_cyberdefence
The command above is used to start the car and cyber monitor. You can now send ICMP packets from the other secondary container (`ping 172.17.x.x`) and the behaviour is:
- If the ICMP packets coming into the car is small then nothing happens
- if the ICMP packets coming into the car is greater than a certain threshold (>5 in this case :smile: ) . Then the user is warned about a possible ICMP packet
- If the ICMP packets coming into the car is much higher and threatening (>10 in this case :smile: ) . A posiive feedback is applied and the car will be slowly brought to stop. 



**Architecture**
--
Describe how your project was designed, what choices you made, how things are organized, etc.
	


**Results**
---


This software is open source and uses the MIT license. Details can be found [here](https://github.com/klavinslab/elma).
