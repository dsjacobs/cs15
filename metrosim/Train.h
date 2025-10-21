/*
 Danielle Jacobs
 October 5, 2025
 MetroSim

 A train has a size, a current location, and a separate passenger queue
 for each station of those onboard who plan to depart at that station.
*/

#ifndef __TRAIN_H__
#define __TRAIN_H__

#include "PassengerQueue.h"

struct Train {
    public: 
        Train() {
            current_location = 0;
        }
        size_t current_location;
        void add_pq(PassengerQueue pq) {
            v_pq_train.push_back(pq);
        }
        void print(std::ostream &output);
        
        vector<PassengerQueue> v_pq_train;

        
    private:
        void sort();
};

#endif