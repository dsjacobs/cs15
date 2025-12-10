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
    bool initialized;
    vector<size_t> caseFileList;
    vector<size_t> caseLineList; 
    caseVariation() {initialized = false;}
};

class WordTableEntry {
    public:
        WordTableEntry();
        WordTableEntry(string wordLower, size_t capacity);

        size_t hashID;
        string spellingLower;
        vector<caseVariation> caseVariations;
        size_t tableCapacity;

        caseVariation get(string origCasing);
        void add(caseVariation newVariation);
};

#endif