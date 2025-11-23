/*
gerp.cpp
November 22, 2025
Project 3, gerp
Danielle Jacobs

Purpose:
*/

#include "gerp.h"
#include <string>

gerp::gerp(std::string input_directory, std::string output_file) {
    input_directory = input_directory;
    output_file = output_file;
    has_quit = true;
};

gerp::~gerp() {};

void gerp::run() {
    while (not has_quit) {
        std::string input = request_input();
        route_cmd(input);
    }
};

