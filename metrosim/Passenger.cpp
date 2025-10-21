/*
 Danielle Jacobs
 October 2, 2025
 MetroSim

 Defines how to print a passenger's id, departing station and destination
 station. This supports the printing of passenger queues for the train and
 stations.
 */

#include <iostream>
#include <string>
#include "Passenger.h"

/*
 * Prints the id, origin and destination of passenger to given output stream.
 */
void Passenger::print(std::ostream &output)
{
        output << "[" << id << ", " << from << "->" << to << "]";
}



