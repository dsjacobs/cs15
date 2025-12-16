/*
processing.h

Danielle Jacobs
November 23, 2025
Project 3, Gerp

Cleans words and reads directory structures for use within hash table.

*/

#ifndef __PROCESSING_H
#define __PROCESSING_H

#include <string>
#include <sstream>
#include <vector>

using namespace std;

string stripNonAlphaNum(string input);
stringstream traverseDirectory(string directory);
ifstream readFileOpenStream(string filename);
string wordToLower(string word);

#endif 