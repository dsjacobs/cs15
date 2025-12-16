/*

WordTableEntry.h

Danielle Jacobs
November 23, 2025
Project 3, Gerp

A word table entry consists of the lowercase spelling of a word, all its 
variations fouond within the input directory, and where they have each been
found.
*/

#include <vector>
#include <string>
#include <functional>
 
using namespace std;

#ifndef __WORDTABLEENTRY_H
#define __WORDTABLEENTRY_H

// Case Variation
struct caseVariation {
    string spelling;
    vector<size_t> caseFileList;
    vector<size_t> caseLineList; 
    // constructor from a lowercase word
    caseVariation(string mySpelling): 
        spelling(mySpelling), caseFileList(), caseLineList() {};
    // default constructo
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