#ifndef __PROCESSING_H
#define __PROCESSING_H

/*
Danielle Jacobs
November 23, 2025
Project 3, Gerp
*/

#include <string>
#include <sstream>
#include <vector>

using namespace std;

string stripNonAlphaNum(string input);
stringstream traverseDirectory(string directory);
ifstream read_file_open_stream(string filename);
vector<string> process_line(string line);

#endif 