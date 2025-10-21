/*
 Danielle Jacobs
 October 2, 2025
 MetroSim

 Passengers can be added or removed from passenger queues. Passenger queues
 can be printed, their size and whether they are empty can be checked. The 
 first passenger in a PassengerQueue can be returned. 
 */

#include "PassengerQueue.h"
#include "Passenger.h"

using namespace std;

// Creates an empty Passenger queue with no input or output.
PassengerQueue::PassengerQueue() {};

// Given a passenger, creates a Passenger queue with that passenger.
PassengerQueue::PassengerQueue(Passenger pas) {
    enqueue(pas);
};

// Returns first passenger in the queue, unless the queue empty.
Passenger PassengerQueue::front() {
    if (isEmpty()) {
        throw std::range_error("Cannot get first element of empty list");
    }
    else {
        return vector_q.front();
    }
}

// Removes first passenger from queue unless the queue is empty.
void PassengerQueue::dequeue() {
    if (isEmpty()) {
        throw std::range_error("Cannot dequeue from empty list");
    }
    else {
        vector_q.erase(vector_q.begin());
    }
}

// Adds a given passenger to the back of a queue.
void PassengerQueue::enqueue(const Passenger &passenger) {
    vector_q.push_back(passenger);
}

// Returns the size of the queue
int PassengerQueue::size() {
    return vector_q.size();
}

// Prints all passengers to given output stream.
void PassengerQueue::print(std::ostream &output) {
    for (int i=0; i < size(); i++) {
        Passenger cur_pas  = vector_q[i];
        cur_pas.print(output);
    }
}

// Returns true if queue is empty.
bool PassengerQueue::isEmpty() {
    return (size()==0);
}
