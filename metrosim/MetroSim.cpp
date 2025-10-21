/*
 Danielle Jacobs
 October 5, 2025
 MetroSim

 Defines how to initialize stations, move the train, onboard and offboard
 passengers, read input files, output and print to files, end the simulation,
 proceed with valid and invalid commands, and ask the user for a command.

*/

#include "MetroSim.h"
#include "Station.h"
#include "PassengerQueue.h"
#include "Passenger.h"
#include "Train.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// constructor takes filenames for stations and outputs, creates
// list of stations and output stream. Creates MetroSim instance.
// Sets initial values for how many passengers have been created, 
// whether to keep askigng for commands, and whether there are
// file read errors.
MetroSim::MetroSim(string stations_fname, string output_fname) 
{
    std::ifstream stations_fs = read_file_open_stream(stations_fname);
    initialize_stations(stations_fs);
    psgr_ctr = 0;
    keep_asking = true;
    file_read_error = false;
    output_filename = output_fname;

    // wont use it now, but this ensures it exists/clears out old copies and
    // tests for errors. used later
    std::ofstream of_stream = open_file_output_stream(output_fname, true);
    of_stream.close();
};

// Takes a command filename, opens it, and creates input stream.
void MetroSim::add_cmd_file(string commands_filename) {
    read_file_open_stream(commands_filename);
}

// Called by the constructor, and based on stations input file.
// Creates list of stations and empty train at station 0
void MetroSim::initialize_stations(ifstream &stations_input) {
    int counter = 0;
    std::string line;
    while (std::getline(stations_input, line)) {
        int new_id = counter;
        string new_name = line;
        station_list.push_back(Station(new_id, new_name));
        PassengerQueue pq;
        the_train.add_pq(pq);
        counter++;
    }
    the_train.current_location = 0;
};

// With given output stream, prints the current status of all
// the stations and how many passengers are waiting
// at that sation to that output.
void MetroSim::print_stations(std::ostream &output) {
    for (size_t i = 0; i < station_list.size(); i++)
    {
        Station station = station_list[i];
        if (i==the_train.current_location) {
            output << "TRAIN: ";
        }
        else {
            output << "       ";
        }
        output << "[" << station.id << "] ";
        output << station.name << " {";
        station.pq_waiting.print(output);
        output << "}" << std::endl; 
    }
};

// No input, returns the current number of stations in the MetroSim.
size_t MetroSim::num_stations() {
    return station_list.size();
};

// Given an output stream, prints the status and passenger queues
// of both the train and stations.
void MetroSim::print_all(std::ostream &output) {
    the_train.print(output);
    print_stations(output);
}

// Asks for user input on the command line, and return it as a string.s
std::string MetroSim::ask_for_command() {
    string input_command;
    cout << "Command? "; 
    std::getline(std::cin, input_command);  
    return input_command;
}

// Given a command, determines what to call next or if command is invalid.
void MetroSim::determine_command(string input_command) {
    if (input_command == "m m") {
        move_train();
    }
    else if (input_command == "m f") {
        keep_asking = false;
        end_sim();
    }
    else if(input_command[0]=='p') {
        std::istringstream mystream(input_command);
        string p,a,d;
        mystream >> p >> a >> d;
        int arrival = std::stoi(a);
        int departure = std::stoi(d);
        add_passenger(arrival, departure);
    }
    else {
        cout << "Command: " << input_command << " not recognized." << endl;
        keep_asking = false;
    }
}

// Onboards  any passengers who are waiting.moves the train (if at the last
// station, then to station 0, otherwise to the next station.) Offboards 
// passengers who are leaving at that location from the train. Prints
// the current train and stations. then
void MetroSim::move_train() {
   onboarding();
   // if its at the last station, move it to station 0 next
    if (the_train.current_location==num_stations()-1)
        {
            the_train.current_location = 0;
    }
    else {the_train.current_location++;}
    offboarding();
    print_all(cout);

};

// Given a passenger's arrival and departure stations, creates a passenger.
// Adds to the passenger counter so that the next passenger
// can have the next ID.
void MetroSim::add_passenger(int arrival, int departure) {
    Passenger new_pgr(psgr_ctr + 1, arrival, departure);

    // stations must be positive and comparable to actual stations
    if (arrival > 0 and departure > 0) {
   	 // stations must be in bounds
	int ns = num_stations();
	if (arrival < ns and departure < ns) {
        	station_list[arrival].pq_waiting.enqueue(new_pgr);
        	psgr_ctr++;
        	print_all(cout);
    	}
    }
    else {cout << "Invalid station";}
};

// No parameters or output. Removes from the train, and from the simulation,
// any passengers getting off at the current stop. Prints them to the
// output file.
void MetroSim::offboarding() {
    int loc = the_train.current_location;
    int num_psgrs_to_leave = the_train.v_pq_train[loc].size();
    for (int i = 0; i < num_psgrs_to_leave; i++) {
        int psgr_id = the_train.v_pq_train[loc].front().id;
        print_offboarding(psgr_id, loc);
        the_train.v_pq_train[loc].dequeue();
    }
}

// No parameters or output. Removes all passengers waiting to board at the
// current station from the queue waiting at that taion, and adds them to
// the queues on the train based on their destinations.
void MetroSim::onboarding() {
    int loc = the_train.current_location;
    int num_psgrs_to_board = station_list[loc].pq_waiting.size();
    for (int i = 0; i < num_psgrs_to_board; i++) {
        Passenger psgr = station_list[loc].pq_waiting.front();
        station_list[loc].pq_waiting.dequeue();
        int to_stn = psgr.to;
        the_train.v_pq_train[to_stn].enqueue(psgr);
    }
}

// Called by offboarding. Given a passenger and station, crafts
// the message to be printed to the output file about that departure,
// and prints it.
void MetroSim::print_offboarding(int psgr_id, int station_id) {
    string station_name = station_list[station_id].name;
    std::ofstream of_stream = open_file_output_stream(output_filename, false);
    of_stream << "Passenger " << psgr_id << " left train at station ";
    of_stream << station_name << endl;
}

// Given an input commands file, reads it line by line and feeds the
// commands to the Determine Command function to be run. Stops when
// the file ends.
void MetroSim::read_commands_file(string filename) {
    std::ifstream cmd_stream = read_file_open_stream(filename);
    string cmd;
    while (getline(cmd_stream, cmd)) {
        cout << "Command? ";
        determine_command(cmd);
    }
    cmd_stream.close();

    // if it got to the end of the file without a "m f", end the sim now
    if (keep_asking) {end_sim();}
}

// Prints the message at the end of the simulation.
void MetroSim::end_sim() {
    cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
}

// Given a filename, returns an input stream. If the file cannot be opener,
// throw an error, count that error as thrown, and end the simulation.
std::ifstream MetroSim::read_file_open_stream(string filename) {
        std::ifstream myifstream;   
        myifstream.open(filename);
        if (not myifstream.is_open()) {
                cerr << "Error: could not open file " << filename << std::endl;
                // when Main.cpp sees this is true, it will throw end sim
                file_read_error = true;
        }
        return myifstream;
}

// Given a filename, creates and returns an output stream to that file. 
std::ofstream MetroSim::open_file_output_stream(string filename, bool first) {
        std::ofstream myofstream;   
        // during initialization, make a new output stream
        if (first) {
            myofstream.open(filename);
        }
        // otherwise append to existing output stream
        else {
            myofstream.open(filename, ios::app);
        }
        if (not myofstream.is_open()) {
                cerr << "Error: could not open file " << filename << std::endl;
        }
        return myofstream;
}
