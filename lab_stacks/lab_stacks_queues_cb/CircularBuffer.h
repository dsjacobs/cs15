/*
 *      CircularBuffer.h
 *      PartyPlaylist
 *      Comp 15 Lab 3
 *
 *      A class that represents an ordered sequence of elements.  This
 *      one is for strings.
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Modified by Mark A. Sheldon, Tufts University
 *                 Added documentation and nextIndex() function.
 *      2020-01-31 Modified by Juliana Vega
 *                 Removed "sequence" wording
 *      2022-02-09 Modified by Matt Russell
 *                 printBuffer->toString
 *      2025-09-24 Danielle Jacobs lab
 */


#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <sstream>
#include <string>

template<typename ElementType>
class CircularBuffer {
public:
    CircularBuffer() { init(INIT_CAPACITY); }
    CircularBuffer(int givenCapcity) { init(givenCapcity); }
    ~CircularBuffer() { delete[] bufferArray; }

    void addAtBack(ElementType elem) {
        if (currentSize == capacity) { expand(); }
        bufferArray[back] = elem;
        currentSize++;
        back = nextIndex(back);
    }

    void addAtFront(ElementType elem){
        if (currentSize == capacity) { expand(); }
        front = prevIndex(front);
        bufferArray[front] = elem;
        currentSize++;
    };

    ElementType removeFromBack() {
        if (currentSize == 0) throw std::range_error("empty!");
        ElementType elem = bufferArray[back];
        back = prevIndex(back);
        currentSize--;
        return elem;
    }

    ElementType removeFromFront() {
        if (currentSize == 0) throw std::range_error("empty!");
        ElementType elem = bufferArray[front];
        front            = nextIndex(front);
        currentSize--;
        return elem;
    }

    std::string toString() const {
        std::stringstream ss;
        int               currIndex = front;
        for (int i = 0; i < currentSize; i++) {
            ss << i + 1 << ": " << bufferArray[currIndex] << "\n";
            currIndex = nextIndex(currIndex);
        }
        return ss.str();
    }

private:
    static const int INIT_CAPACITY = 5;

    ElementType *bufferArray;
    int          currentSize;
    int          capacity;
    int          front;
    int          back;

    /*
     *  Purpose:    Gets the next index in the buffer
     *  Parameters: index - the index to increment
     *  Returns:    The index of the next element in the buffer.
     *  Notes:      Given the 'back' index of the buffer, this function returns
     *              the logical position to insert a new element, **not** the
     *              front index. Wraps around!
     */
    int nextIndex(int index) const {
        if (index == capacity - 1) {return 0;}
        else {return index ++;}
    }

    /*
     *  Name:       prevIndex
     *  Parameters: (int) - the index to decrement.
     *  Returns:    The index of the previous element in the buffer.
     *  Notes:      Given the 'front' index of the buffer, this function returns
     *              the logical position to insert a new element, **not** the
     *              back index. Wraps around!
     */
    int prevIndex(int index) const {
        if (index == 0) {return capacity - 1;}
        else {return index ++;}
    }

    void expand() {
        // TODO
    }

    void init(int givenCapacity) {
        capacity    = givenCapacity;
        bufferArray = new ElementType[capacity];
        currentSize = 0;
        front       = 0;
        back        = 0;
    }
};

#endif
