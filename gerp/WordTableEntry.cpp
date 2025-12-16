/*

WordTableEntry.cpp

Danielle Jacobs
December 7, 2025
Project 3, Gerp

New case variations (ie alternative spellings) can be added to a word table 
entry. A word table entry can be created or deconstructed.

*/

#include "WordTable.h"

using namespace std;

// constructor
// takes in a lowercase word, and the current table capacity.
// creates a new word table entry.
WordTableEntry::WordTableEntry(string wordLower, size_t capacity):
    spellingLower(wordLower) {
    hash<string> myHash;
    hashID = myHash(spellingLower)/capacity;
    allFileIDs = vector<size_t>();
    allLineNums = vector<size_t>();
};

// destructor
WordTableEntry::WordTableEntry() {};

// adds a new case Variation to the word table entry
// say BANANA exists but we want to add baNAna, a new cariation
// takes in that new variation
void WordTableEntry::add(caseVariation newVariation) {
    caseVariations.push_back(newVariation);
};