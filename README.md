Securing Elam's Cruise Control from Cyber Attack
===

ELMA
----
Elma is an event loop and process manager for embedded and reactive systems. Elma is structured as a C++ library of classes on top of which you build your own C++ project. It keeps track of processes, finite state machines, events, and communication channels, executing them at specified frequencies. Elma was developed as part of the University of Washington's [ECE P 520 course](https://github.com/klavins/ECEP520) on advanced embedded systems programming. More information on how Elma was designed can be found in the links below:
- [Event loop management](https://github.com/klavins/ECEP520/tree/master/week_6)
- [Events and finite state machines](https://github.com/klavins/ECEP520/tree/master/week_7)
- [HTTP in event loops](https://github.com/klavins/ECEP520/blob/master/week_8)

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
