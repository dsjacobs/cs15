/*
 * Editor.cpp
 *
 * CS15 Proj 2: Typewriter
 * 
 * TO_DO: Purpose
 *
 * Author: Danielle Jacobs
 */

#include "Editor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

Editor::Editor(std::string text_fname) {
    std::ifstream text_fs = read_file_open_stream(text_fname);
}

std::ifstream Editor::read_file_open_stream(std::string text_file) {
        std::ifstream myifstream;   
        myifstream.open(text_file);
        if (not myifstream.is_open()) {
         std::cerr << "Error: could not open file " << text_file << std::endl;
                // when Main.cpp sees this is true, it will throw end sim
                file_read_error = true;
        }
        return myifstream;
}