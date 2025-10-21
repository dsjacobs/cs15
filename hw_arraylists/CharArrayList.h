/*
 *  CharArrayList.h
 *  Danielle Jacobs
 *  September 12, 2025
 *
 *  COMP 15 HW 1 Cheshire ConCATenation
 *
 *  This file is to outlines a character array list. A character array list
 *  represents an ordered list of characters with a size and capacity. 
 *  Characters can be added or removed from the beginning, middle or end
 *  of the list. Two character array lists can be concatenated. The size
 *  can be checked, as well as whether or not the array list is empty.
 *  An array list can start with any number of elements, including none.
 *  A character array list can also be returned as a string or
 *  backwards as a reverse string.
 *
 */
#define CHAR_ARRAY_LIST_H
#define CHAR_ARRAY_LIST_H
#include <iostream>

class CharArrayList {
public:

    CharArrayList();
    CharArrayList(char c);
    CharArrayList(char arr[], int size);
    CharArrayList(const CharArrayList &other);
    ~CharArrayList(); 
    // Assignment operator frees current array and copies content from
    // the other character array list given as a parameter. 
    CharArrayList &operator=(const CharArrayList &other) {
            // if current instance and parameter instance are the same, don't do
            // anything, just return this instance
            if(this == &other) {return *this;}
            // clear memory, change size and capacity to other
            clear();
            currSize = other.currSize;
            capacity = other.capacity;
            arr_ptr = new char[capacity];
            // copy any elemenets over
            if (currSize > 0) {
                for (int i=0; i < currSize; ++i) {
                arr_ptr[i] = other.arr_ptr[i];
                }
            }
            return *this;
    };

    bool isEmpty() const;
    void clear();
    int size() const;
    char first() const;
    char last() const;

    char elementAt(int index) const;
    std::string toString() const;
    std::string toReverseString() const;

    void pushAtBack(char c);
    void pushAtFront(char c);
    void insertAt(char c, int index);
    void insertInOrder(char c);
    void popFromFront();
    void popFromBack();
    void removeAt(int index);
    void replaceAt(char c, int index);
    void concatenate(CharArrayList *other);

private:
    int currSize;
    int capacity;
    char* arr_ptr;
    std::string buildErrorMessage(int index, char lastchar);
    bool overCapacity();
    void expand();
    CharArrayList(int size);
};

