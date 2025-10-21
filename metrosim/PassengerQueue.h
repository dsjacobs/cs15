/*
 Danielle Jacobs
 October 2, 2025
 MetroSim

 PassengerQueues are lists of passengers that can be waiting at stations
 or onboard the train. Passengers can only enter the queue at the back,
 and can only exit the queue at the front.
 */

#ifndef __PASSENGERQUEUE_H__
#define __PASSENGERQUEUE_H__

#include <iostream>
#include <string>
#include <vector>

#include "Passenger.h"

using namespace std;

class PassengerQueue {
    public:
        PassengerQueue();
        PassengerQueue(Passenger pas);
        Passenger front();
        void dequeue();
        void enqueue(const Passenger &passenger);
        int size();
        void print(std::ostream &output);
    private:
        vector<Passenger> vector_q;
        bool isEmpty();
};

#endif