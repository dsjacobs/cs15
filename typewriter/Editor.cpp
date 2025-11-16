/*
 * Editor.cpp
 *
 * CS15 Proj 2: Typewriter
 * 
 * Defines how to open a new or existing file, take input from the user,
 * run the typewriter program, save to files, determine which action
 * to take based on which key has been pressed, define the actions needed
 * for aarow key moveents, undo, redo, new line, and backspace.
 *
 * Author: Danielle Jacobs
 * Date: November 3, 2025
 */

#include "Editor.h"
#include "TextUI.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Given a filename, opens and reads that file, loads
// it for editing. See constructor helper for additional 
// effects.
Editor::Editor(std::string filename) {
    constructor_helper(filename);
}

// Given two filenames, opens and reads the first, loading
// it for editing. Establishes the second file as a log file.
// See constructor helper for additional effects.
Editor::Editor(std::string filename, std::string logfile) {
    constructor_helper(filename);
    UI.startLogMode(logfile);
}

// Takes in a file name and sets cursor location to top left 
// of the editor. If there is a matching file, opens it and
// loads it for reading. If there is not, creates a new file
// by that name. Used by both constructors. Sets the number
// of lines in the editor, and creates the UI instance,and 
// ensures the editor starts as open.
void Editor::constructor_helper(std::string filename) {
    cursorCol = 0;
    cursorLine = 0;
    numLines = 0;
    text_filename = filename;
    UI = TextUI();
    end = false;
    std::ifstream myifstream = read_file_open_stream(text_filename);
    std::string ifstream_string;
    curTextLines = std::vector<std::string>(); 
    while (getline (myifstream, ifstream_string)) {
        curTextLines.push_back(ifstream_string);
        numLines++;
    }
    if (curTextLines.empty()) {
        curTextLines.push_back("");
        numLines++;
    }
    myifstream.close();
}

// Used by the constructor helper to open a file or determine
// that a new file must be made, and if so, makes it. Returns
// an input file stream for the constructor to read.
std::ifstream Editor::read_file_open_stream(std::string filename) {
   std::ifstream myifstream; 
    myifstream.open(filename);
    if (not myifstream.is_open()) {
            std::ofstream newFile(filename);
            newFile.close(); 
            myifstream.open(filename);
        }
    return myifstream;
}

// Destructor called automatically.
Editor::~Editor() {};

// Called by main.cpp, the run function keeps the editor running 
// until exit (Escape X) is called.
void Editor::run() {
    while (not end) {
        UI.render(curTextLines, cursorCol,cursorLine);
        size_t c = UI.getChar();
        determine_next(c);
    }
}

// Takes in a character from the user and determines what action
// to take with it. This will only work on ASCII characters,
// the escape key, new line and backspace, otherwise it will
// continue to the next function, determine_next_arrow_keys 
// to continue to check it against the arrow keys.
void Editor::determine_next(size_t c) {
    // if ascii
    if (32<=c and c <=126) {
        type_char(c, cursorLine, cursorCol);
    }
    // if escape
    else if (c==27) {
        command_mode();
    }
    // if new line
    else if (c==10) {
        enter_key();
    }
    // if backspace
    else if (c==KEY_BACKSPACE) {
        backspace();
    }
    // else
    else determine_next_arrow_keys(c);
}

// A continuation of determine next, this function determines
// if the user has pressed an arrow key, and which function to call.
// Otherwise, throws an error that it is not a valid input. To
// review, only arrows, backspace, enter, the escape key,
// and ASCII characters are accepted by the Editor.
void Editor::determine_next_arrow_keys(size_t c) {
    if (c==KEY_LEFT) {
        move_left();
    }
    else if (c==KEY_RIGHT) {
        move_right();
    }
    else if (c==KEY_UP) {
        move_up(cursorCol, cursorLine);
    }
    else if (c==KEY_DOWN) {
        move_down(cursorCol, cursorLine);
    }
    else {
        std::cerr << "Invalid character" << std::endl;
    }
};

// When the down arrow is pressed, determine if any movement is needed. 
// Will not move at all at the end of the file. Otherwise, will determine where
// to move the cursor based on line lengths and move it.
void Editor::move_down(size_t col, size_t line) {    
    size_t curLineLength = lineLength(line);
    size_t term_width = UI.getTerminalWidth();
    size_t curDisplayCol = col%term_width;


    // if on the last line and cant go down futher
    if (line==numLines-1 and col + term_width>curLineLength) {}
    else
    {
        // if we should keep within the same line
        if (col + term_width<=curLineLength) {
            col = col + term_width;
        }
        // if we need to go down a line
        else {
            size_t nextLineLength = lineLength(line+1);
            // if next line is too short, go to end
            if (curDisplayCol > nextLineLength) {
                col = nextLineLength;
            }
            else {
                col = curDisplayCol;
            }
            line++;          
        }
    }
    cursorCol = col;
    cursorLine = line;
};


// When the up arrow is pressed, determine if any movement is needed. 
// Will not move at all at the top of the file. Otherwise, will determine where
// to move the cursor based on line lengths and move it.
void Editor::move_up(size_t col, size_t line) {
    size_t term_width = UI.getTerminalWidth();
    size_t curDisplayCol = col%term_width;

    // if on the top line and cant go up further
    if (line==0 and col < term_width) {}
    else {
        // if we should stay within the line
        if (col>=term_width) {
            col = col - term_width;
        }
        // line wont be 0 anymore
        else {
            size_t prevLineLength = lineLength(line-1);
            size_t numPrevLineWraps = prevLineLength/term_width;
            if (curDisplayCol > prevLineLength) {
                col = prevLineLength;
            }
            // previous line is long enough
            else {
                col = ((numPrevLineWraps * term_width) + curDisplayCol);
            }
            line--;
        }
    }
    cursorCol = col;
    cursorLine = line;
}

// When the right arrow is pressed, determine if any movement is needed. 
// Will not move at all at the end of the file. Otherwise, will determine where
// to move the cursor and move it.
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

// When the left arrow is pressed, determine if any movement is needed. 
// Will not move at all at the top of the file. Otherwise, will determine where
// to move the cursor and move it.
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

// Takes in a character and a cursor location. Inserts the character
// at that location and updates the location of the cursor.
// Also stores the action in able to be undone later.
void Editor::type_char(size_t c, size_t line, size_t col) {
    redoStack.clear();
    undoStack.push(static_cast<char>(c),false,line,col);
    insert(c, line, col);
    cursorCol++;
};

// Takes in a character and a cursor location. Inserts the character
// at that location. Does NOT update cursor location or store
// action to be able to be undone later.
void Editor::insert(size_t c, size_t line, size_t col) {
    std::string preCursorText = pre_character(line, col); 
    std::string postCursorText = post_character(line, col); 
    char c_char = static_cast<char>(c);
    curTextLines[line] = preCursorText + c_char + postCursorText;
};

// If the escape key is pressed, the program enters command mode
// and waits for either save (S), exit (X), undo (U), or redo (R).
void Editor::command_mode() {
    size_t c = UI.getChar();
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

// Given a character and cursor location, deletes that character.
// Does NOT move cursor or store deletion to be able to be undone
// later.P
void Editor::delete_char(size_t line, size_t col) {
  curTextLines[line] = pre_character(line, col) + post_character(line, col+1);
};

// Given a character and cursor location, deletes that character.
// DOES move cursor and stores deletion to be able to be undone
// later. At the beginning of a line besides the first, will delete
// the new line character and move cursor to end of previous line.
void Editor::backspace() {
    redoStack.clear();
    std::vector<std::string> new_version;
    // middle of a row
    if (cursorCol!=0) 
    {
        char curChar = curTextLines[cursorLine][cursorCol-1];
        undoStack.push(curChar,true,cursorLine,cursorCol);
        delete_char(cursorLine, cursorCol-1); 
        cursorCol--;
    }
    // beginning of a row
    else {
        if (cursorLine!=0) {
            undoStack.push('\n',true,cursorLine,cursorCol);
            size_t prev_line_length = lineLength(cursorLine-1);
            delete_new_line(cursorLine);
            cursorCol = prev_line_length;
            cursorLine--;
        }
    }
};

// Deletes a new line, combines the text from previous and current lines into one. Does NOT affect cursor location.
void Editor::delete_new_line(size_t line) {
    // not in first line
    if (line!=0) {
        std::vector<std::string> new_version;
        for (size_t i = 0; i < line - 1; i++) {
            new_version.push_back(curTextLines[i]);
        }
        std::string new_line = curTextLines[line-1];
        new_line += curTextLines[line];
        new_version.push_back(new_line);
        for (size_t i = line + 1; i < numLines;  i++) {
            new_version.push_back(curTextLines[i]);
        }
        numLines--;
        curTextLines = new_version;
    }
}

// When the enter key is pressed, inserts a new line, moves the cursor down
// one row and to the beginning of that new line. Stores the action to be able
// to be undone later.
void Editor::enter_key() {
    undoStack.push('\n',false, cursorLine, 0);
    insert_new_line(cursorLine, cursorCol);
    cursorCol = 0;
    cursorLine++;
}

// Creates a new line (combines text of previous and current lines)
// without moving the cursor. Does not store the action to be able to
// be undone later.
void Editor::insert_new_line(size_t line, size_t col) {
    size_t curLineLength = lineLength(line);
    std::vector<std::string> new_version;
    for (size_t i = 0; i < line; i++) {
        new_version.push_back(curTextLines[i]);
    }
    new_version.push_back(pre_character(line, col)); 
    // end of file
    if (line==numLines - 1 and col==curLineLength) {
        new_version.push_back("");
    }
    else {
    new_version.push_back(post_character(line, col));
    for (size_t i = line + 1; i < numLines;  i++) {
        new_version.push_back(curTextLines[i]);
        }
    }
    curTextLines = new_version;
    numLines++;
} 

// Saves the current state of the editor to the file specified by the
// user before the simulation. Displays a save message.
void Editor::command_save() {
    std::ofstream savefile;
    savefile.open(text_filename);
    for (size_t i = 0; i < numLines; i++) {
        savefile << curTextLines[i] << std::endl; 
    }
    
    savefile.close();
    UI.displaySaveMessage();
};

// Asks the user if they would like to save, and then closes the program.
void Editor::command_quit() {
    bool save_bool = UI.savePrompt();
    if (save_bool) {command_save();}
    UI.close();
    end = true;
};

// When Undo is pressed, detrmines whether to proceed with deleteing
// a new line, or deleting a character. Removes action from 
// being stored to be undone, in order to be stored to be redone later.
void Editor::command_undo() {
    if (not undoStack.isEmpty()) {
        ActionStack::Action latest = undoStack.top();
        char c = latest.character;
        size_t line = latest.line;
        size_t col = latest.column;
        bool deleted = latest.deleted;
        undoStack.pop();
        // if undoing a new line characterd
        if(c=='\n') {
            undo_new_line(line, col, deleted);
            redoStack.push(c, not deleted, cursorLine, cursorCol);
        }
        else {
            undo_character(latest);
            redoStack.push(c, not deleted, line, col);
            // keep undoing until nothing left to be undone OR a new line
             if (not undoStack.isEmpty())
                {
                ActionStack::Action next = undoStack.top();
                if (next.deleted==deleted and next.character!='\n') { 
                command_undo(); 
            }
        }
        }
    }
};


// Called by command undo. If a new line character was deleted, makes a new
// line and sets the cursor to the beggining of that line. If a new line 
// had been made, deletes it, and moves the cursor to the beginning of the
// previous line.
void Editor::undo_new_line(size_t line, size_t col, bool deleted) {
    if (deleted) {
        insert_new_line(line, col);
        cursorCol = 0;
        cursorLine = line + 1;
    }
    else {
        size_t prev_line_length = lineLength(line-1);
        delete_new_line(line);
        cursorLine--;
        cursorCol = prev_line_length;
    }
};

// Called by command undo. If a character was deleted, adds it back, and if
// it was entered, deletes it. Continues until either there are no more
// actions to be undone or the next thing to be undone is a new line.
void Editor::undo_character(ActionStack::Action act) {
    char c = act.character;
    size_t line = act.line;
    size_t col = act.column;
    bool deleted = act.deleted;
    if (deleted) {
        insert(c, line, col - 1);
    }
    else {
        delete_char(line, col - 1);
    } 
};

// Redo can 'undo' 'undone' characters and new lines, putting them back in 
// place.

// Redo can 'undo' 'undone' characters and new lines, putting them back in 
// place.
void Editor::command_redo() {
    if (not redoStack.isEmpty()) {
        ActionStack::Action latest = redoStack.top();
        char c = latest.character;
        size_t line = latest.line;
        size_t col = latest.column;
        bool deleted = latest.deleted;
        redoStack.pop();
     
        // if new line
        if (c=='\n') {
            undo_new_line(line, col, deleted);
            undoStack.push(c, not deleted, cursorLine, cursorCol);
        }
        else {
            undo_character(latest);
            undoStack.push(c, not deleted, line, col);
            // keep redoing until nothing left to be redone OR new line
            while (not redoStack.isEmpty()) {
                ActionStack::Action next = redoStack.top();
                if (next.character!='\n')
                 { command_redo(); }
            }
        }

    }
};       

// Takes in a line number and returns the length of that line.
size_t Editor::lineLength(size_t line) {
    size_t curLineLength = curTextLines[line].size();
    return curLineLength;
}

// Takes in a line number and column number and returns any part of that 
// line thats to the left of that column.
std::string Editor::pre_character(size_t line, size_t col) {
    std::string preCursorText = curTextLines[line].substr(0, col);
    return preCursorText;
}

// Takes in a line number and column number and returns any part of that 
// line thats to the right of that column.
std::string Editor::post_character(size_t line, size_t col) {
    size_t length = lineLength(line);
    std::string postCursorText = curTextLines[line].substr(col, length);
    return postCursorText;
}


