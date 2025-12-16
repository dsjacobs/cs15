/*

gerp.h

November 22, 2025
Project 3, gerp
Danielle Jacobs

The Gerp class is the main class, where searches and file processing 
happen. It contains a list of files from the input directory, an output file,
a hash table as defined in WordTable.h, and instructions for how to route input 
from the user. 

*/

#ifndef GERP_H
#define GERP_H

#include <string>
#include <fstream> 
#include <vector>
#include <functional>
#include "WordTable.h"

using namespace std;

// maps file ID to file name
struct FileStruct {
    size_t fileID;
    string fileName;
    FileStruct(size_t myID, string myName): 
        fileID(myID), fileName(myName) {}; 
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
        size_t previousSearchLength;

        vector<string> requestInput();
        void determineWord(string input);
        void routeCmd(vector<string> input);

        void processWord(string word, size_t fileID,size_t LineNum);    
        bool addIfExists(string word, string wordLower, size_t fileID,
                                                                size_t LineNum);
        void addNewWord(string word, string wordLower, 
                                             size_t fileID, size_t LineNum);   
        void ExactCaseExists(caseVariation *cv, size_t fileID, size_t LineNum); 
        void LowercaseExists(WordTableEntry *wte, string word,
                                                size_t fileID,  size_t LineNum);
        bool mostRecentMatch(WordTableEntry *wte, size_t fileID, 
                                                        size_t ineNum);
        void initializeFiles(string directory);
        void processFile(size_t fileID, string fileName);
        void processLine(string line, size_t ileID, size_t LineNum);
        void printLine(size_t fileID, size_t lineNum);
        void printAllInstancesOfWord(WordTableEntry wte);
        void printAllInstancesOfCasing(caseVariation cv);
        vector<WordTableEntry> inputToCollisionList(string input);
};

#endif