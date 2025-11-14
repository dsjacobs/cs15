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
        exit(1);
    }
    else {
        std::string text_filename = argv[1];
        std::string log_filename = "";
        Editor my_editor = which(argc, argv, text_filename, log_filename);
        my_editor.run();
    }

    return 0;
}

// Consider nine points in space, no four  of which are coplanar. Each pair of points is joined by an edge (that is, a line segment) and each edge is either   colored blue or red or left uncolored. Find the smallest value of n such that whenever exactly n edges are colored, the set of colored edges necessarily contains a triangle all of whose edges 0have the same color.  