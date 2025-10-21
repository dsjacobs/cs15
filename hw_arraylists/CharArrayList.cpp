/*
 *  CharArrayList.cpp
 *  Danielle Jacobs
 *  September 12, 2025
 *
 *  COMP 15 HW 1 Cheshire ConCATenation
 *
 *  The functions outlined in this file allow clients to create, add to, 
 *  and removed from a Character Array List. A Character Array List can
 *  be created with 0, 1, or an array of characters. It can also be
 *  copied from an existing array. Characters can be added at the beginning,
 *  end, or based on index or alphabetic order. Characters can be removed
 *  from the beginning, end, and index as well. Characters can be replaced.
 *  The array can be returned as a string, or backwards as a reverse string.
 *  The elements at any index can be returned, and the number of elements
 *  in the array can be checked as well.
 *
 */

#include "CharArrayList.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <iso646.h>
using namespace std;

// Constructor that creates an empty array list with 
// size and capacity of 0.
CharArrayList::CharArrayList() {
        currSize = 0;
        capacity = 0;
        arr_ptr = new char[0];
}

// Constructor that creates an array list of a given
// character and a size and capacity of 1.
CharArrayList::CharArrayList(char c) {
        currSize = 1;
        capacity = 1;
        arr_ptr = new char[capacity];
        *arr_ptr = c;
    }

// Constructor that creates an array list from a given
// array. The size and capacity are both set to the given 
// size. Make sure that the size given is less than or equal
// to the length of the array.
CharArrayList::CharArrayList(char arr[], int size) {
    currSize = size;
    capacity = size;
    arr_ptr = new char[capacity];

    if (size < 0) {
        throw std::range_error("size must be a positive integer");
    }
    else {
            for (int i=0; i < size; ++i) {
            arr_ptr[i] = arr[i];
        }
    }
}

// Copy constructor creates a deep copy (copying over each
// element) of another existing Character Array List, with
// the same size and capacity.
CharArrayList::CharArrayList(const CharArrayList &other) {
    currSize = other.currSize;
    capacity = other.capacity;
    arr_ptr = new char[capacity];
    if (currSize > 0) {
        for (int i=0; i < currSize; ++i) {
            arr_ptr[i] = other.arr_ptr[i];
        }
    }
}

// Destructor frees the space allacotaed for the whole array,
// and sets  size and capacity to 0.
CharArrayList::~CharArrayList() {
    delete[] arr_ptr;
    currSize = 0;
    capacity = 0;

}

// Returns whether or not the size of the array is 0.
bool CharArrayList::isEmpty() const {
    return currSize==0;
}

// Frees allocated space, sets size and capacity to 0, and
// points to a new location with an empty array list.
void CharArrayList::clear() {
    currSize = 0;
    capacity = 0;
    delete[] arr_ptr;
    arr_ptr = new char[capacity];
}

// Returns the current length of the character array list.
int CharArrayList::size() const{
    return currSize;
}

// Takes an index location as a parameter and returns the character
// at that index. If the index is negative or not in range 
// of the current size, it throws a standard range error.
char CharArrayList::elementAt(int index) const{
    // ensures index is positive and less than current size
    if (index <= currSize and index >= 0) {return arr_ptr[index];}
    // if the index is negative or greater than the current size,
    // throws error
    else {
        std::ostringstream errorstream;
        errorstream << "index (" << std::to_string(index);
        errorstream << ") not in range [0..";
        errorstream << std::to_string(currSize) << ")";
        throw std::range_error(errorstream.str());
    }
}

// Returns the first element of the array, unless the array is empty
// in which case it throws a standard runtime error.
char CharArrayList::first() const {
    if (currSize > 0) {
        return elementAt(0);
    }
    // if array list is throw error
    else {
        throw std::runtime_error("cannot get first of empty ArrayList");
    }
}

// Returns the last element of the array, unless the array is empty
// in which case it throws a standard runtime error.
char CharArrayList::last() const {
    if (currSize > 0) {
        return elementAt(currSize -1 );
    }
    // if array is empty throw error
    else {throw std::runtime_error("cannot get last of empty ArrayList");}
}

// Returns a string represntation of the current array list. An empty
// array list will return '[CharArrayList of size 0 <<>>]'
std::string CharArrayList::toString() const {
    std::string ret_string = "[CharArrayList of size ";
    // if array is empty return size 0 <<>>
    if (isEmpty()) {
        ret_string += "0 <<>>]";
    }
    // otherwise return the length and contents of the array
    else {
        ret_string += std::to_string(size());
        ret_string += " <<";
        for (int i=0; i < currSize; i++){
            ret_string += arr_ptr[i];
        }
        ret_string += ">>]";
    }
    return ret_string;
}

// Returns a string represntation of the current array list in backwards
// order. An empty array list will return '[CharArrayList of size 0 <<>>]'
std::string CharArrayList::toReverseString() const {
    std::string ret_string = "[CharArrayList of size ";
    // if array is empty return size 0 <<>>
    if (isEmpty()) {
        ret_string += "0 <<>>]";
    }
    // otherwise return the length and contents of the array backwards
    else {
        ret_string += std::to_string(size());
        ret_string += " <<";
        for (int i=currSize - 1; i>=0; i--){
            ret_string += arr_ptr[i];
        }
        ret_string += ">>]";
    }
    return ret_string;
}

// Inserts a given character at a given index. Increases size
// by 1. If the index is negative or out of range of the size 
// of the array, throws a standard range error. If adding one 
// element would increase the size above capacity, expands the array.
void CharArrayList::insertAt(char c, int index) {
    // makes sure that index is nonnegative and less than current size
    if (index <= currSize and index >= 0) {
        if (overCapacity()) {expand();}
        for (int i = currSize - 1; i >= index; i--) {
            arr_ptr[i+1] = arr_ptr[i];
        }
        arr_ptr[index] = c;
        currSize++; 
    } 
    // throws an error if index is negative or greater than current size
    else {
        std::ostringstream errorstream;
        errorstream << "index ("<< std::to_string(index);
        errorstream << ") not in range [0..";
        errorstream << std::to_string(currSize) << "]";
        throw std::range_error(errorstream.str()); 
    }
}

// Inserts a given character into the array in alphabetic order,
// assuming the array is already in alphabetic order. Increases 
// size by 1. If adding one element would increase
// the size above capacity, expands the array.
void CharArrayList::insertInOrder(char c) {
    if (overCapacity()) {expand();}
    // if list is empty dont worry about order, just put in front
    if (isEmpty()) {pushAtFront(c);}
    // otherwise loop and stop either when the next letter is greater
    // than the input, or when we get to the end of the list,
    // whichever is first.
    else {
        int i = 0;
        while (i < currSize and arr_ptr[i] <= c)
            {i++;}
        insertAt(c,i);
    } 
}

// Takes an index and checks if that is in range of the size of the 
// array. If negative or out of range, throws an error. Otherwise, removes
// the character at that index and reduces size by 1.
void CharArrayList::removeAt(int index) {
    std::ostringstream errorstream;
    errorstream << "index ("<< std::to_string(index);
    errorstream << ") not in range [0..";
    errorstream << std::to_string(currSize) << ")";  
    // if array is empty, the index is greater than the current size,
    // or the index is negative  
    if (isEmpty() or index >= currSize or index < 0) {
        throw std::range_error(errorstream.str());
    }
    else {
        for (int i = index; i < currSize - 1; i++) {
            arr_ptr[i] = arr_ptr[i+1];
        }
        currSize--;

    }
}

// Takes no parameters and removes the first element from a nonempty
// array. If empty, throws a runtime error. If successful,
// decreases size by one.
void CharArrayList::popFromFront() {
    // if array is empty throw error
    if (isEmpty()) {
        throw std::runtime_error("cannot pop from empty ArrayList");
    }
    else {removeAt(0);
    }
}

// Takes no parameters and removes the last element from a nonempty array.
// If empty, throws a runtime error. If successful, decreases size by one.
void CharArrayList::popFromBack() {
    // if array is empty throw error
    if (isEmpty()) {
        throw std::runtime_error("cannot pop from empty ArrayList");
    }
    else {removeAt(currSize - 1);}
}

// Takes a given character and adds it to the front of the array. Increases
// size by one. If adding one element would increase
// the size above capacity, expands the array.
void CharArrayList::pushAtFront(char c) {
    if (overCapacity()) {expand();}
    for (int i = currSize; i >= 0; i--) {
        arr_ptr[i+1] = arr_ptr[i];
    }
    arr_ptr[0] = c;
    currSize++;
}

// Takes a given character and adds it to the back of the array. Increases
// size by one. If adding one element would increase
// the size above capacity, expands the array.
void CharArrayList::pushAtBack(char c) {
    if (overCapacity()) {expand();}
    arr_ptr[currSize] = c;
    currSize++;
}

// Takes in a character and index location and replaces the existing
// character in that location with the input. If the index is out of
// range or negative, throws an error.
void CharArrayList::replaceAt(char c, int index) {
    std::ostringstream errorstream;
        errorstream << "index (" << std::to_string(index);
        errorstream << ") not in range [0..";
        errorstream << std::to_string(currSize) << ")";
    // makes sure array is not empty and index is between zero
    // and current size
    if (isEmpty() or index >= currSize or index < 0)
        {
            throw std::range_error(errorstream.str());
        }
    else {
        removeAt(index);
        insertAt(c,index);
    }
}

// Takes another character array list as input and appends it to the
// end of the current array list. Expands until capacity is enough 
// for the combined length. Adds the size of the two arrays together
// for the new size.
void CharArrayList::concatenate(CharArrayList *other) {
    if ((currSize + other->currSize) > capacity) {expand();}
    for (int i = 0; i < other->currSize; i++) {
        arr_ptr[currSize + i] = other->arr_ptr[i];
    }
    currSize = currSize + other->currSize;
}

/// private functions

// Returns whether or not adding one element would exceed capacity.
bool CharArrayList::overCapacity() {
    return  currSize + 1 > capacity;
}

// Expands the array by doubling capacity and adding 2, creating a new array
// with that new capacity, copying over all elements, freeing the memory
// associated with the old array and pointing to the new one.

void CharArrayList::expand() {
    /* Update capacity and allocate larger array */
    capacity      = (capacity * 2) + 2;
    char* new_inst = new char[capacity];

    /* Copy each element of old array  */
    for (int i = 0; i < currSize; i++) {
        new_inst[i] = arr_ptr[i];
    }

    /* Deallocate memory associated with old array and reassign pointer
    to expanded array */
    delete [] arr_ptr;
    arr_ptr = new_inst;
}