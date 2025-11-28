/*
gerp.cpp
November 22, 2025
Project 3, gerp
Danielle Jacobs

Purpose:
*/

#include "gerp.h"
#include <string>
#include <iostream>
#include <fstream>

gerp::gerp(std::string input_directory, std::string output_file) 
    :output_file(output_file),
    input_directory(input_directory),
    output_stream(create_ofstream(output_file, true)) 
{
    has_quit = false;
};

// Given a filename, creates and returns an output stream to that file. 
std::ofstream gerp::create_ofstream(std::string filename, bool first) {
    
    std::ofstream myofstream;   
    // during initialization, make a new output stream
    if (first) {
        myofstream.open(filename);
    }
    // // otherwise append to existing output stream
    // else {
    //     myofstream.open(filename, ios::app);
    // }
    if (not myofstream.is_open()) {
            std::cerr << "Error: could not open file " << filename << std::endl;
    }
    return myofstream;

}

gerp::~gerp() {};

void gerp::run() {
    while (not has_quit) {
        std::string input = request_input();
        route_cmd(input);
    }
};

void gerp::route_cmd(std::string input) {
    if (input.substr(0, 2)=="@f") {
        std::string new_filename = input.substr(3, input.length());
        output_stream = create_ofstream(new_filename, true);
    }
    else if (input=="@q" or input=="@quit") {
        quit();
    }
    else if(input.substr(0, 2)=="@i" or input.substr(0,12)=="@insensitive") {
        insensitive_search(input);
    }
    else {
        search(input);
    }
}

std::string gerp::request_input() {
    std::string input_command;
    std::cout << "Query?" << std::endl;
    std::getline(std::cin, input_command);  
    return input_command;
};

void gerp::quit() {
    has_quit = true;
}

void gerp::new_output_file(std::string filename) {

}

void gerp::search(std::string input) {

}

void gerp::insensitive_search(std::string input) {

}



