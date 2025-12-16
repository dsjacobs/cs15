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
    ofstream myStream = myGerp.create_ofstream("gerp_output.txt");
    assert(myStream.is_open());
    myGerp.quit();
};

//   create ofstream on not working stream
void a12_Gerp_create_ofstream_not_working_stream() {
    cout << "Test 12" << endl;
    gerp myGerp("gerp-test-dirs/tinyData", "gerp-output.txt");
    ofstream myStream = myGerp.create_ofstream("emptyDir");
    assert(not myStream.is_open());
    myGerp.quit();
};

//before quit
void a13_Gerp_run_before_quit() {
    cout << "Test 13" << endl;
    gerp myGerp("gerp-test-dirs/tinyData", "gerp-output.txt");
    myGerp.run();
    myGerp.quit();
};

//after quit
void a14_Gerp_run_after_quit() {
    cout << "Test 14" << endl;
    gerp myGerp("gerp-test-dirs/tinyData", "gerp-output.txt");
    myGerp.run();
    myGerp.quit();
    myGerp.run();
};

// //   prints the message query?
// void a24_Gerp_request_input_reg() {
//     cout << "Test 24" << endl;
//     std::ostringstream catch_cout;
//     gerp myGerp("gerp-test-dirs/tinyData", "gerp-output.txt") > catch_cout;
//     assert(catch_cout.str() == "Query?\n");
// };


// //   one word
// void a26_Gerp_request_input_one_word() {
//     cout << "Test 26" << endl;

// };

// //   two words
// void a27_Gerp_request_input_two_words() {
//     cout << "Test 27" << endl;
// };

// //   three words
// void a28_Gerp_request_input_three_words() {
//     cout << "Test 28" << endl;
// };

// //   no directory
// void a29_Gerp_initialize_files_no_dir() {
//     cout << "Test 29" << endl;
// };

//   empty directory
void a30_Gerp_initialize_files_empty_dir() {
    cout << "Test 30" << endl;
};

//   small directory
void a31_Gerp_initialize_files_small_dir() {
    cout << "Test 31" << endl;
};

//   medium directory
void a32_Gerp_initialize_files_medium_dir() {
    cout << "Test 32" << endl;
};

//   new file
void a33_Gerp_read_file_open_stream_new_file() {
    cout << "Test 33" << endl;
};

//   hard to read file
void a34_Gerp_read_file_open_stream_unreadable_file() {
    cout << "Test 34" << endl;
};

//   existing file
void a35_Gerp_read_file_open_stream_reg_file() {
    cout << "Test 35" << endl;
};

//   non existent file id
void a36_Gerp_process_file_no_file_id() {
    cout << "Test 36" << endl;
};

//   hard to read file
void a38_Gerp_process_file_unreadable_file() {
    cout << "Test 38" << endl;
};

//   regular file
void a39_Gerp_process_file_reg_file() {
    cout << "Test 39" << endl;
};

//   empty file
void a40_Gerp_process_line_empty_file() {
    cout << "Test 40" << endl;
};

//   some populated lines, some un populated
void a41_Gerp_process_line_half_file() {
    cout << "Test 41" << endl;
};

//   fully populated file
void a42_Gerp_process_line_full_file() {
    cout << "Test 42" << endl;
};

//   uncleaned word
void a43_Gerp_add_to_hash_table_messy_word() {
    cout << "Test 43" << endl;
};

//   clean word
void a44_Gerp_add_to_hash_table_clean_word() {
    cout << "Test 44" << endl;
};

//   nonexistent file
void a45_Gerp_add_to_hash_table_no_file_id() {
    cout << "Test 45" << endl;
};

//   linenum greater than file length
void a46_Gerp_add_to_hash_table_great_line_num() {
    cout << "Test 46" << endl;
};

//   all inputs as expected
void a47_Gerp_add_to_hash_table_reg() {
    cout << "Test 47" << endl;
};

//   with @q
void a48_Gerp_quit_q() {
    cout << "Test 48" << endl;
};

//   with @quit
void a49_Gerp_quit_quit() {
    cout << "Test 49" << endl;
};
//@word@
void a50_Gerp_search_word_leading_and_trailing() {
    cout << "Test 50" << endl;
};

//wo@rd
void a51_Gerp_search_word_middle() {
    cout << "Test 51" << endl;
};

//word
void a52_Gerp_search_word() {
    cout << "Test 52" << endl;
};

//   @i word
void a53_Gerp_insensitive_search_i_word() {
    cout << "Test 53" << endl;
};

//   @insensitive word
void a54_Gerp_insensitive_search_insensitive_word() {
    cout << "Test 54" << endl;
};

//   @i @word@
void a55_Gerp_insensitive_search_i_leading_and_trailing() {
    cout << "Test 55" << endl;
};

//   @i wo&rd
void a56_Gerp_insensitive_search_i_word_middle() {
    cout << "Test 56" << endl;
};

//   @i word
void a57_Gerp_insensitive_search_1_word() {
    cout << "Test 57" << endl;
};

//
void a58_wordTable_expand_reg() {
    cout << "Test 58" << endl;
};

//
void a59_wordTable_hash_reg() {
    cout << "Test 59" << endl;
};

//
void a60_wordTable_contains_reg() {
    cout << "Test 60" << endl;
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
    a13_Gerp_run_before_quit();
    a14_Gerp_run_after_quit();
    // a15_Gerp_route_cmd_i_searchterm();
    // a16_Gerp_route_cmd_insensitve_searchterm();
    // a17_Gerp_route_cmd_searchterm();
    // a18_Gerp_route_cmd_searchterm_leading_and_trailing();
    // a19_Gerp_route_cmd_searchterm_middle();
    // a20_Gerp_route_cmd_quit();
    // a21_Gerp_route_cmd_quit();
    // a22_Gerp_route_cmd_f();
    // a23_Gerp_route_cmd_filename();
    // a24_Gerp_request_input_reg();
    // a25_Gerp_request_input_return();
    // a26_Gerp_request_input_one_word();
    // a27_Gerp_request_input_two_words();
    // a28_Gerp_request_input_three_words();
    // a29_Gerp_initialize_files_no_dir();
    a30_Gerp_initialize_files_empty_dir();
    a31_Gerp_initialize_files_small_dir();
    a32_Gerp_initialize_files_medium_dir();
    a33_Gerp_read_file_open_stream_new_file();
    a34_Gerp_read_file_open_stream_unreadable_file();
    a35_Gerp_read_file_open_stream_reg_file();
    a36_Gerp_process_file_no_file_id();
    a38_Gerp_process_file_unreadable_file();
    a39_Gerp_process_file_reg_file();
    a40_Gerp_process_line_empty_file();
    a41_Gerp_process_line_half_file();
    a42_Gerp_process_line_full_file();
    a43_Gerp_add_to_hash_table_messy_word();
    a44_Gerp_add_to_hash_table_clean_word();
    a45_Gerp_add_to_hash_table_no_file_id();
    a46_Gerp_add_to_hash_table_great_line_num();
    a47_Gerp_add_to_hash_table_reg();
    a48_Gerp_quit_q();
    a49_Gerp_quit_quit();
    a50_Gerp_search_word_leading_and_trailing();
    a51_Gerp_search_word_middle();
    a52_Gerp_search_word();
    a53_Gerp_insensitive_search_i_word();
    a54_Gerp_insensitive_search_insensitive_word();
    a55_Gerp_insensitive_search_i_leading_and_trailing();
    a56_Gerp_insensitive_search_i_word_middle();
    a57_Gerp_insensitive_search_1_word();
    a58_wordTable_expand_reg();
    a59_wordTable_hash_reg();
    a60_wordTable_contains_reg();

    return 0;
}