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

Editor which_constructor(char *arg_v[], std::string text, std::string log) {
    if (arg_v.size() == 2) {
        log = arg_v[2];
        return Editor(text, log);
    }
    else {
        return Editor(text);
    }
}

int main(int argc, char *argv[])
{
    if (argc > 2 or argc == 0) {
        std::cerr << "Invalid number of arguments";
    }
    std::string text_filename = argv[1];
    std::string log_filename = "";
    Editor my_editor = which_constructor(argc, text_filename, log_filename);
    my_editor.run();

    return 0;
}
