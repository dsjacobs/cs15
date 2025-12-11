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
        vector<vector<WordTableEntry>> gerpWordList;

        size_t size();
        size_t wordCapacity();
        float loadFactor();
        size_t myHash(string word);
        void reHash();

        bool contains(string wordLower);
        WordTableEntry get(string wordLower);

        // void newWord(string word, string wordLower, int fileID,int LineNum);    
        // void ExactCasingExists(size_t hashMod, size_t wordIndex, size_t CVI, 
        //                             size_t fileID, size_t LineNum);
        // void LowercaseExists(WordTableEntry wte, string word, int fileID, int LineNum);
        void addLower(string word, string wordLower, int fileID, int LineNum);

        void printWordTable();

    
    private:
        size_t entrySize;
        size_t capacity;
        void expand();
};

#endif