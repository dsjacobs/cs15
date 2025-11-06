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

Editor::Editor(std::string text_fname) {
    text_filename = text_fname;
    std::ifstream ifstream = read_file_open_stream(text_fname);
    std::string ifstream_string;
    while (getline (ifstream, ifstream_string)) {
        curTextLines.push_back(ifstream_string);
    }
    cursorCol = 0;
    cursorLine = 0;
    UI = TextUI();
    end = false;
}

Editor::~Editor() {};

void Editor::run() {
    while (end == false) {
        std::string input  = UI.getChar();
        std::cout << "running" << std::endl;
        determine_next(input);
        UI.render(curTextLines, cursorCol, cursorLine);
    }
    save();
}

void Editor::determine_next(std::string input) {
    try {
        int c = std::stoi(str);
        // if ascii
        if (32 <= c and cerr <= 126) {
            curTextLines[cursorLine][cursorCol] = c;
        }
        // if escape
        else if (c == 27) {
            end = true;
        }
    }
    catch (...) {
    //https://www.w3schools.com/cpp/cpp_exceptions.asp
        if (input == "KEY_BACKSPACE") {
                std::cout << "backspace pressed";
            }
        else if (input == "KEY_LEFT") {
            move_left();
        }
        else if (input == "KEY_RIGHT") {
            move_right();
        }
        else if (input == "KEY_UP") {
            move_up();
        }
        else if (input == "KEY_DOWN") {
            move_down();
        }
        else {
            std::cout << "Invalid character" << std::endl;
        }
    }
    // if backspace
    else if (c == KEY_BACKSPACE) {
        std::cout << "backspace pressed";
    }
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


void Editor::move_down() {};
void Editor::move_up() {};
void Editor::move_right() {};
void Editor::move_left() {};