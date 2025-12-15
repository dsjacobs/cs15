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
    gerpWordList = vector<vector<WordTableEntry>>(capacity);
};

WordTable::~WordTable() {
    gerpWordList.clear();
};

void WordTable::reHash(size_t oldCapacity) {
    vector<vector<WordTableEntry>> newGerpWordList(capacity);
    cout << "rehash party" << endl;
    for (size_t i = 0; i < oldCapacity; i++) {
        vector<WordTableEntry> collisionlist = gerpWordList[i];
        cout << "at " << i << endl;
        for (size_t j = 0; j < collisionlist.size(); j++) {
            cout << "my house  " << i << endl;
            WordTableEntry wte = collisionlist[j];
            cout << "with " << wte.spellingLower << endl;
            size_t hashID = myHash(wte.spellingLower);
            size_t newHashMod = hashID%wordCapacity();
            cout << "and a new hashmod of " << newHashMod << endl;
        cout << newGerpWordList[newHashMod].size() << endl;
        newGerpWordList[newHashMod].push_back(wte);
        cout << "can we get it down? " << endl;
     }
    }
    this->gerpWordList = newGerpWordList;
};

void WordTable::expand() {
    size_t oldCapacity = capacity;
    capacity = (capacity * 2) + 2;
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
    caseVariation cv;
    cv.spelling = word;
    cv.caseFileList.push_back(fileID);
    cv.caseLineList.push_back(LineNum);

     // build all case entry
    WordTableEntry wte(wordLower, wordCapacity());
    wte.caseVariations.push_back(cv);
    gerpWordList[hashmod].push_back(wte);
    entrySize++;
};
