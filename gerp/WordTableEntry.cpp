#include "WordTable.h"

using namespace std;

WordTableEntry::WordTableEntry(string wordLower, size_t capacity):
    spellingLower(wordLower), tableCapacity(capacity) {
    hash<string> myHash;
    hashID = myHash(spellingLower)/capacity;
};

WordTableEntry::WordTableEntry() {};

int WordTableEntry::caseVariationIndex(string origCasing) {
    for (size_t e = 0; e < caseVariations.size(); e++)
    {
        caseVariation c = caseVariations[e];
        if (c.spelling==origCasing) {
            return e;
        }
    }
    return -1;
};

void WordTableEntry::add(caseVariation newVariation) {
    caseVariations.push_back(newVariation);
};