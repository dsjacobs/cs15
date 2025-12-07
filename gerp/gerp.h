/*
gerp.h
November 22, 2025
Project 3, gerp
Danielle Jacobs

*/

#ifndef GERP_H
#define GERP_H

#include <string>
#include <fstream> 
#include <vector>
#include <functional>
#include "wordTable.h"

using namespace std;

struct FileStruct {
    int ID;
    string name;
    vector<string> text_vector;
    FileStruct(int myID, string myName, vector<string> myText) :
        ID(myID), name(myName), text_vector(myText) {};
};

class gerp {
    public:
        gerp(string input_directory, string output_file);
        ~gerp();
        void run();
        ofstream create_ofstream(string filename);
         void search(string search_string);
        void insensitive_search(string search_string);
        WordTable gerpWordTable;

    private:
        bool has_quit;
        string output_file;
        string input_directory;
        vector<FileStruct> filelist;
        ofstream output_stream;

       
        string request_input();
        void determine_word(string input);
        void route_cmd(string input);
        void quit();

        void initialize_files(string directory);
        void process_file(int fileID, string fileName);
        void process_line(string line, int fileID, int LineNum);
        void add_to_hash_table(string word, string word_lower, int fileID,int LineNum);
        void wordlist();
};

#endif