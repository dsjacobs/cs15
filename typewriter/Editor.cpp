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
#include "TextUI.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

render(const std::vector<std::string> &lines, const int &cursorCol, const int &cursorLine);

Editor::Editor(std::string text_fname) {
    text_filename = text_fname;
    std::ifstream ifstream = read_file_open_stream(text_fname);
    std::string ifstream_string;
    while (getline (ifstream, ifstream_string)) {
        curTextLines.push_back(ifstream_string);
    }
    cursorCol = 0;
    cursorLine = 0;
}

Editor::~Editor() {};

void Editor::run() {
    char c = TextUI::getChar();
    determine_next(c);
    TextUI::render(curTextLines, cursorCol, cursorLine);
}

void Editor::determine_next(char c) {
    // if ascii
    if (32 <= c and c <= 126) {
        std::string curLine = curTextLines[cursorLine];
        curLine[cursorCol] == c;
    }
    // else if (c is escape) {

    // }
    // else if (c is backspace) {
        
    // }
}
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
    for (size_t i = 0; i < curTextLines.size(); i++) {
        output << curTextLines[i];
    }
}

void Editor::save() 
{
  std::ofstream text_ofs(text_filename);
  print_text(text_ofs);
}