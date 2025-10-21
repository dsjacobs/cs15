/*
 Danielle Jacobs
 October 2, 2025
 MetroSim

 A series of test for the passenger and passenger queue classes to
 ensure that new passengers and queues are properly created and printed.
 */

#include "Passenger.h"
#include "PassengerQueue.h"
#include "Station.h"
#include "MetroSim.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>

// Single passenger is created properly
void create_passenger() {
    std::cout << "test 1" << std::endl;
    Passenger bob(1,3,5);
    assert(bob.id = 1);
    assert(bob.from = 3);
    assert(bob.to = 5);
}

// Single passenger is printed properly
void print_passenger() {
    std::cout << "test 2" << std::endl;
    Passenger bob(1,3,5);
    std::ostringstream oss;
    bob.print(oss); 
    std::string output = oss.str();
    assert(output=="[1, 3->5]");
}

// A passenger created without values prints with negative 1s.
void print_null_passenger() {
    std::cout << "test 3" << std::endl;
    Passenger bob;
    // with help from the classs chatbot
    std::ostringstream oss;
    bob.print(oss); // Assuming passenger.print takes std::ostream&
    std::string output = oss.str();
    assert(output=="[-1, -1->-1]");
}

// One passenger enqueued increases size by one.
void enqueue_once() {
    std::cout << "test 4" << std::endl;
    PassengerQueue my_pq;
    assert(my_pq.size()==0);
    Passenger tom;
    my_pq.enqueue(tom);
    assert(my_pq.size()==1);
};

// 20 Passengers added with a loop result in the queue of size 20.
void enqueue_loopily() {
    std::cout << "test 5" << std::endl;
    PassengerQueue my_pq;
    for (int i = 0; i < 20; i++) {
        Passenger pas;
        my_pq.enqueue(pas);
    }
    assert(my_pq.size()==20);
};

// Adding 3 passengers separately results in a queue of size 3.
void enqueue_many() {
    std::cout << "test 6" << std::endl;
    PassengerQueue my_pq;
    Passenger pas1;
    Passenger pas2;
    Passenger pas3;
    my_pq.enqueue(pas1);
    my_pq.enqueue(pas2);
    my_pq.enqueue(pas3);
    assert(my_pq.size()==3);
};

// Trying to take front on an empty passenger queue throws an error.
void front_zero() {
    std::cout << "test 7" << std::endl;
    PassengerQueue my_pq;

    bool range_error_thrown = false;
    std::string error_message = "";
    try {
        my_pq.front();
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    assert(range_error_thrown);
    assert(error_message == "Cannot get first element of empty list");
};

// Calling the front of a one passenger queue returns that passenger.
void front_one() {
    std::cout << "test 8" << std::endl;
    PassengerQueue my_pq;
    Passenger bill(1,3,5);
    my_pq.enqueue(bill);
    std::ostringstream oss;
    my_pq.front().print(oss);
    std::string output = oss.str();
    assert(output=="[1, 3->5]");
}

// Calling front on a queue of multiple people still 
// returns the first passenger.
void front_many() {
    std::cout << "test 9" << std::endl;
    PassengerQueue my_pq;
    Passenger bill(1,3,5);
    Passenger joe(10,2,8);
    Passenger sue(4,6,1);
    my_pq.enqueue(bill);
    my_pq.enqueue(joe);
    my_pq.enqueue(sue);
    std::ostringstream oss;
    my_pq.front().print(oss); 
    std::string output = oss.str();
    assert(output=="[1, 3->5]");
    assert(my_pq.size()==3);
};

// Calling dequeue on an empty queue throws an error.
void dequeue_empty() {
    std::cout << "test 10" << std::endl;
        PassengerQueue my_pq;

    bool range_error_thrown = false;
    std::string error_message = "";
    try {
        my_pq.dequeue();
    }
    catch (const std::range_error &e) {
        range_error_thrown = true;
        error_message = e.what();
    }
    assert(range_error_thrown);
    assert(error_message == "Cannot dequeue from empty list");
};

// Calling dequeue on a list of one results in an empty queue.
void dequeue_one() {
    std::cout << "test 11" << std::endl;
    PassengerQueue my_pq;
    Passenger bill(1,3,5);
    my_pq.enqueue(bill);
    assert(my_pq.size()==1);
    my_pq.dequeue();
    assert(my_pq.size()==0);
};

// Dequeueing on a list of many changes front to what used to be 
// the second passenger.
void dequeue_many() {
    std::cout << "test 12" << std::endl;
    PassengerQueue my_pq;
    Passenger bill(1,3,5);
    Passenger joe(10,2,8);
    Passenger sue(4,6,1);
    my_pq.enqueue(bill);
    my_pq.enqueue(joe);
    my_pq.enqueue(sue);
    my_pq.dequeue();
    assert(my_pq.size()==2);
    std::ostringstream oss;
    my_pq.front().print(oss); 
    std::string output = oss.str();
    assert(output=="[10, 2->8]");
}

// An empty queue has size 0
void size_empty() {
    std::cout << "test 13" << std::endl;
    PassengerQueue my_pq;
    assert(my_pq.size()==0);
};

// Calling size on a queue of one returns one.
void size_one() {
    std::cout << "test 14" << std::endl;
    PassengerQueue my_pq;
    Passenger bill(1,3,5);
    my_pq.enqueue(bill);
    assert(my_pq.size()==1);
};

// Calling size on a queue of 3 returns 3.
void size_many() {
    std::cout << "test 15" << std::endl;
    PassengerQueue my_pq;
    Passenger bill(1,3,5);
    Passenger joe(10,2,8);
    Passenger sue(4,6,1);
    my_pq.enqueue(bill);
    my_pq.enqueue(joe);
    my_pq.enqueue(sue);
    assert(my_pq.size()==3);
};

// Printing an empty queue prints an empty string.
void print_empty() {
    std::cout << "test 16" << std::endl;
    PassengerQueue my_pq;
    std::ostringstream oss;
    my_pq.print(oss); 
    std::string output = oss.str();
    assert(output=="");
};

// Printing on a queue of one prints just the one passenger.
void print_one() {
    std::cout << "test 17" << std::endl;
    PassengerQueue my_pq;
    Passenger joe(10,2,8);
    my_pq.enqueue(joe);
    std::ostringstream oss;
    my_pq.print(oss); 
    std::string output = oss.str();
    assert(output=="[10, 2->8]");
};

// Printing a queue of 3 prints all 3 passengers.
void print_many() {
    std::cout << "test 18" << std::endl;
    Passenger bill(1,3,5);
    Passenger joe(10,2,8);
    Passenger sue(4,6,1);
    PassengerQueue my_pq;
    my_pq.enqueue(bill);
    my_pq.enqueue(joe);
    my_pq.enqueue(sue);
    std::ostringstream oss;
    my_pq.print(oss);
    std::string output = oss.str();
    assert(output=="[1, 3->5][10, 2->8][4, 6->1]");
};

// Adding a new station increments the number of stations by one.
void create_station() {
    std::cout << "test 19" << std::endl;
    Station my_station(1, "Alewife");
    assert(my_station.id==1);
    assert(my_station.name=="Alewife");
    MetroSim my_metrosim("stations.txt", "output.txt");
    assert(my_metrosim.num_stations()==26);
    my_metrosim.add_station(my_station);
    assert(my_metrosim.num_stations()==27);
};

// Stations can be created in loops and result in a queue of the right size.
void create_multiple_stations_loopily() {
    std::cout << "test 19" << std::endl;
    MetroSim my_metrosim("stations.txt", "output.txt");
    for (int i = 0; i < 10; i++) {
        Station my_station(i, "Name");
        my_metrosim.add_station(my_station);
    }
    assert(my_metrosim.num_stations()==37);
};

// A stations file can be read.
void read_stations_file() {
    std::cout << "test 20" << std::endl;
    string filename = "stations.txt";
    MetroSim my_metrosim(filename, "output.txt");
    std::ostringstream oss;
    my_metrosim.print_stations(oss);
    std::string output = oss.str();
        std::cout << "end of test 20" << std::endl;

}

// Print all prints both the train and the stations.
void print_state_all() {
    std::cout << "test 21" << std::endl;
    string filename = "stations.txt";
    MetroSim my_metrosim(filename, "output.txt");
    std::ostringstream oss;
    my_metrosim.print_all(oss);
    std::string output = oss.str();
    std::cout << output;
}

int main () {
    create_passenger(); //1
    print_passenger(); //2
    print_null_passenger(); //3

    enqueue_once(); //4
    enqueue_loopily(); //5
    enqueue_many(); //6

    front_zero(); //7
    front_one(); //8
    front_many(); //9

    dequeue_empty(); //10
    dequeue_one(); //11
    dequeue_many(); //12

    size_empty(); //13
    size_one(); //14
    size_many(); //15

    print_empty(); //16
    print_one(); //17
    print_many(); //18

    create_station(); //19
    read_stations_file(); //20

    return 0;
}