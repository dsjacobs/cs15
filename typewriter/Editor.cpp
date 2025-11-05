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
    std::string line;
    while (std::getline(text_fs, line)) {
       curTextLines.push_back(line);
    }
}

Editor::~Editor() {};

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

void Editor::print_text(std::ostream &output)
{
    for (int i=0; i < curTextLines.size(); i++) {
        output << curTextLines[i] << std::endl;
    }
}

void Editor::save(std::string text_fname) {
    std::ofstream text_ofs(text_fname);
    print_text(text_ofs);
    text_ofs.close();
}