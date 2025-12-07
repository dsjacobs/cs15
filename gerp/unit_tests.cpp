/*
Danielle Jacobs
November 23
Gerp
Unit Tests for Processing.h of phase 1

Tests alphanumeric character stripping and directory traversal
*/
#include processing.h
#include <cassert>
#include <iostream>


//tests that a fully alphanumeric word remains unchanged
void 01_Processing_stripNonAlphaNum_reg_word() {
    string input = "Banana123";
    string output = stripNonAlphaNum(input);
    assert(output == "Banana123");
};

//tests leading characters are stripped
void 02_Processing_stripNonAlphaNum_trail_beg() {
    string input = "!!Banana456";
    string output = stripNonAlphaNum(input);
    assert(output == "Banana456");
};

//tests trailing characters are stripped
void 03_Processing_stripNonAlphaNum_trail_end() {
    string input = "Banana456@@";
    string output = stripNonAlphaNum(input);
    assert(output == "Banana456");
};

//tests both leading and trailing characters are stripped
void 04_Processing_stripNonAlphaNum_trail_both() {
    string input = "##Banana456%%";
    string output = stripNonAlphaNum(input);
    assert(output == "Banana456");
};

//tests non alpha-numeric characters in the middle of the string stay
void 05_Processing_stripNonAlphaNum_mid() {
    string input = "Ban&ana45@62";
    string output = stripNonAlphaNum(input);
    assert(output == "Ban&ana45@62");
};

//tests string cleaning on a non alpha-numeric string returns empty string
void 06_Processing_stripNonAlphaNum_none() {
    string input = "@#$%###*";
    string output = stripNonAlphaNum(input);
    assert(output == "");
};

//tests the directory traversal
void 07_Processing_traverseDirectory_dir() {
    traverseDirectory("gerp-test-dirs/small-dir");
};

//non existent input directory
void 08_Gerp_gerp_no_input_dir() {
    traverseDirectory("gerp-test-dirs/banana");
};

//non existent output file
void 09_Gerp_gerp_no_output_file() {
    gerp::gerp("gerp-test-dirs/small-dir", "/not_there.txt");
};

//existing input directory and output file
void 10_Gerp_gerp_input_and_output() {
    gerp::gerp("gerp-test-dirs/small-dir", "gerp-output.txt");
};

//   create of_stream on working stream
void 11_Gerp_create_ofstream_working_stream() {};

//   create ofstream on not working stream
void 12_Gerp_create_ofstream_not_working_stream() {};

//before quit
void 13_Gerp_run_before_quit() {
    gerp::run();
};

//after quit
void 14_Gerp_run_after_quit() {
    gerp::run();
};

//   route cmd on @i searchterm
void 15_Gerp_route_cmd_i_searchterm() {
    gerp::route_cmd("@i searchterm");
};

//   route cmd on @insensitve searchterm
void 16_Gerp_route_cmd_insensitve_searchterm() {
    gerp::route_cmd("@insensitive searchterm");
};

//   route cmd on searchterm
void 17_Gerp_route_cmd_searchterm() {
    gerp::route_cmd("searchterm");
};

//   route cmd on $$seartchterm%%
void 18_Gerp_route_cmd_%%searchterm%%() {
    gerp::route_cmd("%%searchterm%%");
};

//   route cmd on search&&term
void 19_Gerp_route_cmd_search&term() {
    gerp::route_cmd("search&term");
};

//   route cmd on @quit
void 20_Gerp_route_cmd_quit() {
    gerp::route_cmd("@quit");
};

//   rout cmd on @q
void 21_Gerp_route_cmd_quit() {
    gerp::route_cmd("@q");
};

//   route cmd on @f filename
void 22_Gerp_route_cmd_f() {
    gerp::route_cmd("@f filename");
};

//   route cmd on @fab
void 23_Gerp_route_cmd_filename() {
    gerp::route_cmd("@fab");
};

//   prints the message query?
void 24_Gerp_request_input_reg() {};

//   returns whatever was put in
void 25_Gerp_request_input_return() {};

//   one word
void 26_Gerp_request_input_one_word() {};

//   two words
void 27_Gerp_request_input_two_words() {};

//   three words
void 28_Gerp_request_input_three_words() {};

//   no directory
void 29_Gerp_initialize_files_no_dir() {};

//   empty directory
void 30_Gerp_initialize_files_empty_dir() {};

//   small directory
void 31_Gerp_initialize_files_small_dir() {};

//   medium directory
void 32_Gerp_initialize_files_medium_dir() {};

//   new file
void 33_Gerp_read_file_open_stream_new_file() {};

//   hard to read file
void 34_Gerp_read_file_open_stream_unreadable_file() {};

//   existing file
void 35_Gerp_read_file_open_stream_reg_file() {};

//   non existent file id
void 36_Gerp_process_file_no_file_id() {};

//   hard to read file
void 38_Gerp_process_file_unreadable_file() {};

//   regular file
void 39_Gerp_process_file_reg_file() {};

//   empty file
void 40_Gerp_process_line_empty_file() {};

//   some populated lines, some un populated
void 41_Gerp_process_line_half_file() {};

//   fully populated file
void 42_Gerp_process_line_full_file() {};

//   uncleaned word
void 43_Gerp_add_to_hash_table_messy_word() {};

//   clean word
void 44_Gerp_add_to_hash_table_clean_word() {};

//   nonexistent file
void 45_Gerp_add_to_hash_table_no_file_id() {};

//   linenum greater than file length
void 46_Gerp_add_to_hash_table_great_line_num() {};

//   all inputs as expected
void 47_Gerp_add_to_hash_table_reg() {};

//   with @q
void 48_Gerp_quit_q() {};

//   with @quit
void 49_Gerp_quit_quit() {};

//@word@
void 50_Gerp_search_@word@() {};

//wo@rd
void 51_Gerp_search_wo@rd() {};

//word
void 52_Gerp_search_word() {};

//   @i word
void 53_Gerp_insensitive_search_i_word() {};

//   @insensitive word
void 54_Gerp_insensitive_search_insensitive_word() {};

//   @i @word@
void 55_Gerp_insensitive_search_i_@word@() {};

//   @i wo&rd
void 56_Gerp_insensitive_search_i_wo#rd() {};

//   @i word
void 57_Gerp_insensitive_search_1_word() {};

//
void 58_wordTable_expand_reg() {};

//
void 59_wordTable_hash_reg() {};

//
void 60_wordTable_contains_reg() {};


int main () {

    01_Processing_stripNonAlphaNum_reg_word();
    02_Processing_stripNonAlphaNum_trail_beg();
    03_Processing_stripNonAlphaNum_trail_end();
    04_Processing_stripNonAlphaNum_trail_both();
    05_Processing_stripNonAlphaNum_mid();
    06_Processing_stripNonAlphaNum_none();
    07_Processing_traverseDirectory_dir();
    08_Gerp_gerp_no_input_dir();
    09_Gerp_gerp_no_output_file();
    10_Gerp_gerp_input_and_output();
    11_Gerp_create_ofstream_working_stream();
    12_Gerp_create_ofstream_not_working_stream();
    13_Gerp_run_before_quit();
    14_Gerp_run_after_quit();
    15_Gerp_route_cmd_i_searchterm();
    16_Gerp_route_cmd_insensitve_searchterm();
    17_Gerp_route_cmd_searchterm();
    18_Gerp_route_cmd_%%searchterm%%();
    19_Gerp_route_cmd_search&term();
    20_Gerp_route_cmd_quit();
    21_Gerp_route_cmd_quit();
    22_Gerp_route_cmd_f();
    23_Gerp_route_cmd_filename();
    24_Gerp_request_input_reg();
    25_Gerp_request_input_return();
    26_Gerp_request_input_one_word();
    27_Gerp_request_input_two_words();
    28_Gerp_request_input_three_words();
    29_Gerp_initialize_files_no_dir();
    30_Gerp_initialize_files_empty_dir();
    31_Gerp_initialize_files_small_dir();
    32_Gerp_initialize_files_medium_dir();
    33_Gerp_read_file_open_stream_new_file();
    34_Gerp_read_file_open_stream_unreadable_file();
    35_Gerp_read_file_open_stream_reg_file();
    36_Gerp_process_file_no_file_id();
    38_Gerp_process_file_unreadable_file();
    39_Gerp_process_file_reg_file();
    40_Gerp_process_line_empty_file();
    41_Gerp_process_line_half_file();
    42_Gerp_process_line_full_file();
    43_Gerp_add_to_hash_table_messy_word();
    44_Gerp_add_to_hash_table_clean_word();
    45_Gerp_add_to_hash_table_no_file_id();
    46_Gerp_add_to_hash_table_great_line_num();
    47_Gerp_add_to_hash_table_reg();
    48_Gerp_quit_q();
    49_Gerp_quit_quit();
    50_Gerp_search_@word@();
    51_Gerp_search_wo@rd();
    52_Gerp_search_word();
    53_Gerp_insensitive_search_i_word();
    54_Gerp_insensitive_search_insensitive_word();
    55_Gerp_insensitive_search_i_@word@();
    56_Gerp_insensitive_search_i_wo#rd();
    57_Gerp_insensitive_search_1_word();
    58_wordTable_expand_reg();
    59_wordTable_hash_reg();
    60_wordTable_contains_reg();

    return 0;
}