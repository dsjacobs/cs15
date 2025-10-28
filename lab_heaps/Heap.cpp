/* Comp 15 Lab 10: Heaps
 * Implementation of Heap class with string keys
 * Updated 11/2/2020 by Ellis Brown
 * Edited by:
 */

#include <iostream>

#include "Heap.h"

using namespace std;

Heap::Heap(vector<int> list)
{
    // store a sentinal value of -1 at position 0
    // this makes parent/child calculations much more straightforward.
    heap.push_back(-1);

    // copy the unsorted list over
    for (int i = 0; i < (int)list.size(); i++)
    {
        heap.push_back(list[i]);
    }

    // use the build heap function to make it a heap
    buildHeap();
}

/*
 * insert a string into the heap.
 * requires the function upHeap to be implemented
 */
void Heap::insert(int value)
{

    heap.push_back(value);
    upHeap(heap.size());
}

/*
 * return smallest element in heap
 */
int Heap::min() const
{
    // "TODO: YOUR CODE HERE";
    return -1;
}

/*
 * remove and return smallest element in heap
 */
int Heap::removeMin()
{
    // "TODO: YOUR CODE HERE";
    return -1;
}

/*
 * downHeap establishes/verifies heap invariant from given
 * location down to leaves
 * if parent is out of order with respect to children,
 * swap with smaller child and downHeap from updated child
 */
void Heap::downHeap(int location)
{
    // TODO: your code here
    (void)location; // remove this line
}

/* NOT required for this lab, but you can write it if you have time
 * upHeap reestablishes heap invariant from given node to root
 * If child is out of order with respect to parent, swap and
 * continue to upHeap from parent to root
 */
void Heap::upHeap(int location)
{
    (void)location; // Removes compiler warning about unused variable.
}

/*
 * creates a heap out of the unsorted array.
 * Naive algorithm is O(n log n)
 * Algorithm from class/prelab is O(n) (proof in 160)
 */
void Heap::buildHeap()
{
    // TODO: your code here
}

/*
 * Return left child for element at given index
 */
int Heap::leftChild(int index)
{
    return index * 2;
}

/*
 * Return right child for element at given index
 */
int Heap::rightChild(int index)
{
    return (index * 2) + 1;
}

/*
 * Return the parent for element at given index
 */
int Heap::parent(int index)
{
    return index / 2; // note integer division
}
