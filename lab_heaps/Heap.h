/* Comp 15 Lab 10: Heaps
 *
 * A class that organizes a collection of strings into a min-heap
 *
 * O(n log n) construction (can be O(n) if you use algorithm from class!
 * O(log n)   insertion
 * O(1)       to access minimum element
 * O(log n)   to remove minimum element.
 */
#ifndef __HEAP_H__
#define __HEAP_H__

#include <vector>

class Heap
{
public:
    // Build a heap from array
    Heap(std::vector<int> list);

    // remove and return smallest element in heap
    int removeMin();

    // insert a value into heap, not used for this lab
    void insert(int value);

    // return minimum element, not used for this lab
    int min() const;

private:
    std::vector<int> heap;

    // downHeap restores the heap property going downwards from the given index.
    // is recursive.
    void downHeap(int location);

    //
    // upHeap restores the heap property going upwards from the given index.
    // is recursive.
    void upHeap(int location);

    // build heap function used by constructor that takes in an array
    // and turns the array into a heap (aka "heapify")
    void buildHeap();

    //
    // abstract away calculations for child/parent relationships
    //
    int leftChild(int index);
    int rightChild(int index);
    int parent(int index);
};

#endif