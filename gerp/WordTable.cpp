#include <vector>
#include <string>
#include "WordTable.h"
#include <iostream>

/*
Danielle Jacobs
December 6, 2025
Project 3, Gerp
*/

WordTable::WordTable() {
    capacity = 100;
    for (int i = 0; i < capacity; i++) {
        WordTableEntry wte;
        entries.push_back(wte);
    }
};

void WordTable::expand() {
    capacity = (2 * capacity) + 2;
    reHash();
};

float WordTable::load_factor() {
    return (entrySize * 1.0)/(capacity);
}

size_t WordTable::size() {
    return entrySize;
};

void WordTable::add(WordTableEntry wte) {

};

bool WordTable::contains(string word_lower) {
    hash<string> myHash;
    size_t hashID = myHash(word_lower);
    size_t modHash = hashID%capacity;
    if (not entries[modHash].initialized) {
        return false;
    }
    else if (entries[modHash].spelling_lower!=word_lower) {
        return false;
    }
    else {
        return true;
    }
};

void WordTable::reHash() {
    for (size_t x = 0; x < entrySize; x++) {
        WordTableEntry cur = entries[x];

    }
};

void WordTable::add_lower(size_t hashValue, string word, string word_lower, int fileID, int LineNum){
    
};


WordTableEntry WordTable::get(string word_lower) {
    
};


bool WordTableEntry::contains(string origCasing) {
    
};

oneCase WordTableEntry::get(string origCasing) {
    
};

void WordTableEntry::add(oneCase newCase) {
    
};

size_t WordTable::word_capacity() {
    return capacity;
}
