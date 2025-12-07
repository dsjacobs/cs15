#ifndef __PROCESSING_H
#define __PROCESSING_H

/*
Danielle Jacobs
Nov 23, 2025
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