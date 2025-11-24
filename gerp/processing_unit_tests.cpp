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