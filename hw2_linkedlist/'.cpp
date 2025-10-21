/*
 *  CharLinkedList.cpp
 *  Danielle Jacobs
 *  September 22, 2025
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  The functions outlined in this file allow clients to create, add to,
 *  and removed from a Character Linked List. A Character Linked List can
 *  be created with 0, 1, or an array of characters. It can also be
 *  copied from an existing array. Characters can be added at the beginning,
 *  end, or based on index or alphabetic order. Characters can be removed
 *  from the beginning, end, and index as well. Characters can be replaced.
 *  The array can be returned as a string, or backwards as a reverse string.
 *  The elements at any index can be returned, and the number of elements
 *  in the array can be checked as well.
 *
 */

#include "CharLinkedList.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;

// Constructor that creates an empty linked list with
// size of 0.
CharLinkedList::CharLinkedList()
{
    front = nullptr;
    back = nullptr;
    currSize = 0;
};

// Constructor that creates an linked list of a given
// character and a size of 1.
CharLinkedList::CharLinkedList(char c)
{
    // node has value and null next/prev pointers
    Node *c_node = new_node(c);

    // list has front and back pointers to the one node
    front = c_node;
    back = c_node;

    currSize = 1;
};

// Constructor that creates an linked list from a given
// linked list. The size is set to the given
// size. Make sure that the size given is less than or equal
// to the length of the linked list.
CharLinkedList::CharLinkedList(char arr[], int size)
{
    // make sure size is not negative
    if (size < 0) {
        throw std::runtime_error("cannot add negative size");
    }

    // if we have at least character
    else if (size > 0) {

        // instantiate a null pointer outside of the loop
        Node* prev_node = nullptr;

        for (int i = 0; i < size; i++) {
            Node* my_node = new_node(arr[i]);

            // if its the first or last in the list, set it to the front
            if (i == 0) {
                front = my_node;
            }
            // if there was a previous element, set the pointers both ways
            else {
                my_node->prev = prev_node;
                prev_node->next = my_node;
            }
            // if its the last one, set the back pointer to it
            if (i == size - 1) {
                back = my_node;
            }
            // if its not the last one, save the previous as the current
            // for the next round of the loop.
            else {prev_node = my_node;}
        }

    }

    currSize = size;
};

// Copy constructor creates a deep copy (copying over each
// element) of another existing Character Linked List, with
// the same size and capacity.
CharLinkedList::CharLinkedList(const CharLinkedList& other)
{
    currSize = other.currSize;
    
    Node* prev_node = nullptr;
    for (int i = 0; i < currSize; i++) {
        Node* curNode = new_node(other.elementAt(i));

        // if its the first or last in the list, set the pointers accordingly
        if (i == 0) {
            front = curNode;
        }
        else {
            curNode->prev = prev_node;
            prev_node->next = curNode;
        }
        if (i == currSize - 1) {
            back = curNode;
            curNode-> next = nullptr;
        }
    
        // remember this node for the next run of the loop
        prev_node = curNode;
    }
}

// before deleting list, calls clear to remove all nodes, set front and back
// pointers to null, and set size to 0.
CharLinkedList::~CharLinkedList() {
    clear(); 
}

// Returns whether or not the size of the linked is 0.
bool CharLinkedList::isEmpty() const { 
    return currSize == 0; 
}

// removes all nodes, sets front and back pointers to null, and sets size to 0.
void CharLinkedList::clear()
{
    // if its empty, we don't need to do anything.
    if (not isEmpty()) {

        // start at the front, save whats next, delete current, and run on next
        // until we reach the end.
        Node *curNode = front;
        while (curNode != nullptr) {
            Node *next = curNode->next;
            delete curNode;
            curNode = next;
        }
    }
    front = nullptr;
    back = nullptr;
    currSize = 0;
}

// returns the current length of the character array list.
int CharLinkedList::size() const { return currSize; }

// returns the first character in the list.
char CharLinkedList::first() const
{
    // makes sure list is not empty
    if (isEmpty()) {
        throw std::runtime_error("cannot get first of empty LinkedList");
    }

    // returns the value at the location of the front pointer
    Node* first_node = front;
    return first_node->val;
};

// returns the last character in the list.
char CharLinkedList::last() const
{
    // makes sure list is not empty
    if (isEmpty()) {
        throw std::runtime_error("cannot get last of empty LinkedList");
    }

    // returns the value at the location of the back pointer
    Node* last_node = back;
    return last_node->val;
};

// Takes an index location as a parameter and returns the character
// at that index. If the index is negative or not in range
// of the current size, it throws a standard range error.
char CharLinkedList::elementAt(int index) const
{
    Node* cur_node = nodeAt(index);
    return cur_node->val;
};

// Returns a string represntation of the current linked list. An empty
// linked list will return '[CharLinkedList of size 0 <<>>]'
std::string CharLinkedList::toString() const
{
    std::string rawS = "";
    Node* cur = front;

    // if its empty, theres no need to add anything.
    if (not isEmpty()) {
        int ctr = 0;
        // loop and add the value to the raw string.
        while (ctr < currSize) {
            rawS += cur->val;
            cur = cur->next;
            ctr++;
        }
    }
    
    //inserts raw string and size into a helper function 
    //with the standard part ([CharArrayList of size .. <<..>>])'
    return stringBuilder(currSize, rawS);
}

// Returns a string represntation of the current linked list in backwards order.
// An empty linked list will return '[CharArrayList of size 0 <<>>]'
std::string CharLinkedList::toReverseString() const
{
    std::string rawS = "";
    Node* cur = back;

    // if its empty, theres no need to add anything to the standard string.
    if (not isEmpty()) {
        int ctr = currSize - 1;

        // loop and add the value to the raw string.
        while (ctr >= 0) {
            rawS += cur->val;
            cur = cur->prev;
            ctr--;
        }
    }

    //inserts raw string and size into a helper function 
    //with the standard part ([CharArrayList of size .. <<..>>])'
    return stringBuilder(currSize, rawS);
}

// Takes a given character and adds it to the front of the linked list.
// Increases size by one.
void CharLinkedList::pushAtFront(char c)
{
    Node* curfront = front;
    Node* node_to_add = new_node(c);

    // adding to an empty list
    if (back == nullptr and front == nullptr) {
        back = node_to_add;
        front = node_to_add;
    }
    // adding to all other lists by changing front pointer
    else {
        front = node_to_add;
        front->next = curfront;
    }
    currSize++;
}

// Takes a given character and adds it to the back of the linked list. Increases
// size by one.
void CharLinkedList::pushAtBack(char c)
{
    Node* node_to_add = new_node(c);
    Node* curback = back;

    // adding to an empty list
    if (back == nullptr and front == nullptr) {
        back = node_to_add;
        front = node_to_add;
    }

    // adding to all other lists by changing back pointer
    else {
        back = node_to_add;
        back->prev = curback;
        curback->next = node_to_add;
    }
    currSize++;
}

// Inserts a given character at a given index. Increases size
// by 1. If the index is negative or out of range, throws a standard range
// error.
void CharLinkedList::insertAt(char c, int index)
{
    std::string error_msg = errorBuilder(index, currSize, ']');
    // out of range error
    if ((index < 0) or (index > currSize)) {
        throw std::range_error(error_msg);
    }
    // first index, add at beginning
    else if (index == 0) {
        pushAtFront(c);
    }
    // last index, add at end
    else if (index == currSize) {
        pushAtBack(c);
    }
    // remaining will be between two nodes
    else {
        Node* cur = nodeAt(index);
        Node* curAtPrev = nodeAt(index - 1);
        Node* node_to_add = new_node(c);

        // exchange pointers at back
        node_to_add->next = cur;
        cur->prev = node_to_add;

        // exchange pointers at front
        curAtPrev->next = node_to_add;
        node_to_add->prev = curAtPrev;

        // increment size
        currSize++;
    }
}

// Inserts a given character into the linked list in alphabetic order,
// assuming the list is already in alphabetic order. Increases
// size by 1.
void CharLinkedList::insertInOrder(char c)
{
    // if empty no need to loop
    if (isEmpty()) {
        pushAtFront(c);
    }
    // otherwise loop and stop either when the next letter is greater
    // than the input, or when we get to the end of the list,
    // whichever is first.
    else {
        int i = 0;
        while (i < currSize and elementAt(i) <= c) {
            i++;
        }
        insertAt(c, i);
    }
}

// Takes no parameters and removes the last element from a nonempty list.
// If empty, throws a runtime error. If successful, decreases size by one.
void CharLinkedList::popFromBack()
{
    // cant remove from empty list
    if (isEmpty()) {
        throw std::runtime_error("cannot pop from empty LinkedList");
    }
    // if size is just 1 change list pointers, not individual node pointers
    if (currSize == 1) {
        front = nullptr;
        back = nullptr;
    }
    // repoint the backpointer of the list to the previous element
    else {
       back = back->prev;
       back->next = nullptr;
    }

    currSize--;
}

// Takes no parameters and removes the first element from a nonempty list.
// If empty, throws a runtime error. If successful, decreases size by one.
void CharLinkedList::popFromFront()
{
    // cant remove from empty list
    if (isEmpty()) {
        throw std::runtime_error("cannot pop from empty LinkedList");
    }
    // if size is just 1 change list pointers, not individual node pointers
    if (currSize == 1) {
        front = nullptr;
        back = nullptr;
    }
    // repoint the front pointer of the list to the next element
    else {
        front = front->next;
        front->prev = nullptr;
    }
    currSize--;
}

// Takes an index and checks if that is in range of the size of the
// linked list. If negative or out of range, throws an error. Otherwise, removes
// the character at that index and reduces size by 1.
void CharLinkedList::removeAt(int index)
{
    // cant be out of range
    if (isEmpty() or index >= currSize or index < 0) {
        std::string error = errorBuilder(index, currSize, ')');
        throw(std::range_error(error));
    }

    // find whats there
    Node* cur = nodeAt(index);

    // from one element to empty
    if (currSize == 1) {
        front = nullptr;
        back = nullptr;
    }
    else {
        // if it was the last element
        if (index == currSize - 1) {
            back = cur->prev;
            back->next = nullptr;

        }
        // if it was the first element
        else if (index == 0) {
            front = cur->next;
            front->prev = nullptr;
        }
        // if it was between elements
        else {
            Node* prev = cur->prev;
            Node* next = cur->next;
            next->prev = prev;
            prev->next = next;
        }
    }
    // no matter where it was, delete it
    delete cur;
    currSize--;
}

// Takes in a character and index location and replaces the existing
// character in that location with the input. If the index is out of
// range or negative, throws an error.
void CharLinkedList::replaceAt(char c, int index) { nodeAt(index)->val = c; }

// Takes another linked list input and appends it to the
// end of the current linked list. Adds the size of the two lists together
// for the new size.
void CharLinkedList::concatenate(CharLinkedList* other)
{
    // size will be incremented by the insertAt function
    for (int i = 0; i < other->currSize; i++) {
        insertAt(other->elementAt(i), currSize);
    }
}

// private/helpers

//nodeAt helper that finds the node at the index
CharLinkedList::Node*
CharLinkedList::nodeAt_recur_helper(Node* curNode, int start, int index) const
{
    // if we've made it to the desired index we stop
    if (start == index) {
        return curNode;
    }
    // otherwise we look at the next node
    else {
        start++;
        return nodeAt_recur_helper(curNode->next, start, index);
    }
}

// private function that takes an index and returns the node at that index.
CharLinkedList::Node* CharLinkedList::nodeAt(int index) const
{
    // make sure we are in range
    if (index <= currSize and index >= 0) {
        // look at all nodes from front/0 until we reach our desired index
        // or the end of our list, whichever is first
        Node* my_node = nodeAt_recur_helper(front, 0, index);
        return my_node;
    }
    // if out of range, throw error
    else {
        std::string error_msg = errorBuilder(index, currSize, ')');
        throw std::range_error(error_msg);
    }
};

std::string CharLinkedList::errorBuilder(int index, int size,
                                         char lastChar) const
{
    std::ostringstream errorstream;
    errorstream << "index (" << std::to_string(index);
    errorstream << ") not in range [0..";
    errorstream << std::to_string(size) << lastChar;
    return errorstream.str();
}

std::string CharLinkedList::stringBuilder(int size, std::string rawS) const
{
    std::stringstream my_string;
    my_string << "[CharLinkedList of size " << std::to_string(size);
    my_string << " <<" << rawS;
    my_string << ">>]";
    return my_string.str();
}

CharLinkedList::Node::Node() {
    next = nullptr;
    prev = nullptr;
};
CharLinkedList::Node::Node(char c) {
    next = nullptr;
    prev = nullptr;
    val = c;
};


CharLinkedList::Node* CharLinkedList::new_empty_node()
{
    // node has value and null next/prev pointers
    Node *c_node = new Node();
    return c_node;
}

CharLinkedList::Node* CharLinkedList::new_node(char c)
{
    // node has value and null next/prev pointers
    Node *c_node = new Node(c);
    return c_node;
}



{