#include <vector>
#include <string>
#include <functional>
 
using namespace std;

#ifndef __WORDTABLE_H
#define __WORDTABLE_H

struct oneCase {
    string spelling;
    vector<int> file_list;
    vector<int> line_list; 
};

struct WordTableEntry {
    hash<std::string> hashID;
    vector<oneCase> entries;
    WordTableEntry(std::hash<std::string> myHash): hashID(myHash) {};
};

class WordTable {
    public: 
        void expand();
        size_t size();
        void add(WordTableEntry);
        bool contains(string word_lower);
        void reHash();
    private:
        vector<WordTableEntry> entries;
        size_t entrySize;

};

#endif