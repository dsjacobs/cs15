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
#include "WordTable.h"

using namespace std;

struct FileStruct {
    int fileID;
    string fileName;
    vector<string> textVector;
    FileStruct(int myID, string myName, vector<string> myText) :
        fileID(myID), fileName(myName), textVector(myText) {};
};

class gerp {
    public:
        gerp(string inputDirectory, string outputFile);
        ~gerp();
        void run();
        ofstream createOfstream(string filename);
        void search(string search_string);
        void insensitiveSearch(string search_string);
        WordTable gerpWordTable;
        void quit();

    private:
        bool hasQuit;
        string outputFile;
        string inputDirectory;
        vector<FileStruct> gerpFileList;
        ofstream outputStream;

        string requestInput();
        void determineWord(string input);
        void routeCmd(string input);

        void initializeFiles(string directory);
        void processFile(int fileID, string fileName);
        void processLine(string line, int fileID, int LineNum);
        void printAllInstancesOfWord(WordTableEntry wte);
        void printAllInstancesOfCasing(caseVariation cv);
        vector<WordTableEntry> inputToCollisionList(string input);
};

#endif