/*
processing.cpp
Danielle Jacobs
November 23, 2025
Project 3, Gerp

Strips non alpha numeric characters from the beginning and end of words,
and prints out all file paths in a directory.
*/

#include <iostream>
#include <string>
#include <cctype>

#include "processing.h"
#include "FSTree.h"
#include "DirNode.h"

using namespace std;

void traverseDirNode(DirNode directory, string dirpath) {
    if (not directory.isEmpty()) {
        int numSubDirs = directory.numSubDirs();
        int numFiles = directory.numFiles();
        for (int f = 0; f < numFiles; f++) {
            std::string filename =  directory.getFile(f);
            std::cout << dirpath << "/" << filename <<  std::endl;
        }
        for (int d = 0; d < numSubDirs; d++) {
            DirNode *child_directory = directory.getSubDir(d);
            std::string nextpath = dirpath + "/" + child_directory->getName();
            traverseDirNode(*child_directory, nextpath);
        }
    }
}

void traverseDirectory(string directory) {
    FSTree my_fstree(directory);
    DirNode *root = my_fstree.getRoot();
    traverseDirNode(*root, root->getName());

}

string stripNonAlphaNum(string input) {
    size_t firstalpha = 0;
    size_t lastalpha = input.length()-1;
    while (firstalpha < input.length() and not isalnum(input[firstalpha])) {
        firstalpha++;
    }
    while (lastalpha > 0 and not isalnum(input[lastalpha])) {
        lastalpha--;
    }
    if (firstalpha==input.length()-1 and lastalpha==0) {
        return "";
    }
    else {
        int substr_size = lastalpha-firstalpha+1;
        string output = input.substr(firstalpha, substr_size);
        return output;
    }
}
