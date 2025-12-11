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
    for (size_t i = 0; i < capacity; i++) {
        vector<WordTableEntry> emptyVector;
        gerpWordList->push_back(emptyVector);
    }
};

WordTable::~WordTable() {
    delete this->gerpWordList;
};

WordTable::WordTable(const WordTable &other) {
    this->capacity = (other.wordCapacity() * 2) + 2;
    this->entrySize = other.entrySize;
    this->reHash(other.gerpWordList, other.wordCapacity());
};


void WordTable::reHash(vector<vector<WordTableEntry>>* otherWordList, 
                                                        size_t otherCapacity) {
    vector<vector<WordTableEntry>> *newGerpWordList = new vector<vector<WordTableEntry>>(wordCapacity());
    for (size_t i = 0; i < otherCapacity; i++) {
        vector<WordTableEntry> collisionlist = (*otherWordList)[i];
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
    size_t oldCapacity = this->capacity;
    capacity = (capacity * 2) + 2;
    reHash(oldPointer, oldCapacity);
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

// void WordTable::add(WordTableEntry wte) {
//     gerpWordList.push_back(wte);
// };

bool WordTable::contains(string wordLower) {
    hash<string> myHash;
    size_t hashID = myHash(wordLower);
    size_t modHash = hashID%capacity;
    vector<WordTableEntry> wordlist = (*gerpWordList)[modHash];
    for (size_t x = 0; x < wordlist.size(); x++) {
        WordTableEntry wte = wordlist[x];
        if (wte.spellingLower==wordLower) {
            return true;
        }
    }
    return false;
};

WordTableEntry WordTable::get(string wordLower) {
    hash<string> myHash;
    size_t modHash = myHash(wordLower)%capacity;
    vector<WordTableEntry> wordlist = (*gerpWordList)[modHash];
    WordTableEntry uninit_wte;
    for (size_t x = 0; x < wordlist.size(); x++) {
        WordTableEntry wte = wordlist[x];
        if (wte.spellingLower==wordLower) {
            return wte;
        }
    }
    return uninit_wte;
};


size_t WordTable::wordCapacity() const {
    return capacity;
}


void WordTable::printWordTable() {
    for (size_t x = 0; x < (*gerpWordList).size(); x++) {
        cout << "Index/HashMod of: " << x << endl;
        cout << (*gerpWordList)[x].size(); 
        cout << " words found here, including: " << endl;
        for (size_t y=0; y < (*gerpWordList)[x].size(); y++) {
            WordTableEntry wte = (*gerpWordList)[x][y]; 
            for (size_t c = 0; c < wte.caseVariations.size(); c++) {
                caseVariation cv = wte.caseVariations[c];
                cout << cv.spelling << endl;
                for (size_t k = 0; k < cv.caseFileList.size(); k++) {
                    cout << "in file: " << cv.caseFileList[x] << endl;
                    cout << "on line: " << cv.caseLineList[x] << endl;
                }
            }
        }
    }
    cout << loadFactor() << endl;
}


void WordTable::addLower(string word, string wordLower, int fileID, int 
    LineNum) {
    cout << "addLower: " << word << " " << wordLower << " " << fileID;
    cout << " " << LineNum << endl;

    if (loadFactor() > 0.7) {
        expand();
    }
    size_t hashmod = myHash(wordLower)%wordCapacity();
    
    // build lower case    
    caseVariation cv;
    cv.spelling = word;
    cv.initialized = true;
    cv.caseFileList.push_back(fileID);
    cv.caseLineList.push_back(LineNum);

     // build all case entry
    WordTableEntry wte(wordLower, wordCapacity());
    wte.caseVariations.push_back(cv);
    (*gerpWordList)[hashmod].push_back(wte);
};