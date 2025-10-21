/*

 Danielle Jacobs
 October 5, 2025
 MetroSim

 A station has a name, an ID, and a Passenger Queue containing passengers
 waiting at that station.
*/

#ifndef __STATION_H__
#define __STATION_H__

#include "PassengerQueue.h"
using namespace std;

struct Station {
    int id;
    string name;
    PassengerQueue pq_waiting;
    Station(int new_id, string new_name) 
    {
        id = new_id;
        name = new_name;
    }
};

#endif