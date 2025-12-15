#include "WordTable.h"

using namespace std;

WordTableEntry::WordTableEntry(string wordLower, size_t capacity):
    spellingLower(wordLower) {
    hash<string> myHash;
    hashID = myHash(spellingLower)/capacity;
};

WordTableEntry::WordTableEntry() {};

void WordTableEntry::add(caseVariation newVariation) {
    caseVariations.push_back(newVariation);
};