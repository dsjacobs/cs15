#include <vector>
#include <string>
#include "wordTable.h"

/*
Danielle Jacobs
December 6, 2025
Project 3, Gerp
*/

void WordTable::expand() {
    entrySize = (2 x entrySize) + 2;
    reHash();
}

void WordTable::reHash() {
    for (size_t x = 0; x < entrySize; x++) {
        WordTableEntry cur = entries[x];

    }
}

void WordTable::contains(string word_lower) {
    
}