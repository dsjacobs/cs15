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
    cursorCol = 0;
    cursorLine = 0;
    numLines = 0;
    text_filename = filename;
    std::ifstream ifstream = read_file_open_stream(filename);
    std::string ifstream_string;
    while (getline (ifstream, ifstream_string)) {
        curTextLines.push_back(ifstream_string);
        numLines++;
    }
    ifstream.close();
    UI = TextUI();
    end = false;
}

Editor::~Editor() {};

void Editor::run() {
    while (not end) {
        UI.render(curTextLines, cursorCol, cursorLine);
        int c  = UI.getChar();
        determine_next(c);
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
        std::cerr << "Invalid character" << std::endl;
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
    size_t curLineLength = lineLength(cursorLine);
    size_t nextLineLength = lineLength(cursorLine+1);
    size_t term_width = UI.getTerminalWidth();

    if (cursorLine != numLines - 1) or ((cursorCol + term_width) < curLineLength)
    {
        int add_termwidth = cursorCol + term_width;
        // if we should keep within the same line
        if (add_termwidth <= curLineLength) {
            cursorCol = add_termwidth;
        }
        // if we need to go down a line
        else {
            size_t curDisplayCol = cursorCol%term_width;
            cursorCol = curDisplayCol;
            cursorLine++;          
        }
    }
};

void Editor::move_up() {
    // make sure not at top
    size_t curLineLength = lineLength(cursorLine);
    size_t prevLineLength = lineLength(cursorLine-1);
    size_t term_width = UI.getTerminalWidth();
    if (cursorLine > 0 or cursorCol > term_width) 
    {
        // if we should stay within the line
        int subtract_termwidth = cursorCol - term_width;
        if (subtract_termwidth >= 0) {
            cursorCol = subtract_termwidth;
        }
        // if we need to go up a line
        else {
            size_t curDisplayCol = cursorCol%term_width;
            size_t numPrevLineWraps = prevLineLength/term_width;
            cursorCol = (numPrevLineWraps + curDisplayCol);
            cursorLine--;
        }
    }
};

void Editor::move_right() {
    if (cursorCol < curTextLines[cursorLine].size()){
        cursorCol++;
    }
    else if (cursorLine < numLines - 1) {
        cursorCol = 0;
        cursorLine++;
    }
};

void Editor::move_left() {
    if (cursorCol > 0) {
        cursorCol--;
    }
    else if (cursorLine > 0) {
        size_t prevLineLength = lineLength(cursorLine-1);
        cursorCol = prevLineLength;
        cursorLine--;
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

void Editor::delete_char(size_t line, size_t col) {
   std::string line_end = "";
   if (col <= lineLength(line)) {
        line_end = post_character(line, col+1); 
   }
  curTextLines[line] = pre_character(line, col) + line_end;
};

void Editor::backspace() {
    // middle of a row
    if (cursorCol != 0) 
    {
        char curChar = curTextLines[cursorLine][cursorCol];
        undoStack.push(curChar,true,cursorLine,cursorCol);
        delete_char(cursorLine, cursorCol); 
        cursorCol--;
    }
    // beginning of a row
    else {
        if (cursorLine > 0) {
            std::vector<std::string> latter_half;
            for (size_t i = cursorLine+1; i < numLines; i++) {
                latter_half.push_back(curTextLines[i]);
                curTextLines.pop_back();
            }
            // remove current line
            curTextLines.pop_back();
            curTextLines[cursorLine-1] += curTextLines[cursorLine];
            for (size_t i = 0; i < latter_half.size(); i++) {
                curTextLines.push_back(latter_half[i]);
            }
            cursorCol = lineLength(cursorLine-1);
            cursorLine--;
            numLines--;
            undoStack.push('n',true,cursorLine,cursorCol);  
        }      
    }
};

void Editor::new_line() {
    size_t curLine = cursorLine;
    size_t curLineLength = lineLength(cursorLine);
    std::vector<std::string> latter_half;
    // very end of file
    if (curLine==numLines - 1 and cursorCol == curLineLength) {
        curTextLines.push_back("");
    }
    else {
        std::string postCursorText = post_character(cursorLine, cursorCol);
        curTextLines[curLine] = pre_character(cursorLine, cursorCol); 
        for (size_t i = curLine+1; i < numLines; i++) {
            latter_half.push_back(curTextLines[i]);
            curTextLines.pop_back();
        }
        curTextLines.push_back(postCursorText);
        for (size_t i = 0; i < latter_half.size(); i++) {
            curTextLines.push_back(latter_half[i]);
        }
    }
    cursorCol = 0;
    cursorLine++;
    numLines++;
    undoStack.push('\n',false, curLine, 0);
}

void Editor::command_save() {
    std::ofstream savefile = open_file_output_stream(text_filename);
    for (size_t i=0; i < numLines; i++) {
        savefile << curTextLines[i] << std::endl;
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
        char c = latest.character;
        int line = latest.line;
        int col = latest.column;
        bool deleted = latest.deleted;
        // if a character was undone, put it back
        if (deleted) {
            insert(c, line, col);
        }
        else {
            delete_char(line, col);
        }
        undoStack.pop();
        redoStack.push(c, not deleted, line, col);
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

std::ofstream Editor::open_file_output_stream(std::string filename) {
        std::ofstream myofstream;   
        myofstream.open(filename);
        if (not myofstream.is_open()) {
            std::cerr << "Error: could not open file " << filename << std::endl;
            if (errno == ENOENT) {
                std::cerr << "Reason: File " << filename << " does not exist." << std::endl;
            } else if (errno == EACCES) {
                std::cerr << "Reason: Permission denied." << std::endl;
            } else {
                std::cerr << "Reason: Unknown error." << std::endl;
            }
        }
        return myofstream;
}

