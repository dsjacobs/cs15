/*
 * Danielle Jacobs
 * Oct 5, 2025
 * MetroSim
 
 * The MetroSim class defines how passengers, stations, and trains interact
 * in order to support the simulation as a whole. It contains all information
 * relevant to an individual session, and supports all actions the user can
 * take.
 */

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "Passenger.h"
#include "PassengerQueue.h"
#include "Station.h"
#include "Train.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class MetroSim
{   
    public:
        MetroSim();
        MetroSim(string stations_filename, string output_filename);
        
        bool keep_asking;
        bool file_read_error;

        void add_cmd_file(string commands_filename);
        void initialize_stations(ifstream &stations_input);
        
        void print_stations(std::ostream &output);
        void print_all(std::ostream &output);

        std::string ask_for_command();
        void read_commands_file(string filename);
        void determine_command(string input_command);
        void end_sim();
        void move_train();
        void add_passenger(int arrival, int departure);
        void add_station(Station my_station) {
            station_list.push_back(my_station);
        };
        void onboarding();
        void offboarding();

        size_t num_stations();
        void print_offboarding(int psgr_id, int station_id);

        std::ifstream read_file_open_stream(string filename);
        std::ofstream open_file_output_stream(string filename);

    private:
        vector<Station> station_list;
        Train the_train;

        int psgr_ctr;
        string output_filename;
        void exit_failure();
};

#endif
