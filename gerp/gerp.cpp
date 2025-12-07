/*
gerp.cpp
November 22, 2025
Project 3, gerp
Danielle Jacobs

Purpose: TODO
*/

#include "gerp.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include "processing.h"
#include "gerp.h"
#include "wordTable.h"

using namespace std;

// Given an output file, and input directory, creates an instance of the gerp
// program. Sets quit to false, and initializes files to build data structures.
gerp::gerp(string input_directory, string output_file) 
    :output_file(output_file),
    input_directory(input_directory),
    output_stream(create_ofstream(output_file))
{
    has_quit = false;
    initialize_files(input_directory);
};

// Given a filename, creates and returns an output stream to that file. 
ofstream gerp::create_ofstream(string filename) {
    ofstream myofstream;   
    if (not myofstream.is_open()) {
            cerr << "Error: could not open file " << filename << endl;
    }
    return myofstream;
}

// Destructor
gerp::~gerp() {};

// Keeps the gerp program running until user quits. Takes in input user and
// sends to route cmd for processing.
void gerp::run() {
    while (not has_quit) {
        string input = request_input();
        route_cmd(input);
    }
};

// Given an input string from the user, determines whether to quit, create a 
// new file, or perform case sensitive or insensitve search.
void gerp::route_cmd(string input) {
    if (input.substr(0, 2)=="@f") {
        string new_filename = input.substr(3, input.length());
        output_stream = create_ofstream(new_filename);
    }
    else if (input=="@q" or input=="@quit") {
        quit();
    }
    else if(input.substr(0, 2)=="@i" or input.substr(0,12)=="@insensitive") {
        insensitive_search(input);
    }
    else {
        search(input);
    }
}

// Requests input from the user with "Query?" and returns that input
string gerp::request_input() {
    string input_command;
    cout << "Query?" << endl;
    getline(cin, input_command);  
    return input_command;
};

// Called as part of the constructor. Takes in a list files that is output
// from traverse directory, and stores the content of each file.
void gerp::initialize_files(string directory) {
    stringstream fstream = traverseDirectory(directory);
    int counter = 0;
    string filename;
    while (getline(fstream, filename)) {
        int new_id = counter;
        string new_name = filename;
        process_file(new_id, new_name);
        counter++;
    }
    for (size_t i = 0; i < filelist.size(); i++) {
        FileStruct file = filelist[i];
        cout << "ID: " << file.ID << " Name: " << file.name << " ";
        cout << file.text_vector.size() << " lines long" << endl;
    }
};

ifstream read_file_open_stream(string filename) {
   ifstream myifstream; 
    myifstream.open(filename);
    // if file does not exist, make it
    if (not myifstream.is_open()) {
            ofstream newFile(filename);
            newFile.close(); 
            myifstream.open(filename);
        }
    return myifstream;
}

void gerp::process_file(int fileID, string fileName) {
    ifstream fstream = read_file_open_stream(fileName);
    string line;
    vector<string> myVector;
    int lineCounter = 0;
    while (getline(fstream, line)) {
        process_line(line, fileID, lineCounter);
        myVector.push_back(line);
        lineCounter++;
    }
    FileStruct newFileStruct(fileID, fileName, myVector);
    filelist.push_back(newFileStruct);
}

void gerp::process_line(string line, int fileID, int LineNum) {
    vector<string> words;
    stringstream linestream(line);
    string word;
    while (linestream >> word) {
        words.push_back(word);
        string word_lower = "";
        for (size_t l = 0; l < word.size(); l++) {
            word_lower += tolower(word[l]);
        }
    add_to_hash_table(word, word_lower, fileID, LineNum); 
    }
}

void gerp::add_to_hash_table(string word, string word_lower, int fileID,int LineNum) {
    //
}

void gerp::quit() {
    has_quit = true;
}

void gerp::search(string input) {
}

void gerp::insensitive_search(string input) {

}



