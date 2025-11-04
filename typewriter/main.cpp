/*
 * main.cpp
 *
 * CS15 Proj 2: Typewriter
 * 
 * TODO: Purpose
 *
 * Author: Danielle Jacobs
 */

#include <iostream>
#include <fstream>
#include <string>
#include "Editor.h"


int main(int argc, char *argv[])
{
    if (argc > 2 or argc == 0) {
        std::cerr << "Invalid number of arguments";
    }
    std::string text_filename = argv[1];
    std::string log_filename = "";
    std::cout << text_filename << std::endl;
    std::cout << log_filename << std::endl;
    Editor my_editor(text_filename);
    std::cout << "was able to make an instance" << std::endl;
//    if (argc == 2) {
//        log_filename = argv[2];
//    }
    std::cout << "printing input file" << std::endl;
    my_editor.print_inp_file(text_filename, std::cout);     
    
    return 0;
}
