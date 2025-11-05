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
    text_filename = text_fname;
    std::ifstream ifstream = read_file_open_stream(text_fname);
    std::string ifstream_string;
    while (getline (ifstream, ifstream_string)) {
        curTextLines.push_back(ifstream_string);
    }
}

Editor::~Editor() {};

std::ifstream Editor::read_file_open_stream(std::string text_file) {
        std::ifstream myifstream;   
        myifstream.open(text_file);
        if (not myifstream.is_open()) {
         std::cerr << "Error: could not open file " << text_file << std::endl;
                file_read_error = true;
        }
        return myifstream;
}

void Editor::print_text(std::ostream &output)
{
    std::string line;
    while (std::getline(curTextLines, line)) {
        output << line << std::endl; 
    }
}

void Editor::save() 
{
  std::ofstream text_ofs(text_filename);

  for (size_t i = 0; i < curTextLines.size(); i++) {
    text_ofs << curTextLines[i];
  }

  text_ofs.close();
}