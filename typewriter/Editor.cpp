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

Editor::Editor(std::string filename) {
    constructor_helper(filename);
}

Editor::Editor(std::string filename, std::string logfile) {
    constructor_helper(filename);
}

void Editor::constructor_helper(std::string filename) {
    std::ifstream ifstream = read_file_open_stream(filename);
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
        determine_next(c);
        UI.render(curTextLines, cursorCol, cursorLine);
    }
}

void Editor::determine_next(int c) {
    // if ascii
    if (32 <= c and c <= 126) {
        ascii(c);
    }
    // if escapes
    else if (c == 27) {
        command_mode();
    }
    else if (c == KEY_BACKSPACE) {
        backspace();
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

void Editor::move_down() {
    if (cursorLine != curTextLines.size())
    {
        cursorLine++;
    }
};
void Editor::move_up() {
    if (cursorLine > 0) 
    {
        cursorLine--;
    }
};
void Editor::move_right() {
    if (cursorCol < curTextLines[cursorLine].size()){
        cursorCol++;
    }
};
void Editor::move_left() {
    if (cursorCol > 0) {
        cursorCol--;
    }
};

void Editor::ascii(int c) {
    size_t curLineLength = curTextLines[cursorLine].size();
    std::string preCursorText = curTextLines[cursorLine].substr(0, cursorCol);
    std::string postCursorText = curTextLines[cursorLine].substr(cursorCol, curLineLength);
    char c_char = static_cast<char>(c);
    curTextLines[cursorLine] = preCursorText + c_char + postCursorText;
    undoStack.push(c_char,false,cursorLine,cursorCol);
    cursorCol++;
};

void Editor::command_mode() {
    int c = UI.getChar();
    if (c=='s') {
        command_save();
    }
    else if (c=='x') {
        command_quit();
    }
    else if (c=='u') {
        command_undo();
    }
    else if (c=='r') {
        command_redo();
    }
    else {
        close_command_mode();
    }
};

void Editor::backspace() {
    char curChar = curTextLines[cursorLine][cursorCol];
    redoStack.push(curChar,true,cursorLine,cursorCol);
};

void Editor::command_save() {
    std::ofstream savefile(text_filename);
    for (size_t i=0; i < curTextLines.size(); i++) {
        savefile << curTextLines[i];
    }
    savefile.close();
    UI.displaySaveMessage();
};
void Editor::command_quit() {
    bool save_bool = UI.savePrompt();
    if (save_bool) {command_save();}
    UI.close();
    end = true;
};
void Editor::command_undo() {
    undoStack.pop();
};
void Editor::command_redo() {
    redoStack.pop();
};
void Editor::close_command_mode() {};
