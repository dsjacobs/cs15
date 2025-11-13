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
        type_char(c, cursorLine, cursorCol);
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
        return myifstream;
}

void Editor::move_down() {    
    size_t curLineLength = lineLength(cursorLine);
    size_t nextLineLength = lineLength(cursorLine+1);
    size_t term_width = UI.getTerminalWidth();

    // if on the last line and cant go down futher
    if (cursorLine == numLines - 1 and cursorCol + term_width > curLineLength)
    {}
    else
    {
        size_t add_termwidth = cursorCol + term_width;
        // if we should keep within the same line
        if (add_termwidth <= curLineLength) {
            cursorCol = add_termwidth;
        }
        // if we need to go down a line
        else {
            size_t curDisplayCol = cursorCol%term_width;
            // if next line is too short, go to end
            if (curDisplayCol > nextLineLength) {
                cursorCol = nextLineLength;
            }
            // next line is long enough
            else {
                cursorCol = curDisplayCol;
            }
            cursorLine++;          
        }
    }
};

void Editor::move_up() {
    // make sure not at top
    size_t prevLineLength = lineLength(cursorLine-1);
    size_t term_width = UI.getTerminalWidth();

    // if on the top line and cant go up further
    if (cursorLine == 0 and cursorCol < term_width) {}
    else
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
            // if previous line is too short, go to end
            if (curDisplayCol > prevLineLength) {
                cursorCol = prevLineLength;
            }
            // previous line is long enough
            else {
                cursorCol = ((numPrevLineWraps * term_width) + curDisplayCol);
            }
            cursorLine--;
        }
    }
};

void Editor::move_right() {
    // we are before the end of our line
    if (cursorCol < lineLength(cursorLine)) {
        cursorCol++;
    }
    // make sure we're not in the last line of file
    else if (cursorLine < numLines - 1) {
        cursorCol = 0;
        cursorLine++;
    }
};

void Editor::move_left() {
    // if we're not at the beginning of a line   
    if (cursorCol > 0) {
        cursorCol--;
    }
    // make sure we're not in first line of file
    else if (cursorLine > 0) {
        size_t prevLineLength = lineLength(cursorLine-1);
        cursorCol = prevLineLength;
        cursorLine--;
    }
};


void Editor::type_char(int c, int line, int col) {
    insert(c, line, col);
    undoStack.push(static_cast<char>(c),false,line,col);
    cursorCol++;
};

void Editor::insert(int c, int line, int col) {
    std::string preCursorText = pre_character(line, col); 
    std::string postCursorText = post_character(line, col); 
    char c_char = static_cast<char>(c);
    curTextLines[line] = preCursorText + c_char + postCursorText;
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
};

void Editor::delete_char(size_t line, size_t col) {
  curTextLines[line] = pre_character(line, col) + post_character(line, col+1);
};

void Editor::backspace() {
    std::vector<std::string> new_version;
    // middle of a row
    if (cursorCol != 0) 
    {
        char curChar = curTextLines[cursorLine][cursorCol-1];
        undoStack.push(curChar,true,cursorLine,cursorCol-1);
        delete_char(cursorLine, cursorCol-1); 
        cursorCol--;
    }
    // beginning of a row
    else {
        // not in first line
        if (cursorLine != 0) {
        for (size_t i = 0; i < cursorLine - 1; i++) {
            new_version.push_back(curTextLines[i]);
        }
        std::string new_line = curTextLines[cursorLine-1];
        new_line += curTextLines[cursorLine];
        new_version.push_back(new_line);
        for (size_t i = cursorLine + 1; i < numLines;  i++) {
            new_version.push_back(curTextLines[i]);
        }
        cursorCol = lineLength(cursorLine-1);
        cursorLine--;
        numLines--;
        curTextLines = new_version;
        undoStack.push('\n',true,cursorLine,cursorCol-1);
        }
    }
};

void Editor::new_line() {
    size_t curLine = cursorLine;
    size_t curLineLength = lineLength(cursorLine);
    std::vector<std::string> new_version;
    // very end of file
    if (curLine==numLines - 1 and cursorCol == curLineLength) {
        curTextLines.push_back("");
    }
    else {
        for (size_t i = 0; i < curLine; i++) {
            new_version.push_back(curTextLines[i]);
        }
        new_version.push_back(pre_character(cursorLine, cursorCol)); 
        new_version.push_back(post_character(cursorLine, cursorCol));
        for (size_t i = curLine + 1; i < numLines;  i++) {
            new_version.push_back(curTextLines[i]);
        }
        curTextLines = new_version;
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
        if (deleted) {
            insert(c, line, col);
        }
        else {
            delete_char(line, col);
        }
        undoStack.pop();
        redoStack.push(c, not deleted, line, col);
        if (not undoStack.isEmpty() and c != '\n')
            command_undo();
        }
        cursorCol = 0;
        cursorLine = 0;
    };

void Editor::command_redo() {
    if (not redoStack.isEmpty()) {
        ActionStack::Action latest = redoStack.top();
        char c = latest.character;
        int line = latest.line;
        int col = latest.column;
        bool deleted = latest.deleted;
        if (deleted) {
            insert(c, line, col);
        }
        else {
            delete_char(line, col);
        }
        redoStack.pop();
        if (not redoStack.isEmpty() and c != '\n')
            command_redo();
        }
        cursorCol = 0;
        cursorLine = 0;
};

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
            std::cerr << "Could not open file." << std::endl;
        }
        return myofstream;
}

