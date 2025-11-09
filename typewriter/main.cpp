/*
 * main.cpp
 *
 * CS15 Proj 2: Typewriter
 * 
 * TODO: Purpose
 *
 * Author: Danielle Jacobs
 */

#include <iostream>
#include <fstream>
#include <string>
#include "Editor.h"


int main(int argc, char *argv[])
{
    if (argc > 2 or argc == 0) {
        std::cerr << "Invalid number of arguments";
    }
    std::string text_filename = argv[1];
    std::string log_filename = "";
    Editor my_editor;
    if (argc == 2) {
        log_filename = argv[2];
        my_editor(text_filename, log_filename);
    }
    else {
        my_editor(text_filename);
    }
    my_editor.run();
    return 0;
}
