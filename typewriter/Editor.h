/*
 * Editor.h
 *
 * CS15 Proj 2: Typewriter
 * 
 * TODO: Purpose
 *
 * Author: Danielle Jacobs
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

 class Editor {
    public:
        Editor(std::string text_fname);
        ~Editor();
        std::ifstream read_text_file(std::ifstream &text_file);
        read_file_open_stream(std::string text_file);
    private:
 };