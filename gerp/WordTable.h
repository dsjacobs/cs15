/*

WordTable.h

Danielle Jacobs
December 7, 2025
Project 3, Gerp

The word table (a hash table) stores all words from the input directory for 
easy search and lookup. Each hashmod contains a collision list of words found
at that hashmod.

*/

#include <vector>
#include <string>
#include <functional>
#include "WordTableEntry.h"
 
using namespace std;

#ifndef __WORDTABLE_H
#define __WORDTABLE_H

class WordTable {
    public: 
        WordTable();
        ~WordTable();
        vector<vector<WordTableEntry>> gerpWordList;

        size_t size();
        size_t wordCapacity() const;

        float loadFactor();
        size_t myHash(string word);
        void reHash(size_t oldCapacity);
        void expand();
        void addLower(string word, string wordLower, size_t fileID, 
                                                                size_t LineNum);
    
        size_t entrySize;
        size_t capacity;
};

#endif