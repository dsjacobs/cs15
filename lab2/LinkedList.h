/*
 * Dani Jacobs
 * LinkedList.h
 *
 * COMP 15 lab 2
 * by Tyler Calabrese, January 2020
 * edited by Matt R., Juliana Vegas, and Alexis Blair, 1/20/2021
 *
 * Interface for LinkedList lab.
 *
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Planet.h"

class LinkedList {
public:
    LinkedList();

    // TODO:  implement the destructor
    ~LinkedList();

    // TODO: implement these two functions
    void pushAtFront(Planet p);
    void pushAtBack(Planet p);

    // TODO (bonus JFFE): implement this fn
    void reverse();

    std::string toString() const;

private:
    struct Node {
        Planet      info;
        Node       *next;
        std::string toString() { return info.toString(); 
        Node();
};
    };

    Node *front;
    int   size;
};

#endif
