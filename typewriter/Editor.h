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
        size_t numLines;

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
        void insert(int c, int line, int col);
        void delete_char(size_t line, size_t col);
        void backspace(size_t line, size_t col, bool in_place);
        void new_line(size_t line, size_t col, bool in_place);
        void delete_new_line_char(size_t Line, size_t Col, bool in_place);
        
        void command_mode();
        void command_save();
        void command_quit();
        void command_undo();
        void command_redo();
        void close_command_mode();

        std::string pre_character(int col, int row);
        std::string post_character(int col, int row);
        size_t lineLength(int Line);
        std::ofstream open_file_output_stream(std::string filename);
 };
