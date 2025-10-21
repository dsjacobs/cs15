#
#  CS 15: Data Structures
#  Tufts University
#  Makefile for Lab 2
#
#  Makefile for planet-driver, LinkedList and Planet
#
CXX      = clang++
CXXFLAGS = -Wall -Wextra -Wpedantic -Wshadow -g
LDFLAGS  = -g

# linking targets
planet-driver: planet-driver.o LinkedList.o Planet.o
	$(CXX) $(LDFLAGS) -o planet-driver planet-driver.o LinkedList.o Planet.o 

unit_tests: unit_tests.o LinkedList.o Planet.o
	$(CXX) $(LDFLAGS) -o unit_tests unit_tests.o LinkedList.o Planet.o

# Rules to compile the dependencies
planet-driver.o: planet-driver.cpp LinkedList.h Planet.h
	$(CXX) $(CXXFLAGS) -c planet-driver.cpp

LinkedList.o: LinkedList.cpp LinkedList.h Planet.h
	$(CXX) $(CXXFLAGS) -c LinkedList.cpp

Planet.o: Planet.cpp Planet.h
	$(CXX) $(CXXFLAGS) -c Planet.cpp

unit_tests.o: unit_tests.cpp LinkedList.h Planet.h
	$(CXX) $(CXXFLAGS) -c unit_tests.cpp

clean:
	@rm -f *.o core* vgcore* *# *~ planet-driver
