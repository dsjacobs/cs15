/*
gerp.cpp
November 22, 2025
Project 3, gerp
Danielle Jacobs

Gerp can read input files, process them word by word and store them in the Word
Table, perform searches on input from the user, and direct the results to an
output file.
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

// Takes in: an output file, and input directory
// Output: none
// Purpose: creates an instance of the gerp program.
// Effects: Sets quit to false, and initializes files to build data structures.
gerp::gerp(string inputDirectory, string outputFile) 
    :outputFile(outputFile),
    inputDirectory(inputDirectory),
    outputStream(createOfstream(outputFile))
{
    hasQuit = false;
    initializeFiles(inputDirectory);
    previousSearchLength=1;
};

// Takes in: a filename
// Output: an output file stream 
// Purpose: allows search results to be saved to an ouput file.
// Other: returns an error if the file is unopenable.
ofstream gerp::createOfstream(string filename) {
    ofstream myofstream; 
    myofstream.open(filename);  
    if (not myofstream.is_open()) {
        cerr << "Error: could not open file " << filename << endl;
    }
    return myofstream;
}

// Destructor
// No input or output
// Effects: clears all memory associated with the file list and word table.
gerp::~gerp() {
    gerpFileList.clear();
    for (size_t x = 0; x < gerpWordTable.gerpWordList.size(); x++) {
        gerpWordTable.gerpWordList[x].clear();
    }
    gerpWordTable.gerpWordList.clear();
};

// Purpose: Keeps the gerp program running until user quits.
// No output or other effects
void gerp::run() {
    while (not hasQuit) {
        vector<string> input = requestInput();
        routeCmd(input);
    }
};

// Requests input from the user with "Query?"
// Returns the input as a vector of strings, where each string is a word.
vector<string> gerp::requestInput() {
    for (size_t i = 0; i < previousSearchLength; i++) {
        cout << "Query? ";
    }
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

// Takes in: an input string from the user
// Determines:whether to quit, create a new file, or perform a case sensitive
// or case insensitve search.
void gerp::routeCmd(vector<string> input) {
    // new file
    if (input[0]=="@f"){
        string newFilename;
        if (input.size()==2) {
            newFilename = input[1];
        }
        // constructing multiword filenames
        else {
            newFilename = "";
            for (size_t i = 1; i < input.size()-1; i++) {
                newFilename+=input[i];
                newFilename+=" ";
            }
            newFilename+=input[input.size()];
        }
        newFilename = input[1];
        outputStream = createOfstream(newFilename);
    }
    // quit
    else if (input[0]=="@q" or input[0]=="@quit") {
        quit();
    }
    // insensitive search
    else if(input[0]=="@i" or input[0]=="@insensitive") {
        for (size_t x = 1; x < input.size(); x++) {
            insensitiveSearch(input[x]);
        }
        previousSearchLength = input.size() - 1;
    }
    // sensitive search
    else {
        for (size_t x = 0; x < input.size(); x++) {
            search(input[x]);
        }
        previousSearchLength = input.size();
    }
}

// Called as part of the constructor.
// Takes in: a list files from the directory
// Effects: maps each file name to an ID, and sends the file contents to 
// later functions to be read into the hash table.
void gerp::initializeFiles(string directory) {
    stringstream fstream = traverseDirectory(directory);
    size_t counter = 0;
    string filename;
    while (getline(fstream, filename)) {
        size_t newID = counter;
        string newName = filename;
        processFile(newID, newName);
        counter++;
    }
};

// Takes in: a filename
// Output: opens and returns an inupt filestream
// Also: if that file does not exist, creates it
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

// Takes in: a file ID and file name from initializeFiles()
// Effects: sends each file to further functions to be read into the hash table.
// Saves the file ID and name for reference
void gerp::processFile(size_t fileID, string fileName) {
    ifstream fstream = readFileOpenStream(fileName);
    string line;
    size_t lineCounter = 1;
    while (getline(fstream, line)) {
        processLine(line, fileID, lineCounter);
        lineCounter++;
    }
    FileStruct newFileStruct(fileID, fileName);
    gerpFileList.push_back(newFileStruct);
}

// Takes in: a line string, and the file ID and line number where it was found.
// Effects: Sends each word in the line to further functions to be read into
// the hash table.
void gerp::processLine(string line, size_t fileID, size_t lineNum) {
    stringstream linestream(line);
    string word;
    while (linestream >> word) {
        processWord(word, fileID, lineNum);
    }
}

// Takes in: a word, and the file ID and line number where it was found.
// Determines if it is already in the hash table, and how to add this instance
// of the word to the hashtable.
void gerp::processWord(string word, size_t fileID,size_t LineNum) {
    string wordClean = stripNonAlphaNum(word);
    string wordLower = wordToLower(wordClean);
    bool found = addIfExists(wordClean, wordLower, fileID, LineNum);
    if (not found) {addNewWord(wordClean, wordLower, fileID, LineNum);}
}

// Closes gerp program
void gerp::quit() {
    hasQuit = true;
    cout << "Goodbye! Thank you and have a nice day." << endl;
}

// Case sensitive search.
// Takes in a word
// Compares it against the hash table
// If an exact match is found, prints all matches to the output file.
void gerp::search(string input) {
    bool foundMatch = false;
    string wordClean = stripNonAlphaNum(input);
    if (wordClean!="") {
        string wordLower = wordToLower(wordClean);
        size_t hashID = gerpWordTable.myHash(wordLower);
        size_t hashMod = hashID%gerpWordTable.wordCapacity();
        // for all words in that collision list, IE at that hashmod
        for (size_t e = 0; e < gerpWordTable.gerpWordList[hashMod].size(); e++) 
            {WordTableEntry &wte = gerpWordTable.gerpWordList[hashMod][e];
            // determine if the lowercase spelling is a match
            if (wte.spellingLower==wordLower) {
                for (size_t x = 0; x < wte.caseVariations.size(); x++) {
                    caseVariation cv = wte.caseVariations[x];
                    // determines if any of the specific 
                    // case variations are a match
                    if (cv.spelling==wordClean) {
                        foundMatch = true;
                        printAllInstancesOfCasing(cv);
                    }
                }
            }
        }
    }
    if (not foundMatch or wordClean=="") {
        outputStream << wordClean << " Not Found. Try with @insensitive or @i.";
        outputStream << endl;
    }
}

// Case insensitive search
// takes in a word 
// Determines if its lowercase version is in the hash table.
// If so, prints all instances of that word to the output file.
void gerp::insensitiveSearch(string input) {
    bool matchFound = false;
    string wordClean = stripNonAlphaNum(input);
    if (input!="") {
        string wordLower = wordToLower(input);
        vector<WordTableEntry> collisionList = inputToCollisionList(wordClean);
        // for all words in that collision list, IE at that hashmod
        for (size_t e = 0; e < collisionList.size(); e++) {
            WordTableEntry wte = collisionList[e];
            if (wte.spellingLower==wordLower) {
            matchFound = true;
            printAllInstancesOfWord(wte);
            }
        }
    }
    if (not matchFound or wordClean=="") {
        outputStream << wordClean << " Not Found." << endl;
    }
};

// Takes in a hash table entry (a lower case spelling and its associated 
// variations and occurrences) and prints all occurrences of all variations to 
// the output file.
void gerp::printAllInstancesOfWord(WordTableEntry wte) {
    for (size_t i = 0; i < wte.allFileIDs.size(); i++) {
        size_t fileID = wte.allFileIDs[i];
        size_t LineNum = wte.allLineNums[i];
        printLine(fileID, LineNum);
    }
};

// Takes in a case variation, and prints all lines where it is found in the
// input directory, along with their fileIDs and line numbers, to the 
// output file.
void gerp::printAllInstancesOfCasing(caseVariation cv) {
    for (size_t i = 0; i < cv.caseFileList.size(); i++) {
        size_t fileID = cv.caseFileList[i];
        size_t LineNum = cv.caseLineList[i];
        printLine(fileID, LineNum);
    }
};

// Takes in a fileID and LineNum.
// Prints the fileID, LineNum, and the line of text to the output file.
void gerp::printLine(size_t fileID, size_t lineNum) {
    string fileName = gerpFileList[fileID].fileName;
    string line;
    ifstream fstream = readFileOpenStream(fileName);
    size_t lineCounter = 1;
    while (getline(fstream, line) and lineCounter < lineNum) {
        lineCounter++;
    }
    outputStream << fileName << ":" << lineNum << ": " << line << endl;
}

// Takes in a lowercase word.
// Returns the collision list of all the words found at that word's hashmod.
vector<WordTableEntry> gerp::inputToCollisionList(string wordLower) {
    size_t hashID = gerpWordTable.myHash(wordLower);
    size_t hashMod = hashID%gerpWordTable.wordCapacity();
    vector<WordTableEntry> wordlist = gerpWordTable.gerpWordList[hashMod];
    return wordlist;
};


// Takes in: a word, its lowercase spelling, file ID and line number.
// Determines if it is already in the word table
// If it is, adds it to that entry.
// If its not, returns true.
bool gerp::addIfExists(string word, string wordLower, size_t fileID,
                                                            size_t LineNum)  {
    size_t hashValue = gerpWordTable.myHash(wordLower);
    size_t currentCapacity = gerpWordTable.wordCapacity();
    size_t hashMod = hashValue % currentCapacity;
    bool lowerFound = false;   
    bool exactMatchFound = false; 

    for (size_t x = 0; x < gerpWordTable.gerpWordList[hashMod].size(); x++) {
        WordTableEntry &wte = gerpWordTable.gerpWordList[hashMod][x];
        // lower case match (banana and BANANA match)
        if (wte.spellingLower==wordLower) {
            lowerFound = true;
            if (not mostRecentMatch(&wte, fileID, LineNum)) {
                wte.allFileIDs.push_back(fileID);
                wte.allLineNums.push_back(LineNum);
            }
            // exact case match (banana and BANANA do NOT match)
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

// Takes in a pointer to a word table entry, a file ID, and a line Number.
// Returns whether the most recent addition to the all case file and line lists
// are the same as the line and ID that were input.
bool gerp::mostRecentMatch(WordTableEntry *wte, size_t fileID, size_t LineNum) {
    size_t fileListSize = wte->allFileIDs.size();
    size_t mostRecentFile = wte->allFileIDs[fileListSize-1];
    size_t mostRecentLine = wte->allLineNums[fileListSize-1];
    return (mostRecentFile==fileID and mostRecentLine==LineNum);
}

// Takes in: a word, its lowercase spelling, and the fileID and line number
// where it was read from.
// Effects: adds a new entry for it into the hash table.
void gerp::addNewWord(string word, string wordLower, size_t fileID,
                                                            size_t LineNum)    
{  
    gerpWordTable.addLower(word, wordLower, fileID, LineNum);
}

// Takes in: a pointer to a case variation, a file ID, and a line number.
// Effects: adds this occurrence of that exact word to that case variation.
void gerp::ExactCaseExists(caseVariation *cv, size_t fileID, size_t LineNum) {
    
    // checks for a repeat recently entered within the same file and line
    size_t cvSize = cv->caseFileList.size();
    size_t mostRecentFile = cv->caseFileList[cvSize-1];
    size_t mostRecentLine = cv->caseLineList[cvSize-1];
    bool thisLine = (fileID==mostRecentFile and LineNum==mostRecentLine);    
    
    // makes sure its not a repeat within the line
    if (not thisLine) {
        cv->caseFileList.push_back(fileID);  
        cv->caseLineList.push_back(LineNum);  
    }
};

// Takes in: pointer to a word table entry, the exact spelling of a word
// and the file ID and line number where it was found.
// Effects: adds a new case variation containing this occurrence of this 
// spelling. 
void gerp::LowercaseExists(WordTableEntry *wte, string word, size_t fileID,
                                                              size_t LineNum) 
{
    caseVariation cv(word);
    cv.caseFileList.push_back(fileID);
    cv.caseLineList.push_back(LineNum);
    wte->caseVariations.push_back(cv);
}
