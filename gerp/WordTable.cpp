/*
Danielle Jacobs
December 6, 2025
Project 3, Gerp
*/

#include <vector>
#include <string>
#include "WordTable.h"
#include "WordTableEntry.h"
#include <iostream>

WordTable::WordTable() {
    entrySize = 0;
    capacity = 100;
    gerpWordList = new vector<vector<WordTableEntry>>(wordCapacity());
};

WordTable::~WordTable() {
    delete this->gerpWordList;
};

WordTable::WordTable(const WordTable &other) {
    this->capacity = (other.wordCapacity() * 2) + 2;
    this->entrySize = other.entrySize;
    this->gerpWordList = other.gerpWordList;
    reHash(other.wordCapacity());
};


void WordTable::reHash(size_t oldCapacity) {
    vector<vector<WordTableEntry>> *newGerpWordList =
        new vector<vector<WordTableEntry>>(wordCapacity());
    for (size_t i = 0; i < oldCapacity; i++) {
        vector<WordTableEntry> collisionlist = (*gerpWordList)[i];
        for (size_t j = 0; j < collisionlist.size(); j++) {
            WordTableEntry wte = collisionlist[j];
            size_t hashID = myHash(wte.spellingLower);
            size_t newHashMod = hashID%wordCapacity();
        (*newGerpWordList)[newHashMod].push_back(wte);
     }
    }
    this->gerpWordList = newGerpWordList;
};

void WordTable::expand() {
    vector<vector<WordTableEntry>> *oldPointer = this->gerpWordList;
    size_t oldCapacity = capacity;
    capacity = (capacity * 2) + 2;
    reHash(oldCapacity);
    delete oldPointer;
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
    caseVariation cv;
    cv.spelling = word;
    cv.caseFileList.push_back(fileID);
    cv.caseLineList.push_back(LineNum);

     // build all case entry
    WordTableEntry wte(wordLower, wordCapacity());
    wte.caseVariations.push_back(cv);
    (*gerpWordList)[hashmod].push_back(wte);
    entrySize++;
};
