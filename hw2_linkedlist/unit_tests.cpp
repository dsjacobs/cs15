/*
 *  unit_tests.cpp
 *  Danielle Jacobs
 *  09/25/2025
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to linked up in Fur
 *
 * These tests test all public functions in the Character Array List.
 * Functions are tested on arrays of size zero, one and many.
 * It is ensured that any expected errors are returned. 
 */

#include "CharLinkedList.h"
#include <cassert>
#include <iostream>
#include <iso646.h>
#include <stdexcept>
#include <string>

using namespace std;

// Validates that the file is running
void dummytest() { std::cout << "Unit Tests Running" << endl; }

// Tests the null constructor returns an empty instance with size 0
void null_constructor_one()
{
    std::cout << 1 << std::endl;
    CharLinkedList my_empt_inst;
    assert(my_empt_inst.size() == 0);
    assert(my_empt_inst.isEmpty());
}

// tests the character constructor returns an instance with size 1 with
// that character
void char_constructor_one()
{
    std::cout << 2 << std::endl;
    CharLinkedList my_c_inst = CharLinkedList('c');
    assert(not my_c_inst.isEmpty());
    assert(my_c_inst.size() == 1);
    assert(my_c_inst.elementAt(0) == 'c');
    assert(my_c_inst.toString() == "[CharLinkedList of size 1 <<c>>]");
}

// tests the many constructor returns an instance that size with that array
// on a given array of size 3
void many_constructor_many()
{
    std::cout << 3 << std::endl;
    char test_arr[3] = {'f', 'a', 'v'};
    int test_size = 3;
    CharLinkedList my_test_inst = CharLinkedList(test_arr, test_size);
    assert(my_test_inst.size() == 3);
    assert(my_test_inst.toString() == "[CharLinkedList of size 3 <<fav>>]");
}

// tests the many constructor returns an instance that size with that array
// on a given array of size 1
void many_constructor_one()
{
    std::cout << 4 << std::endl;

    char test_arr[1] = {'d'};
    int test_size = 1;
    CharLinkedList my_test_inst = CharLinkedList(test_arr, test_size);
    // assert(my_test_inst.size() == 1);
    // assert(my_test_inst.toString() == "[CharLinkedList of size 1 <<d>>]");
}

// tests the copy constructor returns an copy of the given instance
// with the same size and element on an instance of one
void copy_constructor_one()
{
    std::cout << 5 << std::endl;
    CharLinkedList my_c_inst = CharLinkedList('c');
    CharLinkedList my_copy(my_c_inst);
    assert(not my_copy.isEmpty());
    assert(my_copy.size() == 1);
    assert(my_copy.elementAt(0) == 'c');
    assert(my_copy.toString() == "[CharLinkedList of size 1 <<c>>]");
}

// tests the copy constructor returns an copy of the given instance
// with the same size and element on an instance of three
void copy_constructor_many()
{
    std::cout << 6 << std::endl;

    char test_arr[3] = {'f', 'a', 'v'};
    int test_size = 3;
    CharLinkedList my_test_inst = CharLinkedList(test_arr, test_size);
    CharLinkedList my_copy(my_test_inst);
    assert(my_copy.size() == 3);
    assert(my_copy.elementAt(0) == 'f');
    assert(my_copy.toString() == "[CharLinkedList of size 3 <<fav>>]");
}

// tests the copy constructor returns an copy of the given instance
// with the same size and element on an empty instance
void copy_constructor_zero()
{
    std::cout << 7 << std::endl;

    CharLinkedList my_empt_inst;
    CharLinkedList my_copy(my_empt_inst);
    assert(my_copy.isEmpty());
    assert(my_copy.toString() == "[CharLinkedList of size 0 <<>>]");
}

// tests the isempty function correctly determines an empty instance
void isEmpty_empty()
{
    std::cout << 8 << std::endl;
    CharLinkedList my_empt_inst;
    assert(my_empt_inst.isEmpty());
}

// tests the isempty function on an instance with one character
void isEmpty_notempty()
{
    std::cout << 9 << std::endl;
    CharLinkedList my_c_inst = CharLinkedList('c');
    assert(not my_c_inst.isEmpty());
}

// tests an instance is empty after running clear
void isClear_empty()
{
    std::cout << 10 << std::endl;
    CharLinkedList my_empt_inst;
    my_empt_inst.clear();
    assert(my_empt_inst.isEmpty());
}

// tests that clear returns an empty instance
void isClear_nonempty()
{
    std::cout << 11 << std::endl;
    CharLinkedList my_j_inst = CharLinkedList('j');
    assert(not my_j_inst.isEmpty());
    my_j_inst.clear();
    assert(my_j_inst.isEmpty());
}

// tests that an empty instance has a size of 0
void size_empty()
{
    std::cout << 12 << std::endl;
    CharLinkedList my_empt_inst;
    assert(my_empt_inst.size() == 0);
}

// tests that an instance of 1 has size 1
void size_one()
{
    std::cout << 13 << std::endl;
    CharLinkedList my_c_inst = CharLinkedList('c');
    assert(my_c_inst.size() == 1);
}

// tests that an instance of 3 has size 3
void size_many()
{
    std::cout << 14 << std::endl;
    char test_arr[3] = {'f', 'a', 'v'};
    int test_size = 3;
    CharLinkedList my_test_inst = CharLinkedList(test_arr, test_size);
    assert(my_test_inst.size() == 3);
}

// Tests correct insertion into an empty linked list.
// Afterwards, size should be 1 and element at index 0
// should be the element we inserted.
void insertAt_empty_correct()
{
    std::cout << 15 << std::endl;

    CharLinkedList test_list;
    assert(test_list.isEmpty());
    test_list.insertAt('a', 0);
    assert(test_list.size() == 1);
    assert(test_list.elementAt(0) == 'a');
}

// Tests incorrect insertion into an empty linked list.
// Attempts to call insertAt for index larger than 0.
// This should result in an std::range_error being raised.
void insertAt_empty_incorrect()
{
    std::cout << 16 << std::endl;

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharLinkedList test_list;
    try {
        // insertAt for out-of-range index
        test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..0]");
}

// Tests correct insertAt for front of 1-element list.
void insertAt_front_singleton_list()
{
    std::cout << 17 << std::endl;

    // initialize 1-element list
    CharLinkedList test_list('a');

    // insert at front
    test_list.insertAt('b', 0);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'b');
    assert(test_list.elementAt(1) == 'a');
    assert(test_list.toString() == "[CharLinkedList of size 2 <<ba>>]");
}

// Tests correct insertAt for back of 1-element list.
void insertAt_back_singleton_list()
{
    std::cout << 18 << std::endl;

    // initialize 1-element list
    CharLinkedList test_list('a');

    // insert at back
    test_list.insertAt('b', 1);

    assert(test_list.size() == 2);
    assert(test_list.elementAt(0) == 'a');
    assert(test_list.elementAt(1) == 'b');
}

// Tests calling insertAt for a large number of elements.
void insertAt_many_elements()
{
    std::cout << 19 << std::endl;

    CharLinkedList test_list;

    // insert 1000 elements
    for (int i = 0; i < 1000; i++) {
        // always insert at the back of the list
        test_list.insertAt('a', i);
    }
    assert(test_list.size() == 1000);
    for (int i = 0; i < 1000; i++) {
        assert(test_list.elementAt(i) == 'a');
    }
}

// Tests insertion into front of a larger list
void insertAt_front_large_list()
{
    std::cout << 20 << std::endl;

    char test_arr[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    CharLinkedList test_list(test_arr, 8);
    assert(test_list.size() == 8);

    test_list.insertAt('y', 0);

    assert(test_list.size() == 9);
    assert(test_list.elementAt(0) == 'y');
    std::string out_str = "[CharLinkedList of size 9 <<yabcdefgh>>]";
    assert(test_list.toString() == out_str);
}

// Tests insertion into the back of a larger list
void insertAt_back_large_list()
{
    std::cout << 21 << std::endl;

    char test_arr[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    CharLinkedList test_list(test_arr, 8);
    test_list.insertAt('x', 8);

    assert(test_list.size() == 9);
    assert(test_list.elementAt(8) == 'x');
    std::string out_str = "[CharLinkedList of size 9 <<abcdefghx>>]";
    assert(test_list.toString() == out_str);
}

// Tests insertion into the middle of a larger list
void insertAt_middle_large_list()
{
    std::cout << 22 << std::endl;

    char test_arr[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    CharLinkedList test_list(test_arr, 8);

    test_list.insertAt('z', 5);

    assert(test_list.size() == 9);
    assert(test_list.elementAt(5) == 'z');
    std::string out_str = "[CharLinkedList of size 9 <<abcdezfgh>>]";
    assert(test_list.toString() == out_str);
}

// Tests out-of-range insertion for a non-empty list.
void insertAt_nonempty_incorrect()
{

    std::cout << 23 << std::endl;

    char test_arr[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    CharLinkedList test_list(test_arr, 8);

    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    try {
        test_list.insertAt('a', 42);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (42) not in range [0..8]");
}

// makes sure that elementAt() throws an error when run on an
// empty instance.
void elementAt_empty()
{
    std::cout << 30 << std::endl;
    CharLinkedList empty_arr = CharLinkedList();
    bool range_error_thrown = false;
    std::string error_message = "";

    try {
        empty_arr.elementAt(16);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (16) not in range [0..0)");
}

// elementat(6) on an instance of 7 should return the last character
void elementAt_end()
{
    std::cout << 31 << std::endl;
    char test_arr[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    CharLinkedList test_list(test_arr, 7);
    assert(test_list.elementAt(6) == 'g');
}

// elementat(0) on an instance of 1 should return the last character
void elementAt_end_outofrange()
{
    std::cout << 31.5 << std::endl;
    char test_arr[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    CharLinkedList test_list(test_arr, 8);
    bool range_error_thrown = false;
    std::string error_message = "";
    try {
        test_list.elementAt(8);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    assert(range_error_thrown);
    assert(error_message == "index (8) not in range [0..8)");
}

// asking for the element at a negative index should throw an error
void elementAt_negative()
{
    std::cout << 32 << std::endl;
    CharLinkedList empty_arr = CharLinkedList();
    bool range_error_thrown = false;
    try {
        empty_arr.elementAt(-2);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
    }
    assert(range_error_thrown);
}

// builds a large array with a loop, which should cause multiple expansions
// and makes sure elementAt still works properly
void elementAt_loopily_built()
{
    std::cout << 33 << std::endl;
    CharLinkedList my_inst;
    for (int i = 0; i < 65; i++) {
        my_inst.insertAt('z', i);
    }
    assert(my_inst.size() == 65);
    assert(my_inst.elementAt(34) == 'z');
    assert(my_inst.first() == 'z');
    assert(my_inst.last() == 'z');
}

// elementat(0) on an instance of 1 should return the one character
void elementAt_one()
{
    std::cout << 34 << std::endl;
    CharLinkedList one_arr = CharLinkedList('g');
    assert(one_arr.elementAt(0) == 'g');
}

// asking for the first element of an empty instance should throw an error
void first_zero()
{
    std::cout << 38 << std::endl;

    CharLinkedList my_empt_inst;
    bool runtime_error_thrown = false;
    std::string error_message = "";
    try {
        my_empt_inst.first();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "cannot get first of empty LinkedList");
}

// asking for the first element of an instance of one should return
// the right character
void first_one()
{
    std::cout << 39 << std::endl;

    CharLinkedList my_c_inst = CharLinkedList('c');
    assert(my_c_inst.first() == 'c');
}

// asking for the first element of an instance of 8 should return
// the right character
void first_many()
{
    std::cout << 40 << std::endl;

    char test_arr[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    CharLinkedList test_list(test_arr, 8);
    assert(test_list.first() == 'a');
}

// asking for the last element of an empty instance should throw an error
void last_zero()
{
    std::cout << 41 << std::endl;

    CharLinkedList my_empt_inst;
    bool runtime_error_thrown = false;
    std::string error_message = "";
    try {
        my_empt_inst.last();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot get last of empty LinkedList");
}

// asking for the last element of an instance of one should return
// the right character
void last_one()
{
    std::cout << 42 << std::endl;

    CharLinkedList my_c_inst = CharLinkedList('c');
    assert(my_c_inst.last() == 'c');
}

// asking for the last element of an instance of 8 should return
// the right character
void last_many()
{
    std::cout << 43 << std::endl;

    char test_arr[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    CharLinkedList test_list(test_arr, 8);
    assert(test_list.last() == 'h');
}

// pushAtFront on an instance of 0 should return an instance of 1
// with the right character
void pushatfront_zero()
{
    std::cout << 52 << std::endl;

    CharLinkedList my_empt_inst;
    my_empt_inst.pushAtFront('j');
    assert(my_empt_inst.size() == 1);
    assert(my_empt_inst.first() == 'j');
    assert(my_empt_inst.toString() == "[CharLinkedList of size 1 <<j>>]");
}

// pushAtBack on an instance of 0 should return an instance of 1
// with the right character
void pushatback_zero()
{
    std::cout << 53 << std::endl;

    CharLinkedList my_empt_inst;
    my_empt_inst.pushAtBack('k');
    assert(my_empt_inst.size() == 1);
    assert(my_empt_inst.last() == 'k');
    assert(my_empt_inst.toString() == "[CharLinkedList of size 1 <<k>>]");
}

// pushAtFront on an instance of 8 should return an instance of 9
// with the right character
void pushatfront_many()
{
    std::cout << 54 << std::endl;

    char test_arr[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    CharLinkedList my_linkedlist(test_arr, 8);
    my_linkedlist.pushAtFront('z');
    assert(my_linkedlist.size() == 9);
    assert(my_linkedlist.first() == 'z');
    std::string out_str = "[CharLinkedList of size 9 <<zabcdefgh>>]";
    assert(my_linkedlist.toString() == out_str);
}

// pushAtBack on an instance of 8 should return an instance of 9
// with the right character
void pushatback_many()
{
    std::cout << 55 << std::endl;

    char test_arr[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    CharLinkedList my_linkedlist(test_arr, 8);
    my_linkedlist.pushAtBack('y');
    assert(my_linkedlist.size() == 9);
    assert(my_linkedlist.last() == 'y');
    assert(my_linkedlist.first() == 'a');
    std::string out_str = "[CharLinkedList of size 9 <<abcdefghy>>]";
    assert(my_linkedlist.toString() == out_str);
}

// pushAtFront on an instance of 1 should result in an instance of 2
void pushatfront_one()
{
    std::cout << 56 << std::endl;

    CharLinkedList my_m_inst = CharLinkedList('m');
    my_m_inst.pushAtFront('q');
    assert(my_m_inst.size() == 2);
    assert(my_m_inst.first() == 'q');
    assert(my_m_inst.last() == 'm');
    assert(my_m_inst.toString() == "[CharLinkedList of size 2 <<qm>>]");
}

// pushAtBack on an instance of 1 should result in an instance of 2
void pushatback_one()
{
    std::cout << 57 << std::endl;

    CharLinkedList my_m_inst = CharLinkedList('m');
    my_m_inst.pushAtBack('h');
    assert(my_m_inst.size() == 2);
    assert(my_m_inst.first() == 'm');
    assert(my_m_inst.last() == 'h');
    assert(my_m_inst.toString() == "[CharLinkedList of size 2 <<mh>>]");
}

// toString (and toReverseString) on an empty instance
//  should return "[CharLinkedList of size 0 <<>>]"
void toString_empty()
{
    std::cout << 35 << std::endl;

    CharLinkedList my_empt_inst;
    assert(my_empt_inst.toString() == "[CharLinkedList of size 0 <<>>]");
    std::string rev_string = "[CharLinkedList of size 0 <<>>]";
    assert(my_empt_inst.toReverseString() == rev_string);
};

// toString (and toReverseString) on an instance of 1 e
//  should return "[CharLinkedList of size 1 <<....>>]"
void toString_one()
{
    std::cout << 36 << std::endl;

    CharLinkedList my_y_inst = CharLinkedList('y');
    assert(my_y_inst.toString() == "[CharLinkedList of size 1 <<y>>]");
    assert(my_y_inst.toReverseString() == "[CharLinkedList of size 1 <<y>>]");
};

// toString (and toReverseString) on an instance of 8 e
//  should return "[CharLinkedList of size 8 <<....>>]" with the elements
//  forward and backward
void toString_many()
{
    std::cout << 37 << std::endl;

    char test_arr[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    CharLinkedList arrlist(test_arr, 8);
    assert(arrlist.toString() == "[CharLinkedList of size 8 <<abcdefgh>>]");
    std::string rev_string = "[CharLinkedList of size 8 <<hgfedcba>>]";
    assert(arrlist.toReverseString() == rev_string);
}

// insesrtInOrder on an empty instance results in an instance of 1 with
// the right character
void insertInOrder_zero()
{
    std::cout << 29 << std::endl;

    CharLinkedList my_empt_inst;
    my_empt_inst.insertInOrder('r');
    assert(my_empt_inst.size() == 1);
    assert(my_empt_inst.first() == 'r');
    assert(my_empt_inst.toString() == "[CharLinkedList of size 1 <<r>>]");
}

// insertInOrder on an instance of 1, where paramater character is less
// than existing character, results in an instance with size 2 and
// characters in the right order
void insertInOrder_one_beginning()
{
    std::cout << 27 << std::endl;

    CharLinkedList my_s_inst = CharLinkedList('s');
    my_s_inst.insertInOrder('r');
    assert(my_s_inst.size() == 2);
    assert(my_s_inst.first() == 'r');
    assert(my_s_inst.last() == 's');
    assert(my_s_inst.toString() == "[CharLinkedList of size 2 <<rs>>]");
}

// insertInOrder on an instance of 1, where paramater character is greater
// than existing character, results in an instance with size 2 and
// characters in the right order
void insertInOrder_one_end()
{
    std::cout << 28 << std::endl;

    CharLinkedList my_s_inst = CharLinkedList('s');
    my_s_inst.insertInOrder('t');
    assert(my_s_inst.size() == 2);
    assert(my_s_inst.first() == 's');
    assert(my_s_inst.last() == 't');
    assert(my_s_inst.toString() == "[CharLinkedList of size 2 <<st>>]");
}

// insertInOrder on an instance of 7, where paramater character is less
// than all characters, results in an instance with size 8 and
// characters in the right order
void insertInOrder_beginning()
{
    std::cout << 24 << std::endl;

    char test_arr[7] = {'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    CharLinkedList my_linkedlist(test_arr, 7);
    my_linkedlist.insertInOrder('a');
    assert(my_linkedlist.size() == 8);
    assert(my_linkedlist.first() == 'a');
    assert(my_linkedlist.elementAt(1) == 'b');
    assert(my_linkedlist.elementAt(2) == 'c');
    assert(my_linkedlist.toString() ==
           "[CharLinkedList of size 8 <<abcdefgh>>]");
}

// insertInOrder on an instance of 7, where paramater character is in the
// middle of all the characters, results in an instance with size 8 and
// characters in the right order
void insertInOrder_middle()
{
    std::cout << 26 << std::endl;

    char test_arr[7] = {'a', 'b', 'c', 'd', 'f', 'g', 'h'};
    CharLinkedList my_linkedlist(test_arr, 7);
    my_linkedlist.insertInOrder('e');

    assert(my_linkedlist.size() == 8);
    assert(my_linkedlist.first() == 'a');
    assert(my_linkedlist.elementAt(4) == 'e');
    assert(my_linkedlist.toString() ==
           "[CharLinkedList of size 8 <<abcdefgh>>]");
}

// insertInOrder on an instance of 7, where paramater character is after
// all characters, results in an instance with size 8 and
// characters in the right order
void insertInOrder_end()
{
    std::cout << 25 << std::endl;

    char test_arr[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    CharLinkedList my_linkedlist(test_arr, 7);
    my_linkedlist.insertInOrder('h');
    assert(my_linkedlist.size() == 8);
    assert(my_linkedlist.last() == 'h');
    assert(my_linkedlist.elementAt(4) == 'e');
    std::string out_str = "[CharLinkedList of size 8 <<abcdefgh>>]";
    assert(my_linkedlist.toString() == out_str);
}

// calling removeAt on an empty instance throws an error
void removeAt_zero()
{
    std::cout << 44 << std::endl;
    CharLinkedList my_empt_inst;
    bool range_error_thrown = false;
    std::string error_message = "";
    try {
        my_empt_inst.removeAt(0);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    assert(range_error_thrown);
    assert(error_message == "index (0) not in range [0..0)");
}

// calling removeAt on an empty instance with a higher
// index also throws an error
void removeAt_zero_nonzero()
{
    std::cout << 51 << std::endl;

    CharLinkedList my_empt_inst;
    bool range_error_thrown = false;
    std::string error_message = "";
    try {
        my_empt_inst.removeAt(3);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (3) not in range [0..0)");
}

// calling removeAt on an instance of 1 at index 2
// index also throws an error
void removeAt_many_outofrange()
{
    std::cout << 49 << std::endl;

    CharLinkedList my_c_inst('c');
    bool range_error_thrown = false;
    std::string error_message = "";
    try {
        my_c_inst.removeAt(2);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    assert(range_error_thrown);
    assert(error_message == "index (2) not in range [0..1)");
}

// calling removeAt correctly on an instance of 1
// results in an empty instance
void removeAt_one()
{
    std::cout << 45 << std::endl;

    CharLinkedList my_c_inst('c');
    my_c_inst.removeAt(0);
    assert(my_c_inst.isEmpty());
}

// calling removeAt on an instance of 1
// with an out of range index throws an error
void removeAt_one_error()
{
    std::cout << 50 << std::endl;

    CharLinkedList my_c_inst('c');
    bool range_error_thrown = false;
    std::string error_message = "";
    try {
        my_c_inst.removeAt(3);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    assert(range_error_thrown);
    assert(error_message == "index (3) not in range [0..1)");
}

// calling removeAt on an instance of 7
// with an index of 0 removes the first element
// and results in a size of 6
void removeAt_beginning()
{
    std::cout << 46 << std::endl;

    char test_arr[7] = {'a', 'b', 'c', 'd', 'f', 'g', 'h'};
    CharLinkedList my_linkedlist(test_arr, 7);
    my_linkedlist.removeAt(0);
    assert(my_linkedlist.size() == 6);
    assert(my_linkedlist.first() == 'b');
    assert(my_linkedlist.toString() == "[CharLinkedList of size 6 <<bcdfgh>>]");
}

// calling removeAt on an instance of 7
// with an index of 2 removes the third element
// and results in a size of 6
void removeAt_mid()
{
    std::cout << 47 << std::endl;

    char test_arr[7] = {'a', 'b', 'c', 'd', 'f', 'g', 'h'};
    CharLinkedList my_linkedlist(test_arr, 7);
    my_linkedlist.removeAt(2);
    assert(my_linkedlist.size() == 6);
    assert(my_linkedlist.elementAt(2) == 'd');
    assert(my_linkedlist.toString() == "[CharLinkedList of size 6 <<abdfgh>>]");
}

// calling removeAt on an instance of 7
// with an index of 6 removes the last element
// and results in a size of 6
void removeAt_end()
{
    std::cout << 48 << std::endl;

    char test_arr[7] = {'a', 'b', 'c', 'd', 'f', 'g', 'h'};
    CharLinkedList my_linkedlist(test_arr, 7);
    my_linkedlist.removeAt(6);
        std::cout << 48 << std::endl;

    assert(my_linkedlist.size() == 6);
    assert(my_linkedlist.last() == 'g');
    assert(my_linkedlist.toString() == "[CharLinkedList of size 6 <<abcdfg>>]");
}

// calling popfromfront on an empty instance calls an error
void popfromfront_zero()
{
    std::cout << 63 << std::endl;
    CharLinkedList my_empt_inst;
    bool runtime_error_thrown = false;
    std::string error_message = "";
    try {
        my_empt_inst.popFromFront();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }

    assert(runtime_error_thrown);
    assert(error_message == "cannot pop from empty LinkedList");
};

// calling popfromfront on an instance of one makes an empty instance
void popfromfront_one()
{
    std::cout << 62 << std::endl;
    CharLinkedList my_c_inst('c');
    my_c_inst.popFromFront();
    assert(my_c_inst.isEmpty());
};

// calling popfromfront on an instance of 7 makes an instance of 6
// and removes the first character
void popfromfront_many()
{
    std::cout << 61 << std::endl;

    char test_arr[7] = {'a', 'b', 'c', 'd', 'f', 'g', 'h'};
    CharLinkedList my_linkedlist(test_arr, 7);
    my_linkedlist.popFromFront();
    assert(my_linkedlist.size() == 6);
    assert(my_linkedlist.first() == 'b');
    assert(my_linkedlist.toString() == "[CharLinkedList of size 6 <<bcdfgh>>]");
};

// calling popfromback on an empty instance calls an error
void popfromback_zero()
{
    std::cout << 60 << std::endl;

    CharLinkedList my_empt_inst;
    bool runtime_error_thrown = false;
    std::string error_message = "";
    try {
        my_empt_inst.popFromBack();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    // out here, we make our assertions
    assert(runtime_error_thrown);
    assert(error_message == "cannot pop from empty LinkedList");
};

// calling popfromback on an instance of one makes an empty instance
void popfromback_one()
{
    std::cout << 59 << std::endl;

    CharLinkedList my_c_inst('c');
    my_c_inst.popFromBack();
    assert(my_c_inst.isEmpty());
};

// calling popfromback on an instance of 7 makes an instance of 6
// and removes the last character
void popfromback_many()
{
    std::cout << 58 << std::endl;

    char test_arr[7] = {'a', 'b', 'c', 'd', 'f', 'g', 'h'};
    CharLinkedList my_linkedlist(test_arr, 7);
    my_linkedlist.popFromBack();

    assert(my_linkedlist.size() == 6);
    assert(my_linkedlist.last() == 'g');
    assert(my_linkedlist.toString() == "[CharLinkedList of size 6 <<abcdfg>>]");
};

// calling replace on an empty instance throws an error
void replace_empty()
{
    std::cout << 65 << std::endl;

    CharLinkedList my_empt_inst;
    bool range_error_thrown = false;
    std::string error_message = "";
    try {
        my_empt_inst.replaceAt('b', 4);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }

    assert(range_error_thrown);
    assert(error_message == "index (4) not in range [0..0)");
}

// calling replace on an instance of 1 replaces the character
void replace_one()
{
    std::cout << 68 << std::endl;

    CharLinkedList my_j_inst('j');
    my_j_inst.replaceAt('k', 0);
    assert(my_j_inst.size() == 1);
    assert(my_j_inst.first() == 'k');
}

// calling replace at the beginning of a 7 character list
// replaces the character
void replace_beginning()
{
    std::cout << 64 << std::endl;

    char test_arr[7] = {'a', 'b', 'c', 'd', 'f', 'g', 'h'};
    CharLinkedList my_linkedlist(test_arr, 7);
    my_linkedlist.replaceAt('k', 0);
    assert(my_linkedlist.first() == 'k');
    assert(my_linkedlist.toString() ==
           "[CharLinkedList of size 7 <<kbcdfgh>>]");
}

// calling replace in the middle of a 7 character list
// replaces the character
void replace_mid()
{
    std::cout << 67 << std::endl;

    char test_arr[7] = {'a', 'b', 'c', 'd', 'f', 'g', 'h'};
    CharLinkedList my_linkedlist(test_arr, 7);
    my_linkedlist.replaceAt('k', 5);
    assert(my_linkedlist.elementAt(5) == 'k');
    assert(my_linkedlist.toString() ==
           "[CharLinkedList of size 7 <<abcdfkh>>]");
}

// calling replace at the end of a 7 character list
// replaces the character
void replace_end()
{
    std::cout << 66 << std::endl;

    char test_arr[7] = {'a', 'b', 'c', 'd', 'f', 'g', 'h'};
    CharLinkedList my_linkedlist(test_arr, 7);
    my_linkedlist.replaceAt('k', 6);
    assert(my_linkedlist.last() == 'k');
    assert(my_linkedlist.toString() ==
           "[CharLinkedList of size 7 <<abcdfgk>>]");
}

// calling replace on an index greater than the list size
// throws an error
void replace_outofrange()
{
    std::cout << 69 << std::endl;

    char test_arr[7] = {'a', 'b', 'c', 'd', 'f', 'g', 'h'};
    CharLinkedList my_linkedlist(test_arr, 7);
    std::string error_message = "";
    bool error_thrown = false;
    try {
        my_linkedlist.replaceAt('b', 20);
    }
    catch (const std::range_error &e) {
        error_thrown = true;
        error_message = e.what();
    }
    // out here, we make our assertions
    assert(error_thrown);
    assert(error_message == "index (20) not in range [0..7)");
}

// concatenating two empty lists results in an empty list
void concat_empty_to_empty()
{
    std::cout << 70 << std::endl;

    CharLinkedList empt_a;
    CharLinkedList empt_b;
    empt_a.concatenate(&empt_b);
    assert(empt_a.isEmpty());
}

// concatenating an empty list onto a list of 1 results in an list of 1
void concat_empty_to_one()
{
    std::cout << 71 << std::endl;

    CharLinkedList empt_a;
    CharLinkedList one_b('k');
    one_b.concatenate(&empt_a);
    assert(one_b.size() == 1);
}

// concatenating an list of 1 onto an empty list results in a list of 1
void concat_one_to_empty()
{
    std::cout << 72 << std::endl;

    CharLinkedList one_a('k');
    CharLinkedList empt_b;
    empt_b.concatenate(&one_a);
    assert(empt_b.size() == 1);
    assert(empt_b.first() == 'k');
}

// concatenating an instance of 3 to an instance of 4 results in an instance
// of 7 with the right characters
void concat_many_to_many()
{
    std::cout << 73 << std::endl;

    char list_a[4] = {'a', 'b', 'c', 'd'};
    char list_b[3] = {'k', 'l', 'm'};
    CharLinkedList arr_a = CharLinkedList(list_a, 4);
    CharLinkedList arr_b = CharLinkedList(list_b, 3);
    arr_a.concatenate(&arr_b);
    assert(arr_a.size() == 7);
    assert(arr_a.toString() == "[CharLinkedList of size 7 <<abcdklm>>]");
}

void assignment_operator_one() {
    std::cout << 74 << std::endl;
    CharLinkedList one('j');
    CharLinkedList my_empt_inst;
    my_empt_inst = one;
    assert(my_empt_inst.size()==1);
    std::string out_str = "[CharLinkedList of size 1 <<j>>]";
    assert(my_empt_inst.toString() == out_str);
}

void assignment_operator_many() {
    std::cout << 75 << std::endl;
    char list_b[3] = {'k', 'l', 'm'};
    CharLinkedList arr_b = CharLinkedList(list_b, 3);
    CharLinkedList copy;
    copy = arr_b;
    assert(copy.size()==3);
    std::string out_str = "[CharLinkedList of size 3 <<klm>>]";
    assert(copy.toString() == out_str);
}

void assignment_operator_empty() {
    std::cout << 76 << std::endl;
    CharLinkedList one;
    CharLinkedList copy('h');
    copy = one;
    assert(copy.isEmpty());
    assert(copy.toString() == "[CharLinkedList of size 0 <<>>]");
}

int main()
{

    dummytest(); // 0

    null_constructor_one();  // 1
    char_constructor_one();  // 2
    many_constructor_many(); // 3
    many_constructor_one();  // 4
    copy_constructor_one();  // 5
    copy_constructor_many(); // 6
    copy_constructor_zero(); // 7

    isEmpty_empty();    // 8
    isEmpty_notempty(); // 9
    isClear_empty();    // 10
    isClear_nonempty(); // 11
    size_empty();       // 12
    size_one();         // 13
    size_many();        // 14

    insertAt_empty_correct();        // 15
    insertAt_empty_incorrect();      // 16
    insertAt_front_singleton_list(); // 17
    insertAt_back_singleton_list();  // 18m
    insertAt_many_elements();        // 19
    insertAt_front_large_list();     // 20
    insertAt_middle_large_list();    // 21
    insertAt_back_large_list();      // 22
    insertAt_nonempty_incorrect();   // 23

    insertInOrder_beginning();     // 24
    insertInOrder_end();           // 25
    insertInOrder_middle();        // 26
    insertInOrder_one_beginning(); // 27
    insertInOrder_one_end();       // 28
    insertInOrder_zero();          // 29

    elementAt_empty();         // 30
    elementAt_end();           // 31
    elementAt_end_outofrange(); //31.5
    elementAt_negative();      // 32
    elementAt_loopily_built(); // 33
    elementAt_one();           // 34

    toString_empty(); // 35
    toString_one();   // 36
    toString_many();  // 37

    first_zero(); // 38
    first_one();  // 39
    first_many(); // 40
    last_zero();  // 41
    last_one();   // 42
    last_many();  // 43

    removeAt_zero();            // 44
    removeAt_one();             // 45
    removeAt_beginning();       // 46
    removeAt_mid();             // 47
    removeAt_end();             // 48
    removeAt_many_outofrange(); // 49
    removeAt_one_error();       // 50
    removeAt_zero_nonzero();    // 51

    pushatfront_zero(); // 52
    pushatback_zero();  // 53
    pushatfront_many(); // 54
    pushatback_many();  // 55
    pushatfront_one();  // 56
    pushatback_one();   // 57

    popfromback_many();  // 58
    popfromback_one();   // 59
    popfromback_zero();  // 60
    popfromfront_many(); // 61
    popfromfront_one();  // 62
    popfromfront_zero(); // 63

    replace_beginning();  // 64
    replace_empty();      // 65
    replace_end();        // 66
    replace_mid();        // 67
    replace_one();        // 68
    replace_outofrange(); // 69

    concat_empty_to_empty(); // 70
    concat_empty_to_one();   // 71
    concat_one_to_empty();   // 72
    concat_many_to_many();   // 73

    assignment_operator_one(); //74
    assignment_operator_many(); //75
    assignment_operator_empty(); //76

    return 0;
}
