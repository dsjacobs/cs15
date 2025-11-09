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
    UI.startLogMode(logfile);
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
        insert(c, cursorLine, cursorCol);
        cursorCol++;
    }
    // if escapes
    else if (c == 27) {
        command_mode();
    }
    // if new line
    else if (c == 10) {
        new_line();
    }
    else if (c == KEY_BACKSPACE or c==263) {
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

void Editor::insert(int c, int line, int col) {
    std::string preCursorText = pre_character(line, col); 
    std::string postCursorText = post_character(line, col); 
    char c_char = static_cast<char>(c);
    curTextLines[line] = preCursorText + c_char + postCursorText;
    undoStack.push(c_char,false,line,col);
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

void Editor::delete_char(int line, int col) {
    curTextLines[line] = pre_character(line, col) + post_character(line, col+1);
};

void Editor::backspace() {
    char curChar = curTextLines[cursorLine][cursorCol];
    delete_char(cursorLine, cursorCol);
    undoStack.push(curChar,true,cursorLine,cursorCol);
};

void Editor::new_line() {
    size_t curLine = cursorLine;
    if (curLine < curTextLines.size()) {
        for (int i = curTextLines.size(); i > curLine; i--) {
            curTextLines[i+1] = curTextLines[i];
        }
    }
    curTextLines[curLine] = pre_character(cursorLine, cursorCol);
    curTextLines[curLine+1] = post_character(cursorLine, cursorCol);
    cursorLine++;
    undoStack.push('n',false,cursorLine, cursorCol)
}

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
    if (not undoStack.isEmpty()) {
        ActionStack::Action latest = undoStack.top();
        // if a character was undone, put it back
        if (latest.deleted) {
            insert(latest.character, latest.line, latest.column);
        }
        else {
            delete_char(latest.line, latest.column);
        }
        undoStack.pop();
        redoStack.push(latest.character, not latest.deleted, latest.line, latest.column);
    }
};

void Editor::command_redo() {
    if (not redoStack.isEmpty()) {
    ActionStack::Action latest = redoStack.top();
    if (latest.deleted) {
            insert(latest.character, latest.line, latest.column);
        }
        else {
            delete_char(latest.line, latest.column);
    }
    redoStack.pop();
    }
};

void Editor::close_command_mode() {};

size_t Editor::lineLength(int Line) {
    size_t curLineLength = curTextLines[Line].size();
    return curLineLength;
}

std::string Editor::pre_character(int line, int col) {
    std::string preCursorText = curTextLines[line].substr(0, col);
    return preCursorText;
}

std::string Editor::post_character(int line, int col) {
    size_t length = lineLength(line);
    std::string postCursorText = curTextLines[line].substr(col, length);
    return postCursorText;
}
