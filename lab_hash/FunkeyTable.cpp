/*
 * FunkeyTable.cpp --- compare two different methods of handling hash
 * table collisions and two different hash functions.
 *
 * your job:  code the insert functions and expand function
 *  our job:  run the insert functions and report results
 *
 * Based on a previous lab by Ben Hescott, I think.
 *
 * Mark A. Sheldon, Tufts University, Spring 2017
 */

#include <iostream>
#include <stdio.h>
#include <functional>

#include "FunkeyTable.h"

using namespace std;

/*
 * Constructor allocates and initializes two empty tables
 * of the INITIAL_TABLE_SIZE
 */
FunkeyTable::FunkeyTable()
{
        currentTableSize = INITIAL_TABLE_SIZE;
        numItemsInTable = 0;

        chainedTable = new ChainNode *[currentTableSize];
        linearTable = new TableEntry[currentTableSize];

        for (int i = 0; i < currentTableSize; i++)
        {
                chainedTable[i] = nullptr;
                linearTable[i].isEmpty = true;
        }
}

/*
 * Delete all nodes in list starting with given node
 */
void FunkeyTable::deleteList(ChainNode *node)
{
        for (int i=0; i<ChainedTable.size(); i++) {
                *chain curr = ChainedTable[i]
                while (curr != nullptr) {
                        *node next = curr.next;
                        delete curr;
                        curr = next;
                }
        }
        delete ChainedTable;
}

/*
 * destructor
 */
FunkeyTable::~FunkeyTable()
{
        for (int i=0; i<ChainedTable.size(); i++) {
                deleteList(ChainedTable[i];)
        }
}

static size_t good_hash_function(KeyType key)
{
        return std::hash<KeyType>{}(key);
}

static size_t bad_hash_function(KeyType key)
{
        return key.length();
}

static size_t hashValue(KeyType key, FunkeyTable::HashFunction hashFunction)
{
        if (hashFunction == FunkeyTable::BAD_HASH_FUNCTION)
                return bad_hash_function(key);
        else
                return good_hash_function(key);
}

/*
 * Linear Probing
 *
 * Return number of collisions before finding a spot
 *
 */
int FunkeyTable::insertProbing(KeyType key, ValueType value,
                               HashFunction hashFunction)
{
        int attempt = 0;
        bool found = false;

        // NOTE:  You can put things here if it helps you

        while (not found)
        {
                // TODO:  Students write code here
                //        (you may write code outside the loop, too)
        }
        return attempt;
}

/*
 * Return length of list starting at given node
 */
int FunkeyTable::listLength(ChainNode *nodep)
{
        // TODO:  Students write code here
}

/*
 * Chained hashing --- each spot in table is a linked list
 *
 * Return number of items in that spot before insertion
 */
int FunkeyTable::insertChaining(KeyType key, ValueType value,
                                HashFunction hashFunction)
{
        // TODO: Students write code here
        // STUB: Replace with the correct code
        return 0;
}

/*
 * Expand both of the hash tables
 */
void FunkeyTable::expand(HashFunction hashFunction)
{
        // TODO: Students write code here
}

void FunkeyTable::printTableEntry(TableEntry entry)
{
        if (entry.isEmpty)
                cout << "empty";
        else
                cout << "key:  "
                     << entry.key
                     << "; value:  {"
                     << entry.value.chartPosition
                     << ", "
                     << entry.value.bpm
                     << "}";
}

void FunkeyTable::printChainNode(ChainNode *nodep)
{
        cout << "key:  " << nodep->key
             << "; value:  {" << nodep->value.chartPosition
             << ", " << nodep->value.bpm << "}";
}

/*
 * Print both hash tables
 * Could break this up into two print functions
 */
void FunkeyTable::print()
{
        cout << "Linear table" << endl;

        for (int i = 0; i < currentTableSize; ++i)
        {
                cout << i << ":  ";
                printTableEntry(linearTable[i]);
                cout << endl;
        }
        cout << endl
             << "Chained table" << endl;

        for (int i = 0; i < currentTableSize; ++i)
        {
                ChainNode *curr = chainedTable[i];
                cout << i << ":  [ ";
                while (curr != NULL)
                {
                        printChainNode(curr);
                        curr = curr->next;
                        if (curr != NULL)
                                cout << ", ";
                }
                cout << "]" << endl;
        }
        cout << endl;
}
