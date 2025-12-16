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
#include <sstream>
#include <fstream>

#include "processing.h"
#include "FSTree.h"
#include "DirNode.h"

using namespace std;

// recursive helper function for traverseDir
// takes in: a directory, its path, and a string stream.
// returns: the full paths of the filenames
void traverseDirNode(DirNode directory, string dirpath,std::stringstream &boo ) {
    if (not directory.isEmpty()) {
        int numSubDirs = directory.numSubDirs();
        int numFiles = directory.numFiles();
        // all files in parent directory
        for (int f = 0; f < numFiles; f++) {
            std::string filename =  directory.getFile(f);
            boo << dirpath << "/" << filename <<  std::endl;
        }
        // all child directories
        for (int d = 0; d < numSubDirs; d++) {
            DirNode *child_directory = directory.getSubDir(d);
            std::string nextpath = dirpath + "/" + child_directory->getName();
            traverseDirNode(*child_directory, nextpath, boo);
        }
    }
}

// takes in: a directory
// returns: the full paths of the filenames from that directory
std::stringstream traverseDirectory(string directory) {
    FSTree my_fstree(directory);
    DirNode *root = my_fstree.getRoot();
    std::stringstream f;
    std::string rootname = root->getName();
    traverseDirNode(*root,rootname, f);
    std::string line;
    return f;
}

// takes in: a word
// returns: that word cleaned of any leading and trailing 
// nonalphanumeric characters
string stripNonAlphaNum(string input) {
    size_t firstalpha = 0;
    size_t lastalpha = input.length()-1;
    //leading
    while (firstalpha < input.length() and not isalnum(input[firstalpha])) {
        firstalpha++;
    }
    // trailing
    while (lastalpha > 0 and not isalnum(input[lastalpha])) {
        lastalpha--;
    }
    // if one character word
    if (input.length()==1) {
        if (isalnum(input[firstalpha])) {
            return input;
        }
        else {
            return "";
        }
    }
    // entirely non alpha numeric
    else if (firstalpha==input.length()-1 and lastalpha==0) {
        return "";
    }
    else {
        int substr_size = lastalpha-firstalpha+1;
        string output = input.substr(firstalpha, substr_size);
        return output;
    }
}

// takes in: a word
// returns: that word in all lowercase
string wordToLower(string word) {
    string word_lower = "";
        for (size_t l = 0; l < word.size(); l++) {
            word_lower += tolower(word[l]);
        }
    return word_lower;
}
    