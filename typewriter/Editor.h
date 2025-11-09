/*
 * Editor.h
 *
 * CS15 Proj 2: Typewriter
 * 
 * TODO: Purpose
 *
 * Author: Danielle Jacobs
 */

#include "TextUI.h"
#include "ActionStack.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

 class Editor {
    public:
        Editor(std::string text_fname);
        Editor(std::string filename, std::string logfile);
        ~Editor();
        void run();
      
    private:
        std::string text_filename;
        std::vector<std::string> curTextLines;
        size_t cursorCol;
        size_t cursorLine;
        bool end;
        TextUI UI;

        ActionStack undoStack;
        ActionStack redoStack; 

        void constructor_helper(std::string filename);
        std::ifstream read_text_file(std::ifstream &text_file);
        std::ifstream read_file_open_stream(std::string text_file);
        bool file_read_error;

        void add_logfile(std::string log_filename);
        void determine_next(int c);

        void move_down();
        void move_up();
        void move_right();
        void move_left();
        void insert(int c, int col, int line);
        void delete_char(int c, int col, int line)
        void command_mode();
        void backspace();

        void command_save();
        void command_quit();
        void command_undo();
        void command_redo();
        void close_command_mode();

        std::string pre_character(int col, int row);
        std::string post_character(int col, int row);
        size_t lineLength(int Line);
 };
