/*
Danielle Jacobs
November 23
Gerp
Unit Tests

Tests processing functions, constructors for word table, word 
table entries, and case variations, as well as gerp functionality
to add and search.

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

// WordTable constructs properly
void wt13_wordtable_constructor() {
    cout << "Test 13" << endl;
    WordTable myWT;
    assert(myWT.wordCapacity()==100);
    assert(myWT.size()==0);
};

void wt14_wordtable_size() {
    cout << "Test 14" << endl;
    WordTable myWT;
    myWT.addLower("pineapple","pineapple",3,4);
    myWT.addLower("banana","banana",7,8);
    assert(myWT.size()==2);
};

void wt15_wordtable_expand() {
    cout << "Test 15" << endl;
    WordTable myWT;
    assert(myWT.wordCapacity()==100);
    myWT.expand();
    assert(myWT.wordCapacity()==202);
}

void wt16_wordtable_addLower() {
    cout << "Test 16" << endl;
    WordTable myWT;
    myWT.addLower("banana", "banana", 1, 2);
    size_t hashID = myWT.myHash("banana");
    size_t hashMod = hashID%myWT.wordCapacity();
    assert(myWT.gerpWordList[hashMod].size()==1);
}

void wte17_wordtableentry_defaultconstructor() {
        cout << "Test 17" << endl;
    WordTableEntry wte;
    wte.spellingLower = "grapefruit";
    assert(wte.spellingLower=="grapefruit");
    assert(wte.allFileIDs.size()==0);
    assert(wte.allLineNums.size()==0);
}

void wte18_wordtableentry_customconstructor() {
    cout << "Test 18" << endl;
    WordTable myWT;
    WordTableEntry wte("grape",100);
    assert(wte.spellingLower=="grape");
    assert(wte.allFileIDs.size()==0);
    assert(wte.allLineNums.size()==0);
}

void cv19_casevariation_defaultconstructor() {
    cout << "Test 19" << endl;
    caseVariation cv;
    assert(cv.spelling=="");
    assert(cv.caseFileList.size()==0);
    assert(cv.caseLineList.size()==0);
}

void cv20_casevariation_customconstructor() {
    cout << "Test 20" << endl;
    caseVariation cv("mango");
    assert(cv.spelling=="mango");
    assert(cv.caseFileList.size()==0);
    assert(cv.caseLineList.size()==0);
}

void wte21_addCV() {
    cout << "Test 21" << endl;
    WordTableEntry wte;
    caseVariation cv1("mango");
    caseVariation cv2("mAngo");
    wte.add(cv1);
    wte.add(cv2);
    assert(wte.caseVariations.size()==2);
}

void processing_fromgs() {
    cout << "Test 22" << endl;
    string input = "{...";
    string output = stripNonAlphaNum(input);
    cout << output;
    cout << output.size();
    cout << "Test 22 over" << endl;
}

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
    wt13_wordtable_constructor();
    wt14_wordtable_size();
    wt15_wordtable_expand();
    wt16_wordtable_addLower();
    wte17_wordtableentry_defaultconstructor();
    wte18_wordtableentry_customconstructor();
    cv19_casevariation_defaultconstructor();
    cv20_casevariation_customconstructor();
    wte21_addCV();
    processing_fromgs();
    return 0;
}