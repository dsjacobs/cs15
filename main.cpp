/*
 * Comp 15:  Heap lab
 *
 */

#include <iostream>
#include <vector>
#include "Heap.h"

using namespace std;

int main()
{
    vector<int> toHeapify = {9, 8, 7, 6, 5, 4, 3, 2, 1};

    // make a heap from the original list
    Heap h(toHeapify);

    vector<int> heapified;
    for (int i = 0; i < (int)toHeapify.size(); i++)
    {
        heapified.push_back(h.removeMin());
    }

    for (int i = 0; i < heapified.size(); i++)
    {
        std::cout << heapified[i] << " ";
    }
    cout << "\n";

    return 0;
}
