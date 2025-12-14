/*

WordTable.h

Danielle Jacobs
December 7, 2025
Project 3, Gerp

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
        WordTable(const WordTable &other);
        vector<vector<WordTableEntry>> *gerpWordList;

        size_t size();
        size_t wordCapacity() const;

        float loadFactor();
        size_t myHash(string word);
        void reHash(size_t oldCapacity);
        void expand();
        void addLower(string word, string wordLower, int fileID, int LineNum);
    
    private:
        size_t entrySize;
        size_t capacity;
};

#endif