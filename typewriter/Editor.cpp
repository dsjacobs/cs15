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
        int c  = UI.getChar();
        std::cout << "running" << std::endl;
        determine_next(c);
        UI.render(curTextLines, cursorCol, cursorLine);
    }
    save();
}

void Editor::determine_next(int c) {
    // if ascii
    if (32 <= c and c <= 126) {
        curTextLines[cursorLine][cursorCol] = c;
        std::cout << curTextLines[cursorLine] << std::endl;
    }
    // if escapes
    else if (c == 27) {
        end = true;
    }
    if (c == KEY_BACKSPACE) {
        std::cout << "backspace pressed";
    }
    else if (c == KEY_LEFT) {
        move_left();
    }
    else if (c == KEY_RIGHT) {
        move_right();
    }
    else if (c == KEY_UP) {
        move_up();
    }
    else if (c == KEY_DOWN) {
        move_down();
    }
    else {
        std::cout << "Invalid character" << std::endl;
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