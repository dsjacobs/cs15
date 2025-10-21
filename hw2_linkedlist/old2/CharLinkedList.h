/*
 *  CharLinkedList.h
 *  Danielle Jacobs
 *  9/22/2025
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  This file is to outline a character linked list. A character linked list
 *  represents an ordered list of characters, each in their own node structure.
 *  Each node has a value and pointers to the nodes on either side of it. The 
 *  list itself has a front and back pointer as well. 
 *  Characters can be added or removed from the beginning, middle or end
 *  of the list. Two character linked lists can be concatenated. The size
 *  can be checked, as well as whether or not the linked list is empty.
 *  A linked list can start with any number of elements, including none.
 *  A character linked list can also be returned as a string or
 *  backwards as a reverse string. *
 */

#ifndef CHAR_LINKED_LIST_H
#define CHAR_LINKED_LIST_H

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;

class CharLinkedList {

  public:
    CharLinkedList();
    CharLinkedList(char c);
    CharLinkedList(char arr[], int size);
    CharLinkedList(const CharLinkedList &other);
    ~CharLinkedList();

    CharLinkedList &operator=(const CharLinkedList &other)
    {
        if (this == &other) {
            return *this;
        }
        currSize = other.currSize;
        clear();
        deep_copy(other);
        return *this;
    }

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
    void concatenate(CharLinkedList *other);

  private:
    struct Node {
        char val;
        Node *next;
        Node *prev;
        Node();
        Node(char c); 
    };

    int currSize;
    Node *front;
    Node *back;

    Node *nodeAt(int index) const;
    Node *new_node(char c);
    Node *new_empty_node();

    Node *add_recur_helper(char arr[], int size, int start) const;
    Node *nodeAt_recur_helper(Node *curNode, int start, int index) const;
    void clear_recur_helper(Node *curNode) const;

    void deep_copy(const CharLinkedList &other);

    std::string errorBuilder(int index, int size, char lastChar) const;
    std::string stringBuilder(int size, std::string rawS) const;
};

#endif
