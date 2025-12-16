/*
Danielle Jacobs
November 23
Gerp
Unit Tests

Tests processing functions, gerp and word table functionality.

*/
#include "processing.h"  
#include "gerp.h"
#include "WordTable.h"
#include "WordTableEntry.h"
#include <cassert>
#include <iostream>

using namespace std;

string nonexistent = "not_there_123.txt";

//tests that a fully alphanumeric word remains unchanged
void a01_Processing_stripNonAlphaNum_reg_word() {
    cout << "Test 01" << endl;
    string input = "Banana123";
    string output = stripNonAlphaNum(input);
    assert(output == "Banana123");
};

//atests leading characters are stripped
void a02_Processing_stripNonAlphaNum_trail_beg() {
    cout << "Test 02" << endl;
    string input = "!!Banana456";
    string output = stripNonAlphaNum(input);
    assert(output == "Banana456");
};

//tests trailing characters are stripped
void a03_Processing_stripNonAlphaNum_trail_end() {
    cout << "Test 03" << endl;
    string input = "Banana456@@";
    string output = stripNonAlphaNum(input);
    assert(output == "Banana456");
};

//tests both leading and trailing characters are stripped
void a04_Processing_stripNonAlphaNum_trail_both() {
    cout << "Test 04" << endl;
    string input = "##Banana456%%";
    string output = stripNonAlphaNum(input);
    assert(output == "Banana456");
};

//tests non alpha-numeric characters in the middle of the string stay
void a05_Processing_stripNonAlphaNum_mid() {
    cout << "Test 05" << endl;
    string input = "Ban&ana45@62";
    string output = stripNonAlphaNum(input);
    assert(output == "Ban&ana45@62");
};

//tests string cleaning on a non alpha-numeric string returns empty string
void a06_Processing_stripNonAlphaNum_none() {
    cout << "Test 06" << endl;
    string input = "@#$%###*";
    string output = stripNonAlphaNum(input);
    assert(output == "");
};

//tests the directory traversal
void a07_Processing_traverseDirectory_dir() {
    cout << "Test 07" << endl;
    traverseDirectory("gerp-test-dirs/tinyData");
};

//non existent input directory
void a08_Gerp_gerp_no_input_dir() {
    cout << "Test 08" << endl;
    bool runtime_error_thrown = false;
    std::string error_message = "";
    try {
        traverseDirectory("gerp-test-dirs/banana");
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
};

//non existent output file
void a09_Gerp_gerp_no_output_file() {
    cout << "Test 09" << endl;
    ifstream file(nonexistent);
    assert(not file.is_open());
    file.close();
    gerp myGerp("gerp-test-dirs/tinyData", nonexistent);
    ifstream file2(nonexistent);
    assert(file2.is_open());
};

//existing input directory and output file
void a10_Gerp_gerp_input_and_output() {
    cout << "Test 10" << endl;
    gerp myGerp("gerp-test-dirs/tinyData", "gerp-output.txt");
    myGerp.quit();
};

//   create of_stream on working stream
void a11_Gerp_create_ofstream_working_stream() {
    cout << "Test 11" << endl;
    gerp myGerp("gerp-test-dirs/tinyData", "gerp-output.txt");
    ofstream myStream = myGerp.createOfstream("gerp_output.txt");
    assert(myStream.is_open());
    myGerp.quit();
};

//   create ofstream on not working stream
void a12_Gerp_create_ofstream_not_working_stream() {
    cout << "Test 12" << endl;
    gerp myGerp("gerp-test-dirs/tinyData", "gerp-output.txt");
    ofstream myStream = myGerp.createOfstream("emptyDir");
    assert(not myStream.is_open());
    myGerp.quit();
};

int main () {

    a01_Processing_stripNonAlphaNum_reg_word();
    a02_Processing_stripNonAlphaNum_trail_beg();
    a03_Processing_stripNonAlphaNum_trail_end();
    a04_Processing_stripNonAlphaNum_trail_both();
    a05_Processing_stripNonAlphaNum_mid();
    a06_Processing_stripNonAlphaNum_none();
    a07_Processing_traverseDirectory_dir();
    a08_Gerp_gerp_no_input_dir();
    a09_Gerp_gerp_no_output_file();
    a10_Gerp_gerp_input_and_output();
    a11_Gerp_create_ofstream_working_stream();
    a12_Gerp_create_ofstream_not_working_stream();
    return 0;
}