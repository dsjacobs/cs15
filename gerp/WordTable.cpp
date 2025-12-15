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

WordTable::WordTable() {
    entrySize = 0;
    capacity = 100;
    gerpWordList = vector<vector<WordTableEntry>>(capacity);
};

WordTable::~WordTable() {
    gerpWordList.clear();
};

void WordTable::reHash(size_t oldCapacity) {
    vector<vector<WordTableEntry>> newGerpWordList(capacity);
    for (size_t i = 0; i < oldCapacity; i++) {
        for (size_t j = 0; j < gerpWordList[i].size(); j++) {
            WordTableEntry &wte = gerpWordList[i][j];
            size_t hashID = myHash(wte.spellingLower);
            size_t newHashMod = hashID%wordCapacity();
            newGerpWordList[newHashMod].push_back(wte);
            for (size_t k = 0; k < wte.caseVariations.size(); k++) {
               wte.caseVariations[k].caseLineList.clear();
            }
     }
     gerpWordList[i].clear();
    }
    gerpWordList.clear();
    this->gerpWordList = newGerpWordList;
};

void WordTable::expand() {
    size_t oldCapacity = capacity;
    capacity = (capacity * 2) + 2;
    cout << "expanding from: " << oldCapacity << " to: " << capacity << endl;
    reHash(oldCapacity);
};

size_t WordTable::myHash(string word) {
    hash<string> myHashF;
    return myHashF(word);
}

float WordTable::loadFactor() {
    return (entrySize * 1.0)/(capacity);
}

size_t WordTable::size() {
    return entrySize;
};

size_t WordTable::wordCapacity() const {
    return capacity;
}

void WordTable::addLower(string word, string wordLower, int fileID, int 
    LineNum) {

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
