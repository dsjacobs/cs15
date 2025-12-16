/* main.cpp
Project 3, Gerp
Danielle Jacobs
November 22, 2025

Purpose: Starts the gerp program from the command line, and provides it the input directory
and output file name so that it can run.
*/

#include "gerp.h"
#include <string>
#include <iostream>


int main(int argc, char *argv[])
{
    // needs to be exactly 3 arguments
    if (argc!=3) {
        std::cerr << "Usage : ./ gerp inputDirectory outputFile";
        return EXIT_FAILURE;
    }
    else {
        std::string input_directory = argv[1];
        std::string output_file_name = argv[2];
        gerp my_gerp(input_directory, output_file_name);
        my_gerp.run();
    }
    return 0;
}