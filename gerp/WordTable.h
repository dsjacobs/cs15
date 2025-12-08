#include <vector>
#include <string>
#include <functional>
 
using namespace std;

#ifndef __WORDTABLE_H
#define __WORDTABLE_H

struct oneCase {
    string spelling;
    vector<size_t> file_list;
    vector<size_t> line_list; 
};

struct WordTableEntry {
    size_t hashID;
    string spelling_lower;
    vector<oneCase> entries;
    size_t tableCapacity;
    bool initialized;
    WordTableEntry(string word_lower, size_t capacity): 
       spelling_lower(word_lower),  tableCapacity(capacity)
    {
        hash<string> myHash;
        hashID = myHash(spelling_lower)/capacity;
        initialized = true;
    };
    //default constructor
    WordTableEntry() {
        initialized = false;
    };
    bool contains(string origCasing);
    oneCase get(string origCasing);
    void add(oneCase newCase);
};

class WordTable {
    public: 
        WordTable();
        void expand();
        size_t size();
        size_t word_capacity();
        float load_factor();

        void add(WordTableEntry);
        bool contains(string word_lower);
        void reHash();
        WordTableEntry get(string word_lower);
        void add_lower(size_t hashValue, string word, string word_lower, int fileID, int LineNum);
    
    private:
        size_t entrySize;
        size_t capacity;
        vector<WordTableEntry> entries;
};

#endif