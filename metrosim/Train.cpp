/*
 Danielle Jacobs
 October 5, 2025
 MetroSim 

 A train can be printed as a series of passenger queues on the train.
*/

#include "Train.h"
#include "PassengerQueue.h"

// Given an output stream, prints the train to that output stream.
void Train::print(std::ostream &output) {
    output << "Passengers on the train: {";
    for (size_t i = 0; i < v_pq_train.size(); i++) {
        v_pq_train[i].print(output);
    }
    output << "}" << std::endl;
}