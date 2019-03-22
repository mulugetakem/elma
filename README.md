Securing Elam's Cruise Control from Cyber Attack
===

ELMA
----
Elma is an event loop and process manager for embedded and reactive systems. Elma is structured as a C++ library of classes on top of which you build your own C++ project. It keeps track of processes, finite state machines, events, and communication channels, executing them at specified frequencies. Elma was developed as part of the University of Washington's [ECE P 520 course](https://github.com/klavins/ECEP520) on advanced embedded systems programming. More information on how Elma was designed can be found in the links below:
- [Event loop management](https://github.com/klavins/ECEP520/tree/master/week_6)
- [Events and finite state machines](https://github.com/klavins/ECEP520/tree/master/week_7)
- [HTTP in event loops](https://github.com/klavins/ECEP520/blob/master/week_8)

**Milestone this Week** 
----

- Development docker container environemnt is setup with the necessary bits. I used klavins/ecep520:latest
- I was able to send ICMP packets between two docker containers 
- The first class  that processes packets coming into the docker hub is implmented via C. More work needs to be done to integrate this to ELMA
>**How to run test the progress**
1. cd to elma_project. You'll need to instantiate two docker images: Primary one for processing the ip packets and secondary one to send ICMP packets (attacker). 
2. Run `docker run -v $pwd:/source -it klavins/elma:latest bash` for  both 
3. Also start another docker container to use as a client. Use the same command as in #2.
4. On the first container cd to /src/proj folder and run `make`
5. Before proceeding to run the output, get the IP address of the primary container so that you send ICMP packages from the other docker container: Run this command to get the IP address of the primary docker container 

    `ip a | grep -oE "\b([0-9]{1,3}\.){3}[0-9]{1,3}\b" | grep 172.17`

5. Now start processing packets on the primary docker image via `./bin/cyberdefence` 
6. Let #5 run and from the secondary docker ping the ip address of the primary docker.  `ping <172.17.x.x> `
7. You'll notice the primary continer identifes it has received ICMP packets and starts to count. The out put will be similar [this one](https://github.com/mulugetakem/elma_project/blob/master/img/primaryprocess.PNG)






 

About This Project
--------
With the widespread adaptation of Autonomous vehicles, cyber security is  of utmost value. This is a fun project intended to extend ELMA's functionality. This project is based on ELMA(Event Loop Manager)<HyperLink here>. The Repo is forked from ELMA. In the project I'll demonstrate how to implement a defensive mechanism against commonly known network layer attacks. We'll specifically implement defense and protection mechanism against DoS and D-DoS attacks. 

Project Implementation
===========
ELMA source code along with the Cruise Control implementation. Additionally, C++ Socket library will be used.  The system will listen for any event on a channel called "Firewall". If there are any DoS or DDoS attack an event will be emitted warning the system about possible attack. During which the user is either notified about the breach and the car will be brought to halt. 


How to use
===

Coming Soon....

Milestones
====
1.  Exploration (03/10): This stage mainly feasibility study and 
2. Implement Elma's cruise control (03/15)
3. Define classes and methods that will be used (03/15)
4. Write Test Cases  (03/15)
5. Implement classes and methods  (03/22)
6. Code Complete and Test Pass: (03/15)
7. Documentation 03/22
	


License
===

This software is open source and uses the MIT license. Details can be found [here](https://github.com/klavinslab/elma).
