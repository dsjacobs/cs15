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

Editor which(int argc, char *argv[], std::string text, std::string log) {
    if (argc == 3) {
        log = argv[2];
        return Editor(text, log);
    }
    else {
        return Editor(text);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2 or argc > 3 ) {
        std::cerr << "Usage: ./typewriter textFile [logFile]" << std::endl;
    }
    else {
        std::string text_filename = argv[1];
        std::string log_filename = "";
        Editor my_editor = which(argc, argv, text_filename, log_filename);
        my_editor.run();
    }

    return 0;
}
