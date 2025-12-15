/*
gerp.cpp
November 22, 2025
Project 3, gerp
Danielle Jacobs

Purpose: TODO
*/

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>

#include "gerp.h"
#include "processing.h"
#include "WordTable.h"
#include "WordTableEntry.h"

using namespace std;

// Given an output file, and input directory, creates an instance of the gerp
// program. Sets quit to false, and initializes files to build data structures.
gerp::gerp(string inputDirectory, string outputFile) 
    :outputFile(outputFile),
    inputDirectory(inputDirectory),
    outputStream(createOfstream(outputFile))
{
    hasQuit = false;
    initializeFiles(inputDirectory);
};

// Given a filename, creates and returns an output stream to that file. 
ofstream gerp::createOfstream(string filename) {
    ofstream myofstream; 
    myofstream.open(filename);  
    if (not myofstream.is_open()) {
            cerr << "Error: could not open file " << filename << endl;
    }
    return myofstream;
}

// Destructor
gerp::~gerp() {
    gerpFileList.clear();
};

// Keeps the gerp program running until user quits. Takes in input user and
// sends to route cmd for processing.
void gerp::run() {
    while (not hasQuit) {
        vector<string> input = requestInput();
        routeCmd(input);
    }
};

// Requests input from the user with "Query?" and returns that input
vector<string> gerp::requestInput() {
    cout << "Query?" << endl;
    string input;
    getline(cin, input);
    stringstream inputstream(input);
    vector<string> inputVec;
    string word;
    while (inputstream >> word) {
        inputVec.push_back(word);
    }
    return inputVec;
};

// Given an input string from the user, determines whether to quit, create a 
// new file, or perform case sensitive or insensitve search.
void gerp::routeCmd(vector<string> input) {
    if (input[0]=="@f"){
        string newFilename;
        // TODO: Fix for multi word filenames
        // for (size_t x = 1; x < input.size()-1; x++) {
        //     newFilename += input[x];
        //     newFilename += " "; 
        // }
        newFilename = input[1];
        outputStream = createOfstream(newFilename);
    }
    else if (input[0]=="@q" or input[0]=="@quit") {
        quit();
    }
    else if(input[0]=="@i" or input[0]=="@insensitive") {
        for (size_t x = 1; x < input.size(); x++) {
            insensitiveSearch(input[x]);
        }
    }
    else {
        for (size_t x = 0; x < input.size(); x++) {
            search(input[x]);
        }
    }
}

// Called as part of the constructor. Takes in a list files that is output
// from traverse directory, and stores the content of each file.
void gerp::initializeFiles(string directory) {
    stringstream fstream = traverseDirectory(directory);
    int counter = 0;
    string filename;
    while (getline(fstream, filename)) {
        int newID = counter;
        string newName = filename;
        processFile(newID, newName);
        counter++;
    }
};

ifstream readFileOpenStream(string filename) {
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

void gerp::processFile(int fileID, string fileName) {
    ifstream fstream = readFileOpenStream(fileName);
    string line;
    vector<string> myVector;
    int lineCounter = 0;
    while (getline(fstream, line)) {
        processLine(line, fileID, lineCounter);
        myVector.push_back(line);
        lineCounter++;
    }
    FileStruct newFileStruct(fileID, fileName, myVector);
    gerpFileList.push_back(newFileStruct);
}

void gerp::processLine(string line, int fileID, int lineNum) {
    stringstream linestream(line);
    string word;
    while (linestream >> word) {
        processWord(word, fileID, lineNum);
    }
}

void gerp::processWord(string word, int fileID,int LineNum) {
    string wordClean = stripNonAlphaNum(word);
    string wordLower = wordToLower(wordClean);
    bool found = addIfExists(wordClean, wordLower, fileID, LineNum);
    if (not found) {addNewWord(wordClean, wordLower, fileID, LineNum);}
}


void gerp::quit() {
    hasQuit = true;
    cout << "Goodbye! Thank you and have a nice day." << endl;
}

void gerp::search(string input) {
    string wordClean = stripNonAlphaNum(input);
    string wordLower = wordToLower(wordClean);
    vector<WordTableEntry> collisionList = inputToCollisionList(wordClean);
    bool foundMatch = false;
    for (size_t e = 0; e < collisionList.size(); e++) {
        WordTableEntry wte = collisionList[e];
        if (wte.spellingLower==wordLower) {
            for (size_t x = 0; x < wte.caseVariations.size(); x++) {
                caseVariation cv = wte.caseVariations[x];
                if (cv.spelling==wordClean) {
                    foundMatch = true;
                    printAllInstancesOfCasing(cv);
                }
            }
        }
    }
    if (not foundMatch) {
        outputStream << input << " Not Found. Try with @insensitive or @i.";
        outputStream << endl;
    }
}

void gerp::insensitiveSearch(string input) {
    string wordClean = stripNonAlphaNum(input);
    string wordLower = wordToLower(input);
    vector<WordTableEntry> collisionList = inputToCollisionList(wordClean);
    bool matchFound = false;
    for (size_t e = 0; e < collisionList.size(); e++) {
        WordTableEntry wte = collisionList[e];
        if (wte.spellingLower==wordLower) {
           matchFound = true;
           printAllInstancesOfWord(wte);
        }
    }
    if (not matchFound) {
        outputStream << input << " Not Found." << endl;
    }
};

void gerp::printAllInstancesOfWord(WordTableEntry wte) {
    for (size_t x = 0; x < wte.caseVariations.size(); x++) {
        caseVariation cv = wte.caseVariations[x];
        printAllInstancesOfCasing(cv);
    }
};

void gerp::printAllInstancesOfCasing(caseVariation cv) {
    for (size_t i = 0; i < cv.caseFileList.size(); i++) {
        int fileNum = cv.caseFileList[i];
        int lineNum = cv.caseLineList[i];
        string fileName = gerpFileList[fileNum].fileName;
        string text = gerpFileList[fileNum].textVector[lineNum];
        outputStream << fileName << ":" << lineNum;
        outputStream << ": " << text << endl;
    }
};

vector<WordTableEntry> gerp::inputToCollisionList(string wordLower) {
    size_t hashID = gerpWordTable.myHash(wordLower);
    size_t hashMod = hashID%gerpWordTable.wordCapacity();
    vector<WordTableEntry> wordlist = gerpWordTable.gerpWordList[hashMod];
    return wordlist;
};


bool gerp::addIfExists(string word, string wordLower, int fileID,int LineNum)  {
    size_t hashValue = gerpWordTable.myHash(wordLower);
    size_t currentCapacity = gerpWordTable.wordCapacity();
    size_t hashMod = hashValue % currentCapacity;
    bool lowerFound = false;   
    bool exactMatchFound = false; 

    for (size_t x = 0; x < gerpWordTable.gerpWordList[hashMod].size(); x++) {
        WordTableEntry &wte = gerpWordTable.gerpWordList[hashMod][x];
        // upper case match
        if (wte.spellingLower==wordLower) {
            lowerFound = true;
            // lower case match
            for (size_t j = 0; j < wte.caseVariations.size(); j++) {
                caseVariation &cv = wte.caseVariations[j];
                if (cv.spelling==word) {
                    ExactCaseExists(&cv, fileID, LineNum);
                    exactMatchFound = true;
                }
            }
            if (not exactMatchFound) {
                LowercaseExists(&wte, word, fileID, LineNum);
            }
        }
    }
    return lowerFound;
}

void gerp::addNewWord(string word, string wordLower, int fileID,int LineNum)    
{  
    size_t hashValue = gerpWordTable.myHash(wordLower);
    size_t currentCapacity = gerpWordTable.wordCapacity();
    size_t hashMod = hashValue % currentCapacity;
    gerpWordTable.addLower(word, wordLower, fileID, LineNum);
    if (((gerpWordTable.gerpWordList))[hashMod].size() >= 3) {
        gerpWordTable.expand();
    }
}

void gerp::ExactCaseExists(caseVariation *cv, size_t fileID, size_t LineNum) {
    // check if the exact file and line are already there
    size_t cvSize = cv->caseFileList.size();
    size_t mostRecentFile = cv->caseFileList[cvSize-1];
    size_t mostRecentLine = cv->caseLineList[cvSize-1];
    bool thisLine = (fileID==mostRecentFile and LineNum==mostRecentLine);    
    
    if (not thisLine) {
        cv->caseFileList.push_back(fileID);  
        cv->caseLineList.push_back(LineNum);  
    }
};

void gerp::LowercaseExists(WordTableEntry *wte, string word, int fileID,
                                                                   int LineNum) 
{
    caseVariation cv;
    cv.spelling = word;
    cv.caseFileList.push_back(fileID);
    cv.caseLineList.push_back(LineNum);
    wte->caseVariations.push_back(cv);
}
