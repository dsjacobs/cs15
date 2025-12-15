/*

WordTableEntry.h

Danielle Jacobs
November 23, 2025
Project 3, Gerp

*/

#include <vector>
#include <string>
#include <functional>
 
using namespace std;

#ifndef __WORDTABLEENTRY_H
#define __WORDTABLEENTRY_H

struct caseVariation {
    string spelling;
    vector<size_t> caseFileList;
    vector<size_t> caseLineList; 
    caseVariation(string mySpelling): 
        spelling(mySpelling), caseFileList(), caseLineList() {};
    caseVariation(): 
        spelling(""), caseFileList(), caseLineList() {};
};

class WordTableEntry {
    public:
        WordTableEntry();
        WordTableEntry(string wordLower, size_t tableCapacity);

        size_t hashID;
        string spellingLower;
        vector<caseVariation> caseVariations;
        void add(caseVariation newVariation);
};

#endif