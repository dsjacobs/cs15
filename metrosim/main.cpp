/*
 Danielle Jacobs
 October 5, 2025
 MetroSim

 The main file takes input from the user, either in a file or from the command
 line and instantiates the simulation. It determines the validity of the 
 number of arguments, which metrosim class functions to call to move
 forward with the simulation, and how long the simulation should run for.
*/

#include <iostream>
#include <fstream>
#include <string>

#include "MetroSim.h"
#include "PassengerQueue.h"
#include "Passenger.h"
#include "Station.h"

int  main(int argc, char *argv[])
{
    if (argc < 3 or argc > 4) {
        std::cerr << "Invalid number of arguments";
     }

        string stations_filename = argv[1];
        string output_filename = argv[2];
        string commands_filename = "";
        MetroSim my_metrosim(stations_filename, output_filename);
        if (argc == 4) {
                commands_filename = argv[3];
                my_metrosim.add_cmd_file(commands_filename);
                if (not my_metrosim.file_read_error) {
                my_metrosim.print_all(std::cout);
                my_metrosim.read_commands_file(commands_filename);
                }
        }
        else {
                my_metrosim.print_all(std::cout);
                while (my_metrosim.keep_asking) {
                string cmd = my_metrosim.ask_for_command();
                my_metrosim.determine_command(cmd);
                }
        }

        return 0;
}
