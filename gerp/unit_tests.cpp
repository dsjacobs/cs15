/*
Danielle Jacobs
November 23
Gerp
Unit Tests for Processing.h of phase 1

Tests alphanumeric character stripping and directory traversal
*/
#include "processing.h"
#include <cassert>
#include <iostream>


// Processing
// tests that a fully alphanumeric word remains unchanged
void reg_word() {
    string input = "hello";
    assert(stripNonAlphaNum(input)==input);
}

// tests leading characters are stripped
void trail_beg() {
    string input = "&&!hello";
    assert(stripNonAlphaNum(input)=="hello");
}

// tests trailing characters are stripped
void trail_end() {
    string input = "hello?$?";
    assert(stripNonAlphaNum(input)=="hello");
}

// tests both leading and trailing characters are stripped
void trail_both() {
    string input = "&&!hello?$?";
    assert(stripNonAlphaNum(input)=="hello");
}

// tests non alpha-numeric characters in the middle of the string stay
void mid() {
    string input = "&&!hel!!lo?$?";
    assert(stripNonAlphaNum(input)=="hel!!lo");
}

// tests string cleaning on a non alpha-numeric string returns empty string
void none() {
    string input = "&&!#$%*()";
    assert(stripNonAlphaNum(input)=="");
}

// tests the directory traversal
void dir() {
    traverseDirectory("gerp-test-dirs/tinyData");
}

// GERP.CPP
//gerp::gerp
    // non existend input directory
    // non existent output file
    // existing input directory and output file

// gerp::create_ofstream
    // create of_stream on working stream
    // create ofstream on not working stream

// gerp::run
    // before quit
    // after quit

// gerp::route_cmd
    // route cmd on @i searchterm
    // route cmd on @insensitve searchterm
    // route cmd on searchterm
    // route cmd on $$seartchterm%%
    // route cmd on search&&term
    // route cmd on @quit
    // rout cmd on @q
    // route cmd on @f filename
    // route cmd on @fab

// gerp::request_input
    // prints the message query?
    // returns whatever was put in
    // one word
    // two words
    // three words

// gerp:: initialize_files
    // no directory
    // empty directory
    // small directory
    // medium directory

// gerp::  read_file_open_stream
    // new file
    // hard to read file
    // existing file

// gerp::process_file
    // non existent file id
    // non existent file id
    // hard to read file
    // regular file

// gerp::process_line
    // empty file
    // some populated lines, some un populated
    // fully populated file

// gerp::add_to_hash_table
    // uncleaned word
    // clean word
    // nonexistent file
    // linenum greater than file length
    // all inputs as expected

// gerp::quit
    // with @q
    // with @quit

// gerp::search
    // @word@
    //wo@rd
    // word

// gerp::insensitive search
    // @i word
    // @insensitive word
    // @i @word@
    // @i wo&rd
    // @i word

// wordTable.cpp

// wordTable::expand
// wordTable::reHash
// wordTable::contains

int main () {
    reg_word();
    trail_beg();
    trail_end();
    trail_both();
    mid();
    none();
    dir();
    return 0;
}