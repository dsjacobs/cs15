/*
 * unit_tests.cpp
 *
 * CS 15 homework 1
 * Tyler Calabrese, January 2021 
 * edited by: Milod Kazerounian, January 2022
 * edited by: Danielle Jacobs
 * 
 * September 12, 2025
 * 
 * These tests test all public functions in the Character Array List.
 * Functions are tested on arrays of size zero, one and many.
 * It is ensured that eny expected errors are returned.
 */

#include "CharArrayList.h"
#include <cassert>
#include <iostream>
using namespace std;

// Validates that the file is running
void dummytest() {std::cout << "Unit Tests Running" << endl;}

// Tests the null constructor returns an empty instance with size 0
void null_constructor_one(){
    CharArrayList my_empt_inst;
    assert(my_empt_inst.size()==0);
    assert(my_empt_inst.isEmpty());
}

// tests the character constructor returns an instance with size 1 with 
// that character
void char_constructor_one(){
    CharArrayList my_c_inst = CharArrayList('c');
    assert(not my_c_inst.isEmpty());
    assert(my_c_inst.size()==1);
    assert(my_c_inst.elementAt(0)=='c');
    assert(my_c_inst.toString()=="[CharArrayList of size 1 <<c>>]");
}

// tests the many constructor returns an instance that size with that array
// on a given array of size 3
void many_constructor_many() {
    char test_arr[3] = {'f','a','v'};
    int test_size = 3;
    CharArrayList my_test_inst = CharArrayList(test_arr, test_size);
    assert(my_test_inst.size()==3);
    assert(my_test_inst.toString()=="[CharArrayList of size 3 <<fav>>]");
}

// tests the many constructor returns an instance that size with that array
// on a given array of size 1
void many_constructor_one() {
    char test_arr[1] = {'d'};
    int test_size = 1;
    CharArrayList my_test_inst = CharArrayList(test_arr, test_size);
    assert(my_test_inst.size()==1);
    assert(my_test_inst.toString()=="[CharArrayList of size 1 <<d>>]");
}

// tests the copy constructor returns an copy of the given instance
// with the same size and element on an instance of one 
void copy_constructor_one() {
    CharArrayList my_c_inst = CharArrayList('c');
    CharArrayList my_copy(my_c_inst);
    assert(not my_copy.isEmpty());
    assert(my_copy.size()==1);
    assert(my_copy.elementAt(0)=='c');   
    assert(my_copy.toString()=="[CharArrayList of size 1 <<c>>]");
}

// tests the copy constructor returns an copy of the given instance
// with the same size and element on an instance of three
void copy_constructor_many() {
    char test_arr[3] = {'f','a','v'};
    int test_size = 3;
    CharArrayList my_test_inst = CharArrayList(test_arr, test_size);
    CharArrayList my_copy(my_test_inst);
    assert(my_copy.size()==3);
    assert(my_copy.elementAt(0)=='f');
    assert(my_copy.toString()=="[CharArrayList of size 3 <<fav>>]");

}

// tests the copy constructor returns an copy of the given instance
// with the same size and element on an empty instance
void copy_constructor_zero() {
    CharArrayList my_empt_inst;
    CharArrayList my_copy(my_empt_inst);
    assert(my_copy.isEmpty());
    assert(my_copy.toString()=="[CharArrayList of size 0 <<>>]");
}

// tests the isempty function correctly determines an empty instance
void isEmpty_empty() {

    CharArrayList my_empt_inst;
    assert(my_empt_inst.isEmpty());
}

// tests the isempty function on an instance with one character
void isEmpty_notempty() {
    CharArrayList my_c_inst = CharArrayList('c');
    assert(not my_c_inst.isEmpty());
}

// tests an instance is empty after running clear
void isClear_empty() {
    CharArrayList my_empt_inst;
    my_empt_inst.clear();
    assert(my_empt_inst.isEmpty());
}

// tests that clear returns an empty instance
void isClear_nonempty() {
    CharArrayList my_j_inst = CharArrayList('j');
    assert(not my_j_inst.isEmpty());
    my_j_inst.clear();
    assert(my_j_inst.isEmpty());
}

// tests that an empty instance has a size of 0
void size_empty() {
    CharArrayList my_empt_inst;
    assert(my_empt_inst.size()==0);
}

// tests that an instance of 1 has size 1
void size_one() {
    CharArrayList my_c_inst = CharArrayList('c');
    assert(my_c_inst.size()==1);
}

// tests that an instance of 3 has size 3
void size_many() {
    char test_arr[3] = {'f','a','v'};
    int test_size = 3;
    CharArrayList my_test_inst = CharArrayList(test_arr, test_size);
    assert(my_test_inst.size()==3);
}


// Tests correct insertion into an empty AL.
// Afterwards, size should be 1 and element at index 0
// should be the element we inserted.
void insertAt_empty_correct() {
        CharArrayList test_list;
        assert(test_list.isEmpty());
        test_list.insertAt('a', 0);
        assert(test_list.size()==1);
        assert(test_list.elementAt(0)=='a');
}

// Tests incorrect insertion into an empty AL.
// Attempts to call insertAt for index larger than 0.
// This should result in an std::range_error being raised.
void insertAt_empty_incorrect() {
    
    // var to track whether range_error is thrown
    bool range_error_thrown = false;

    // var to track any error messages raised
    std::string error_message = "";

    CharArrayList test_list;
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
    assert(error_message=="index (42) not in range [0..0]");    
}

// Tests correct insertAt for front of 1-element list.
void insertAt_front_singleton_list() {
    // initialize 1-element list
    CharArrayList test_list('a');

    // insert at front
    test_list.insertAt('b', 0);

    assert(test_list.size()==2);
    assert(test_list.elementAt(0)=='b');
    assert(test_list.elementAt(1)=='a');
    assert(test_list.toString()=="[CharArrayList of size 2 <<ba>>]");
}

// Tests correct insertAt for back of 1-element list.
void insertAt_back_singleton_list() {
    // initialize 1-element list
    CharArrayList test_list('a');

    // insert at back
    test_list.insertAt('b', 1);

    assert(test_list.size()==2);
    assert(test_list.elementAt(0)=='a');
    assert(test_list.elementAt(1)=='b');
}

// Tests calling insertAt for a large number of elements.
// Not only does this test insertAt, it also checks that
// array expansion works correctly.
void insertAt_many_elements() {
    CharArrayList test_list;

    // insert 1000 elements
    for (int i = 0; i < 1000; i++) {
        // always insert at the back of the list
        test_list.insertAt('a', i);
    }

    assert(test_list.size()==1000);

    for (int i = 0; i < 1000; i++) {
        assert(test_list.elementAt(i)=='a');
    }
}

// Tests insertion into front of a larger list
void insertAt_front_large_list() {
        char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
        CharArrayList test_list(test_arr, 8);

        test_list.insertAt('y', 0);

        assert(test_list.size()==9);
        assert(test_list.elementAt(0)=='y');
        std::string out_str = "[CharArrayList of size 9 <<yabcdefgh>>]"; 
        assert(test_list.toString()==out_str);
}

// Tests insertion into the back of a larger list
void insertAt_back_large_list() {
        char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
        CharArrayList test_list(test_arr, 8);
        test_list.insertAt('x', 8);

        assert(test_list.size()==9);
        assert(test_list.elementAt(8)=='x');
        std::string out_str = "[CharArrayList of size 9 <<abcdefghx>>]"; 
        assert(test_list.toString()==out_str);
}

// Tests insertion into the middle of a larger list
void insertAt_middle_large_list() {
        char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
        CharArrayList test_list(test_arr, 8);

        test_list.insertAt('z', 3);

        assert(test_list.size()==9);
        assert(test_list.elementAt(3)=='z');
        std::string out_str = "[CharArrayList of size 9 <<abczdefgh>>]";
        assert(test_list.toString()==out_str);
}

// Tests out-of-range insertion for a non-empty list.
void insertAt_nonempty_incorrect() {

    // something in here is PRINTING
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);

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
    assert(error_message=="index (42) not in range [0..8]");
}

// makes sure that elementAt() throws an error when run on an
// empty instance.
void elementAt_empty() {
    CharArrayList empty_arr = CharArrayList();
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
    assert(error_message=="index (16) not in range [0..0)");
}

// elementat(7) on an instance of 8 should return the last character
void elementAt_end() {
    CharArrayList one_arr = CharArrayList('g');
    assert(one_arr.elementAt(0)=='g');
} 

// elementat(0) on an instance of 1 should return the one character
void elementAt_one() {
    CharArrayList one_arr = CharArrayList('g');
    assert(one_arr.elementAt(0)=='g');
}

// asking for the element at a negative index should throw an error
void elementAt_negative() {
    CharArrayList empty_arr = CharArrayList();
    bool range_error_thrown = false;
    try{empty_arr.elementAt(-2);}
    catch (const std::range_error &e) {
        range_error_thrown = true;    }
    assert(range_error_thrown);
}

// builds a large array with a loop, which should cause multiple expansions
// and makes sure elementAt still works properly
void elementAt_loopily_built() {
    CharArrayList my_inst;
    for (int i = 0; i < 65; i++) {
        my_inst.insertAt('z', i);
    }
    assert(my_inst.size()==65);
    assert(my_inst.elementAt(34)=='z');
    assert(my_inst.first()=='z');
    assert(my_inst.last()=='z');
}
// asking for the first element of an empty instance should throw an error
void first_zero() {
    CharArrayList my_empt_inst;
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
    assert(error_message=="cannot get first of empty ArrayList");
}

// asking for the first element of an instance of one should return
// the right character
void first_one() {
    CharArrayList my_c_inst = CharArrayList('c');
    assert(my_c_inst.first()=='c');
}

// asking for the first element of an instance of 8 should return
// the right character
void first_many() {
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);
    assert(test_list.first()=='a');
}

// asking for the last element of an empty instance should throw an error
void last_zero() {
    CharArrayList my_empt_inst;
    bool runtime_error_thrown = false;
    std::string error_message = "";
    try {
    my_empt_inst.last();
    }
    catch (const std::runtime_error &e) {
    runtime_error_thrown = true;
    error_message = e.what();
    }
    // out here, we make our assertions
    assert(runtime_error_thrown);
    assert(error_message=="cannot get last of empty ArrayList");
}

// asking for the last element of an instance of one should return
// the right character
void last_one() {
    CharArrayList my_c_inst = CharArrayList('c');
    assert(my_c_inst.last()=='c');
}

// asking for the last element of an instance of 8 should return
// the right character
void last_many() {
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList test_list(test_arr, 8);
    assert(test_list.last()=='h');
}

// pushAtFront on an instance of 0 should return an instance of 1
// with the right character
void pushatfront_zero() {
    CharArrayList my_empt_inst;
    my_empt_inst.pushAtFront('j');
    assert(my_empt_inst.size()==1);
    assert(my_empt_inst.first()=='j');
    assert(my_empt_inst.toString()=="[CharArrayList of size 1 <<j>>]");
}

// pushAtBack on an instance of 0 should return an instance of 1
// with the right character
void pushatback_zero() {
    CharArrayList my_empt_inst;
    my_empt_inst.pushAtBack('k');
    assert(my_empt_inst.size()==1);
    assert(my_empt_inst.last()=='k');
    assert(my_empt_inst.toString()=="[CharArrayList of size 1 <<k>>]");
}

// pushAtFront on an instance of 8 should return an instance of 9
// with the right character
void pushatfront_many() {
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList my_arrlist(test_arr, 8);
    my_arrlist.pushAtFront('z');
    assert(my_arrlist.size()==9);
    assert(my_arrlist.first()=='z');
    std::string out_str = "[CharArrayList of size 9 <<zabcdefgh>>]";
    assert(my_arrlist.toString()==out_str);
}

// pushAtBack on an instance of 8 should return an instance of 9
// with the right character
void pushatback_many() {
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList my_arrlist(test_arr, 8);
    my_arrlist.pushAtBack('y');
    assert(my_arrlist.size()==9);
    assert(my_arrlist.last()=='y');
    assert(my_arrlist.first()=='a');
    std::string out_str = "[CharArrayList of size 9 <<abcdefghy>>]";
    assert(my_arrlist.toString()==out_str);
}

//pushAtFront on an instance of 1 should result in an instance of 2
void pushatfront_one() {
    CharArrayList my_m_inst = CharArrayList('m');
    my_m_inst.pushAtFront('q');
    assert(my_m_inst.size()==2);
    assert(my_m_inst.first()=='q');
    assert(my_m_inst.last()=='m');
    assert(my_m_inst.toString()=="[CharArrayList of size 2 <<qm>>]");
}

//pushAtBack on an instance of 1 should result in an instance of 2
void pushatback_one() {
    CharArrayList my_m_inst = CharArrayList('m');
    my_m_inst.pushAtBack('h');
    assert(my_m_inst.size()==2);
    assert(my_m_inst.first()=='m');
    assert(my_m_inst.last()=='h');
    assert(my_m_inst.toString()=="[CharArrayList of size 2 <<mh>>]");
}

//toString (and toReverseString) on an empty instance
// should return "[CharArrayList of size 0 <<>>]"
void toString_empty() {
    CharArrayList my_empt_inst;
    assert(my_empt_inst.toString()=="[CharArrayList of size 0 <<>>]");
    std::string rev_string = "[CharArrayList of size 0 <<>>]";
    assert(my_empt_inst.toReverseString()==rev_string);
};

//toString (and toReverseString) on an instance of 1 e
// should return "[CharArrayList of size 1 <<....>>]"
void toString_one() {
    CharArrayList my_y_inst = CharArrayList('y');
    assert(my_y_inst.toString()=="[CharArrayList of size 1 <<y>>]");
    assert(my_y_inst.toReverseString()=="[CharArrayList of size 1 <<y>>]");
};

//toString (and toReverseString) on an instance of 8 e
// should return "[CharArrayList of size 8 <<....>>]" with the elements
// forward and backward
void toString_many() {
    char test_arr[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList arrlist(test_arr, 8);
    assert(arrlist.toString()=="[CharArrayList of size 8 <<abcdefgh>>]");
    std::string rev_string = "[CharArrayList of size 8 <<hgfedcba>>]";
    assert(arrlist.toReverseString()==rev_string);
}

// insesrtInOrder on an empty instance results in an instance of 1 with
// the right character
void insertInOrder_zero() {
    CharArrayList my_empt_inst;
    my_empt_inst.insertInOrder('r');
    assert(my_empt_inst.size()==1);
    assert(my_empt_inst.first()=='r');
    assert(my_empt_inst.toString()=="[CharArrayList of size 1 <<r>>]");
}

// insertInOrder on an instance of 1, where paramater character is less
// than existing character, results in an instance with size 2 and 
// characters in the right order
void insertInOrder_one_beginning() {
    CharArrayList my_s_inst = CharArrayList('s');
    my_s_inst.insertInOrder('r');
    assert(my_s_inst.size()==2);
    assert(my_s_inst.first()=='r');
    assert(my_s_inst.last()=='s');
    assert(my_s_inst.toString()=="[CharArrayList of size 2 <<rs>>]");
}

// insertInOrder on an instance of 1, where paramater character is greater
// than existing character, results in an instance with size 2 and 
// characters in the right order
void insertInOrder_one_end() {
    CharArrayList my_s_inst = CharArrayList('s');
    my_s_inst.insertInOrder('t');
    assert(my_s_inst.size()==2);
    assert(my_s_inst.first()=='s');
    assert(my_s_inst.last()=='t');
    assert(my_s_inst.toString()=="[CharArrayList of size 2 <<st>>]");
}

// insertInOrder on an instance of 7, where paramater character is less
// than all characters, results in an instance with size 8 and 
// characters in the right order
void insertInOrder_beginning() {
    char test_arr[7] = { 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    CharArrayList my_arrlist(test_arr, 7);
    my_arrlist.insertInOrder('a');
    assert(my_arrlist.size()==8);
    assert(my_arrlist.first()=='a');
    assert(my_arrlist.elementAt(1)=='b');
    assert(my_arrlist.elementAt(2)=='c');
    assert(my_arrlist.toString()=="[CharArrayList of size 8 <<abcdefgh>>]");
}

// insertInOrder on an instance of 7, where paramater character is in the
// middle of all the characters, results in an instance with size 8 and 
// characters in the right order
void insertInOrder_middle() {
    char test_arr[7] = { 'a', 'b', 'c', 'd', 'f', 'g', 'h' };
    CharArrayList my_arrlist(test_arr, 7);
    my_arrlist.insertInOrder('e');

    assert(my_arrlist.size()==8);
    assert(my_arrlist.first()=='a');
    assert(my_arrlist.elementAt(4)=='e');
    assert(my_arrlist.toString()=="[CharArrayList of size 8 <<abcdefgh>>]");
}

// insertInOrder on an instance of 7, where paramater character is after
// all characters, results in an instance with size 8 and 
// characters in the right order
void insertInOrder_end() {
    char test_arr[7] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    CharArrayList my_arrlist(test_arr, 7);
    my_arrlist.insertInOrder('h');
    assert(my_arrlist.size()==8);
    assert(my_arrlist.last()=='h');
    assert(my_arrlist.elementAt(4)=='e');
    std::string out_str = "[CharArrayList of size 8 <<abcdefgh>>]";
    assert(my_arrlist.toString()==out_str);
}

// calling removeAt on an empty instance throws an error
void removeAt_zero(){
    CharArrayList my_empt_inst;
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
    assert(error_message=="index (0) not in range [0..0)");
}

// calling removeAt on an empty instance with a higher
// index also throws an error
void removeAt_zero_nonzero(){
    CharArrayList my_empt_inst;
    bool range_error_thrown = false;
    std::string error_message = "";
    try {
        my_empt_inst.removeAt(3);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    // out here, we make our assertions
    assert(range_error_thrown);
    assert(error_message=="index (3) not in range [0..0)");
}

// calling removeAt on an instance of 1 at index 2
// index also throws an error
void removeAt_many_outofrange(){
    CharArrayList my_c_inst('c');
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
    assert(error_message=="index (2) not in range [0..1)");
}

// calling removeAt correctly on an instance of 1 
// results in an empty instance
void removeAt_one(){
    CharArrayList my_c_inst('c');
    my_c_inst.removeAt(0);
    assert(my_c_inst.isEmpty());
}

// calling removeAt on an instance of 1 
// with an out of range index throws an error
void removeAt_one_error(){
    CharArrayList my_c_inst('c');
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
    assert(error_message=="index (3) not in range [0..1)");
}

// calling removeAt on an instance of 7
// with an index of 0 removes the first element
// and results in a size of 6 
void removeAt_beginning(){
    char test_arr[7] = { 'a', 'b', 'c', 'd', 'f', 'g', 'h' };
    CharArrayList my_arrlist(test_arr, 7);  
    my_arrlist.removeAt(0);
    assert(my_arrlist.size()==6);
    assert(my_arrlist.first()=='b');
    assert(my_arrlist.toString()=="[CharArrayList of size 6 <<bcdfgh>>]");
}

// calling removeAt on an instance of 7
// with an index of 2 removes the third element
// and results in a size of 6 
void removeAt_mid(){
    char test_arr[7] = { 'a', 'b', 'c', 'd', 'f', 'g', 'h' };
    CharArrayList my_arrlist(test_arr, 7);  
    my_arrlist.removeAt(2);
    assert(my_arrlist.size()==6);
    assert(my_arrlist.elementAt(2)=='d');
    assert(my_arrlist.toString()=="[CharArrayList of size 6 <<abdfgh>>]");

}

// calling removeAt on an instance of 7
// with an index of 6 removes the last element
// and results in a size of 6 
void removeAt_end(){
    char test_arr[7] = { 'a', 'b', 'c', 'd', 'f', 'g', 'h' };
    CharArrayList my_arrlist(test_arr, 7);  
    my_arrlist.removeAt(6);
    assert(my_arrlist.size()==6);
    assert(my_arrlist.last()=='g');
    assert(my_arrlist.toString()=="[CharArrayList of size 6 <<abcdfg>>]");
}

// calling popfromfront on an empty instance calls an error
void popfromfront_zero() {
    CharArrayList my_empt_inst;
    bool runtime_error_thrown = false;
    std::string error_message = "";
    try {
        my_empt_inst.popFromFront();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    // out here, we make our assertions
    assert(runtime_error_thrown);
    assert(error_message=="cannot pop from empty ArrayList");
};

// calling popfromfront on an instance of one makes an empty instance
void popfromfront_one(){
    CharArrayList my_c_inst('c');
    my_c_inst.popFromFront();
    assert(my_c_inst.isEmpty());
};

// calling popfromfront on an instance of 7 makes an instance of 6
// and removes the first character
void popfromfront_many(){
    char test_arr[7] = { 'a', 'b', 'c', 'd', 'f', 'g', 'h' };
    CharArrayList my_arrlist(test_arr, 7);  
    my_arrlist.popFromFront();
    assert(my_arrlist.size()==6);
    assert(my_arrlist.first()=='b');
    assert(my_arrlist.toString()=="[CharArrayList of size 6 <<bcdfgh>>]");
};

// calling popfromback on an empty instance calls an error
void popfromback_zero() {
    CharArrayList my_empt_inst;
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
    assert(error_message=="cannot pop from empty ArrayList");
};

// calling popfromback on an instance of one makes an empty instance
void popfromback_one(){
    CharArrayList my_c_inst('c');
    my_c_inst.popFromBack();
    assert(my_c_inst.isEmpty());
};

// calling popfromback on an instance of 7 makes an instance of 6
// and removes the last character
void popfromback_many(){
    char test_arr[7] = { 'a', 'b', 'c', 'd', 'f', 'g', 'h' };
    CharArrayList my_arrlist(test_arr, 7); 
    my_arrlist.popFromBack();
    assert(my_arrlist.size()==6);
    assert(my_arrlist.last()=='g'); 
    assert(my_arrlist.toString()=="[CharArrayList of size 6 <<abcdfg>>]");
};

// calling replace on an empty instance throws an error
void replace_empty(){
    CharArrayList my_empt_inst;
    bool range_error_thrown = false;
    std::string error_message = "";
    try {
        my_empt_inst.replaceAt('b',4);
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    assert(range_error_thrown);
    assert(error_message=="index (4) not in range [0..0)");
}

// calling replace on an instance of 1 replaces the character
void replace_one(){
    CharArrayList my_j_inst('j');
    my_j_inst.replaceAt('k',0);
    assert(my_j_inst.size()==1);
    assert(my_j_inst.first()=='k');
}

// calling replace at the beginning of a 7 character array 
// replaces the character
void replace_beginning(){
    char test_arr[7] = { 'a', 'b', 'c', 'd', 'f', 'g', 'h' };
    CharArrayList my_arrlist(test_arr, 7); 
    my_arrlist.replaceAt('k',0);
    assert(my_arrlist.first()=='k');
    assert(my_arrlist.toString()=="[CharArrayList of size 7 <<kbcdfgh>>]");
}


// calling replace in the middle of a 7 character array 
// replaces the character
void replace_mid(){
    char test_arr[7] = { 'a', 'b', 'c', 'd', 'f', 'g', 'h' };
    CharArrayList my_arrlist(test_arr, 7); 
    my_arrlist.replaceAt('k',5);
    assert(my_arrlist.elementAt(5)=='k');
    assert(my_arrlist.toString()=="[CharArrayList of size 7 <<abcdfkh>>]");
}

// calling replace at the end of a 7 character array 
// replaces the character
void replace_end(){
    char test_arr[7] = { 'a', 'b', 'c', 'd', 'f', 'g', 'h' };
    CharArrayList my_arrlist(test_arr, 7); 
    my_arrlist.replaceAt('k',6);
    assert(my_arrlist.last()=='k');
    assert(my_arrlist.toString()=="[CharArrayList of size 7 <<abcdfgk>>]");
}

// calling replace on an index greater than the array size
// throws an error
void replace_outofrange(){
    char test_arr[7] = { 'a', 'b', 'c', 'd', 'f', 'g', 'h' };
    CharArrayList my_arrlist(test_arr, 7); 
    std::string error_message = "";
    bool error_thrown = false;
    try {
        my_arrlist.replaceAt('b',20);
    }
    catch (const std::range_error &e) {
    error_thrown = true;
    error_message = e.what();
    }
    // out here, we make our assertions
    assert(error_thrown);
    assert(error_message=="index (20) not in range [0..7)");
}

// concatenating two empty lists results in an empty list
void concat_empty_to_empty() {
    CharArrayList empt_a;
    CharArrayList empt_b;
    empt_a.concatenate(&empt_b);
    assert(empt_a.isEmpty());
}

// concatenating an empty array onto an array of 1 results in an array of 1
void concat_empty_to_one() {
    CharArrayList empt_a;
    CharArrayList one_b('k');
    one_b.concatenate(&empt_a);
    assert(one_b.size()==1);
}

// concatenating an array of 1 onto an empty array results in an array of 1
void concat_one_to_empty(){
    CharArrayList one_a('k');
    CharArrayList empt_b;
    empt_b.concatenate(&one_a);
    assert(empt_b.size()==1);
    assert(empt_b.first()=='k');
}

// concatenating an instance of 3 to an instance of 4 results in an instance
// of 7 with the right characters
void concat_many_to_many() {
    char list_a[4] = {'a','b','c','d'};
    char list_b[3] = {'k','l','m'};
    CharArrayList arr_a = CharArrayList(list_a,4);
    CharArrayList arr_b = CharArrayList(list_b,3);
    arr_a.concatenate(&arr_b);
    assert(arr_a.size()==7);
    assert(arr_a.toString()=="[CharArrayList of size 7 <<abcdklm>>]");
}

int main() {
    dummytest();

    null_constructor_one();
    char_constructor_one();
    many_constructor_many();
    many_constructor_one();
    copy_constructor_one();
    copy_constructor_many();
    copy_constructor_zero();

    isEmpty_empty();
    isEmpty_notempty();
    isClear_empty();
    isClear_nonempty();
    size_empty();
    size_one();
    size_many();

    insertAt_empty_correct();
    insertAt_empty_incorrect();
    insertAt_front_singleton_list();
    insertAt_back_singleton_list();
    insertAt_many_elements();
    insertAt_front_large_list();
    insertAt_middle_large_list();
    insertAt_back_large_list();
    insertAt_nonempty_incorrect();

    insertInOrder_beginning();
    insertInOrder_end();
    insertInOrder_middle();
    insertInOrder_one_beginning();
    insertInOrder_one_end();
    insertInOrder_zero();

    elementAt_empty();
    elementAt_end();
    elementAt_loopily_built();
    elementAt_negative();
    elementAt_one();

    toString_empty();
    toString_one();
    toString_many();

    first_zero();
    first_one();
    first_many();
    last_zero();
    last_one();
    last_many();

    removeAt_zero();
    removeAt_one();
    removeAt_beginning();
    removeAt_mid();
    removeAt_end();
    removeAt_many_outofrange();
    removeAt_one_error();
    removeAt_zero_nonzero();

    pushatfront_zero();
    pushatback_zero();
    pushatfront_many();
    pushatback_many();
    pushatfront_one();
    pushatback_one();

    popfromback_many();
    popfromback_one();
    popfromback_zero();
    popfromfront_many();
    popfromfront_one();
    popfromfront_zero();

    replace_beginning();
    replace_empty();
    replace_end();
    replace_mid();
    replace_one();
    replace_outofrange();

    concat_empty_to_empty();
    concat_empty_to_one();
    concat_one_to_empty();
    concat_many_to_many();

    return 0;
}