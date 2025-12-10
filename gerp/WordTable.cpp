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
    for (size_t i = 0; i < capacity; i++) {
        vector<WordTableEntry> emptyVector;
        gerpWordList.push_back(emptyVector);
    }
};

size_t WordTable::myHash(string word) {
    hash<string> myHashF;
    return myHashF(word);
}

void WordTable::expand() {
    cout << "EXPANDING" << endl;
    capacity = (2 * capacity) + 2;
    reHash();
};

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
    vector<WordTableEntry> wordlist = gerpWordList[modHash];
    for (size_t x = 0; x < wordlist.size(); x++) {
        WordTableEntry wte = wordlist[x];
        if (wte.spellingLower==wordLower) {
            return true;
        }
    }
    return false;
};

void WordTable::reHash() {
    for (size_t x = 0; x < entrySize; x++) {

    }
};

WordTableEntry WordTable::get(string wordLower) {
    hash<string> myHash;
    size_t modHash = myHash(wordLower)%capacity;
    vector<WordTableEntry> wordlist = gerpWordList[modHash];
    WordTableEntry uninit_wte;
    for (size_t x = 0; x < wordlist.size(); x++) {
        WordTableEntry wte = wordlist[x];
        if (wte.spellingLower==wordLower) {
            return wte;
        }
    }
    return uninit_wte;
};


size_t WordTable::wordCapacity() {
    return capacity;
}

void WordTable::newWord(string word, string wordLower, int fileID,int LineNum) {
    size_t hashValue = myHash(wordLower);
    size_t hashMod = hashValue % wordCapacity();
    vector<WordTableEntry> wordlist = gerpWordList[hashMod];
    bool found = false;
    for (size_t x = 0; x < wordlist.size(); x++) {
        WordTableEntry wte = wordlist[x];
        // upper case match
        if (wte.spellingLower==wordLower) {
            found = true;
            caseVariation cv = wte.get(word);
            // lower case match
            if (cv.initialized) {
                ExactCasingExists(cv, fileID, LineNum);
            }
            // just upper case
            else {
                LowercaseExists(wte, word, fileID, LineNum);
            }
        }
    }
    if (not found) {
        addLower(word, wordLower, fileID, LineNum);
    }
}

void WordTable::addLower(string word, string wordLower, int fileID, int LineNum) {
    entrySize++;
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
    gerpWordList[hashmod].push_back(wte);
}

void WordTable::ExactCasingExists(caseVariation cv, int fileID, int LineNum) {
    cv.caseFileList.push_back(fileID);
    cv.caseLineList.push_back(LineNum);
}

void WordTable::LowercaseExists(WordTableEntry wte, string word, int fileID, int LineNum) {
    caseVariation cv;
    cv.spelling = word;
    cv.initialized = true;
    cv.caseFileList.push_back(fileID);
    cv.caseLineList.push_back(LineNum);
    wte.add(cv);
}

void WordTable::printWordTable() {
    for (size_t x = 0; x < gerpWordList.size(); x++) {
        cout << "Index/HashMod of: " << x << endl;
        cout << gerpWordList[x].size(); 
        cout << " words found here, including: " << endl;
        for (size_t y=0; y < gerpWordList[x].size(); y++) {
            cout << gerpWordList[x][y].spellingLower << endl;
        }
    }
    cout << loadFactor();
}
