#########################################################
#             PROJECT 1: MetroSim Makefile             #
# Danielle Jacobs
# October 5, 2025

# The Makefile defines relationships and dependencies
# between files, and how/what to run to ensure complete
# compilation.
#########################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

MetroSim: MetroSim.o main.o PassengerQueue.o Passenger.o Train.o Station.h
	$(CXX) $(CXXFLAGS) -o MetroSim MetroSim.o main.o PassengerQueue.o \
	Passenger.o Train.o

# This rule builds PassengerQueue.o
PassengerQueue.o: PassengerQueue.cpp PassengerQueue.h Passenger.h 
	$(CXX) $(CXXFLAGS) -c PassengerQueue.cpp

# This rule builds Passenger.o
Passenger.o: Passenger.cpp Passenger.h
	$(CXX) $(CXXFLAGS) -c Passenger.cpp

# This rule builds Train.o
Train.o: Train.cpp PassengerQueue.h Passenger.h
	$(CXX) $(CXXFLAGS) -c Train.cpp

# This rule builds unit_tests.o
unit_tests.o: unit_tests.cpp Passenger.h PassengerQueue.h Train.h Station.h
	$(CXX) $(CXXFLAGS) -c unit_tests.cpp

# This rule builds main.o
main.o: MetroSim.cpp MetroSim.h main.cpp Passenger.h PassengerQueue.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# This rule builds MetroSim.o
MetroSim.o: MetroSim.cpp MetroSim.h main.cpp Passenger.h PassengerQueue.h \
Train.o
	$(CXX) $(CXXFLAGS) -c MetroSim.cpp

# This rule builds Unit Tests
unit_tests: unit_tests.o Passenger.o PassengerQueue.o Station.h MetroSim.o \
Train.o
	$(CXX) $(CXXFLAGS) -o unit_tests unit_tests.o Passenger.o \
	PassengerQueue.o MetroSim.o Train.o


# remove executables, object code, and temporary files from the current folder
# -- the executable created by unit_test is called a.out
clean: 
	rm -f *.o *~ a.out
