/*
Danielle Jacobs
December 6, 2025
Project 3, Gerp

The word table (Hash table) can be expanded and rehashed when the load factor
is high. The size, capacity, and load factor can be checked. New words, with
no existing match in the word table of any case variation, can be added.

*/

#include <vector>
#include <string>
#include "WordTable.h"
#include "WordTableEntry.h"
#include <iostream>

// constructor, starts with 0 entries and a capacity of 100
WordTable::WordTable() {
    entrySize = 0;
    capacity = 100;
    gerpWordList = vector<vector<WordTableEntry>>(capacity);
};

// destructor, clears all stack memory
WordTable::~WordTable() {
    gerpWordList.clear();
};

// takes in: the previous capacity
// effects: creates a new hash table with a larger capacity. Rehashes all 
// entries and inserts them into the new hash table. Empties the old table and
// keeps the new one.
void WordTable::reHash(size_t oldCapacity) {
    vector<vector<WordTableEntry>> newGerpWordList(capacity);
    // number of hashmod buckets
    for (size_t i = 0; i < oldCapacity; i++) {
        // number of words in that bucket
        for (size_t j = 0; j < gerpWordList[i].size(); j++) {
            WordTableEntry &wte = gerpWordList[i][j];
            size_t hashID = myHash(wte.spellingLower);
            size_t newHashMod = hashID%wordCapacity();
            newGerpWordList[newHashMod].push_back(wte);
            // clears old table
            for (size_t k = 0; k < wte.caseVariations.size(); k++) {
               wte.caseVariations[k].caseLineList.clear();
            }
     }
     gerpWordList[i].clear();
    }
    gerpWordList.clear();
    this->gerpWordList = newGerpWordList;
};

// expands the capacity of the hash table/
void WordTable::expand() {
    size_t oldCapacity = capacity;
    capacity = (capacity * 2) + 2;
    reHash(oldCapacity);
};

// defines a function to hash all input words.
size_t WordTable::myHash(string word) {
    hash<string> myHashF;
    return myHashF(word);
}

// calculates the load factor, in order to determine if the table 
// needs expanding.
float WordTable::loadFactor() {
    return (entrySize * 1.0)/(capacity);
}

// returns the entry size, or the number of words in the table.
size_t WordTable::size() {
    return entrySize;
};

// returns the table capacity
size_t WordTable::wordCapacity() const {
    return capacity;
}

// adds a new lowercase word to the table.
// takes in: a word, its lowercase spelling, and the file ID and line number
// where it was found.
void WordTable::addLower(string word, string wordLower, int fileID, 
                                                                int LineNum) {

    if (loadFactor() > 0.7) {
        expand();
    }
    size_t hashmod = myHash(wordLower)%wordCapacity();
    
    // build lower case    
    caseVariation cv(word);
    cv.caseFileList.push_back(fileID);
    cv.caseLineList.push_back(LineNum);

     // build all case entry
    WordTableEntry wte(wordLower, wordCapacity());
    wte.caseVariations.push_back(cv);
    gerpWordList[hashmod].push_back(wte);
    entrySize++;
};
