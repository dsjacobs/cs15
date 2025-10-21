/*
 * ArrayList.h
 * Danielle Jacobs
 * COMP15 lab 1
 * 9/9/2025
 *
 * This is a class declaration for an ArrayList for lab0.
 *
 * TODO: complete the file!
 */
#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <string>

class ArrayList {
public:
    // TODO: Implement the constructor, destructor, pushAtBack, isEmpty,
    //       size, toString, and expand functions.

    ArrayList();
    ~ArrayList();

    void pushAtBack(int elem);

    bool        isEmpty() const;
    int         size() const;
    std::string toString() const;

    // JFFE! Write a find function that returns true if a given integer is
    // in the ArrayList, and false if not.
    bool find(int to_find) const;

    // JFFE! Write a popFromBack function that removes the last element of
    // the ArrayList.
    void popFromBack();

private:
    int numItems;
    int capacity;
    int* arrlist;

    // helper function for changing the capacity of the ArrayList
    void expand();
};

#endif
