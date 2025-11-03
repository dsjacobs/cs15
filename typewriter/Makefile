#########################################################
#             PROJECT 2            #
# Danielle Jacobs
# November 2, 2025

# The Makefile defines relationships and dependencies
# between files, and how/what to run to ensure complete
# compilation.
#########################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

ActionStack: ActionStack.o
	$(CXX) $(CXXFLAGS) -o ActionStack ActionStack.o

# This rule builds unit_tests.o
unit_tests.o: unit_tests.cpp ActionStack.h
	$(CXX) $(CXXFLAGS) -c unit_tests.cpp

# This rule builds ActionStack.o
ActionStack.o: ActionStack.cpp ActionStack.h
	$(CXX) $(CXXFLAGS) -c ActionStack.cpp

# This rule builds Unit Tests
unit_tests: unit_tests.o ActionStack.o
	$(CXX) $(CXXFLAGS) -o unit_tests unit_tests.o ActionStack.o

# remove executables, object code, and temporary files from the current folder
# -- the executable created by unit_test is called a.out
clean: 
	rm -f *.o *~ a.out
