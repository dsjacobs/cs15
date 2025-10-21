/*
 * Danielle Jacobs
 * October 2, 2025
 * Class Template
 * MetroSim
 *
 * An individual passenger has an id, and the station ids of the stations
 * where they will get on and off the train. A passenger can be created
 * as well as printed.
*/


#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include <iostream>

struct Passenger
{

        int id, from, to;
        
        Passenger()
        {
                id   = -1;
                from = -1;
                to   = -1;
        }

        Passenger(int newId, int arrivalStation, int departureStation)
        {
                id   = newId;
                from = arrivalStation;
                to   = departureStation;
        }

        void print(std::ostream &output);
};

#endif
