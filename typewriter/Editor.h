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
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

 class Editor {
    public:
        Editor(std::string text_fname);
        ~Editor();

        std::string text_filename;
        std::vector<std::string> curTextLines;
        size_t cursorCol;
        size_t cursorLine;
        bool end;
        TextUI UI;

        std::ifstream read_text_file(std::ifstream &text_file);
        std::ifstream read_file_open_stream(std::string text_file);
        bool file_read_error;
        void run();
        void print_text(std::ostream &output);
        void save();
        void determine_next(char c);
 };
