/*
 *      main.cpp
 *      PartyPlaylist
 *      Comp 15 Lab 3
 *
 *      Simple test program that tests the code for the lab.  The
 *      testing is not as thorough as one might like, but it's a
 *      start.  You should extend the CircularBuffer tests at
 *      least.  What cases are important to test?
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Updated by Mark A. Sheldon, Tufts University
 *                 Documenation, factored testing into separate
 *                 functions.
 *      2019-08-01 Modified by Alice Dempsey
 *      2020-01-31 Modified by Juliana vega
 *                 Removed "sequence" wording
 *      2020-09-21 Modified by Matt Champlin
 *                 Updated songs to be current top 10.
 *                 Removed numbering from songs. Print function handles
 *                 numbering now.
 *                 Made parameters in tests void to avoid warnings.
 *      2025-09-24 Danielle Jacobs lab homework
 *
 */

#include <iostream>

#include "CircularBuffer.h"
#include "Queue.h"
#include "Stack.h"

using namespace std;

void testCircularBuffer(string songs[], int numSongs);
void testStack(string songs[], int numSongs);
void testQueue(string songs[], int numSongs);



int main() {
    string songs[10] = {"Dynamite", "Laugh Now Cry Later", "Rockstar",      "Blinding Lights",
                        "Mood",     "Watermelon Sugar",    "What's Poppin", "Savage Love",
                        "Popstar",  "Before You Go"};

    const int numSongs = sizeof(songs) / sizeof(string);

    testCircularBuffer(songs, numSongs);

    // Uncomment each test as you write each part
    // testStack(songs, numSongs);
    // testQueue(songs, numSongs);

    // cout << "\n\t\t**** Wrap-Up Questions ****\n"
    //      << "In your opinion, which data structure is better for a DJ"
    //      << " table? \nWhich one is better for a Top 10 Countdown on the"
    //      << " radio?\n\n";
    // cout << "How do stacks and queues interact with each other?\n"
    //      << "What happens when you dequeue into a stack and then"
    //      << " pop everything off?\n\n";

    return 0;
}

/**********************************************************************
 *******************  TEST ONE: Testing Buffer  **********************
 ***********************************************************************/

/*  Purpose: Test all CircularBuffer functions are working as expected.
 *  Parameters: songs[]  - a predetermined list of songs
 *              numsongs - The number of songs in songs[]
 */
void testCircularBuffer(string songs[], int numSongs) {
    // TODO: Write more tests for testing the Buffer.
    //       You can use the songs array for your tests.
    cout << "Testing CircularBuffer: \n";
    cout << "first addAtBack test" << endl;
    CircularBuffer<std::string> buffOne(numSongs);
    for (int i = 0; i < numSongs; i++) {
        buffOne.addAtBack(songs[i]);
        cout << buffOne.toString() << endl;
    }

    cout << "first addAtFront test" << endl;
    CircularBuffer<std::string> buffTwo(numSongs);
    for (int i = 0; i < numSongs; i++) {
        buffTwo.addAtFront(songs[i]);
        cout << buffTwo.toString() << endl;
    }
}

/***********************************************************************
 **********************  TEST TWO: Testing Stack  **********************
 ***********************************************************************/

/*  Purpose: Tests Stack class
 *  Parameters: songs[]  - a predetermined list of songs
 *              numsongs - The number of songs in songs[]
 */
void testStack(string songs[], int numSongs) {
    cout << "\nTesting Stack: \n";

    Stack<std::string> myStack(numSongs * 2);
    // add all songs to the stack
    for (int i = 0; i < numSongs; i++) {
        cout << "Adding " << songs[i] << " to playlist.\n";
        myStack.push(songs[i]);
    }

    myStack.push("Old Town Road");
    cout << "Playing " << myStack.pop() << endl;
    cout << "Love that song! Let's request it again.\n";

    myStack.push("Old Town Road");
    cout << "Playing " << myStack.pop() << endl;

    cout << "Now, the top ten should still be there: \n";
    for (int i = 0; i < numSongs; i++) {
        cout << myStack.pop() << endl;
    }

    cout << "Nice work! Do you think this data structure works well as\n"
         << "a playlist for a party? Would a Queue work better or worse?\n";
}

/**********************************************************************
 ********************  TEST THREE: Testing Queue  **********************
 ***********************************************************************/

/*  Purpose: Tests Queue class.
 *  Parameters: songs[]  - a predetermined list of songs
 *              numsongs - The number of songs in songs[]
 */
void testQueue(string songs[], int numSongs) {
    // TODO: Write more tests for testing the queue.
    //       Think about how a queue keeps track of the next song
    //       and how you can test that through enqueue and dequeue

    cout << "\nTesting Queue: \n";

    Queue<std::string> myQueue(numSongs * 2);
    // add all songs to the queue
    for (int i = 0; i < numSongs; i++) {
        cout << "Adding " << songs[i] << " to playlist.\n";
        myQueue.enqueue(songs[i]);
    }
    cout << "\nLets start the playlist!" << endl;
    cout << "Next up:\n";
    for (int i = 0; i < numSongs; i++) {
        cout << myQueue.dequeue() << endl;
    }
}
