/*
 *      Queue.h
 *      PartyPlaylist
 *      Comp 15 Lab 3
 *
 *      A class that represents a queue of elements.
 *      The type ElementType is presumed to be defined before this
 *      file is included.
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Modified by Mark A. Sheldon
 *                 Added documentation, include guards
 *                 Removed unnecessary includes
 *      2020-01-31 Modified by Juliana Vega
 *                 Removed "sequence" wording
 *      2025-09-24 Danielle Jacobs lab
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "CircularBuffer.h"
#include <string>

template<typename ElementType>
class Queue {
public:
    Queue() {}
    Queue(int initialCapacity) : queue(initialCapacity) {}
    ~Queue() {}

    ElementType dequeue() {
        CircularBuffer.removeFromFront();
    }

    void enqueue(ElementType element) {
        CircularBuffer.addAtBack();
    }

private:
    CircularBuffer<ElementType> queue;
};

#endif
