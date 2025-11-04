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

std::ifstream Editor::read_file_open_stream(string text_file) {
        std::ifstream myifstream;   
        myifstream.open(filename);
        if (not myifstream.is_open()) {
                cerr << "Error: could not open file " << filename << std::endl;
                // when Main.cpp sees this is true, it will throw end sim
                file_read_error = true;
        }
        return myifstream;
}