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

typewriter: main.o Editor.o ActionStack.object
	$(CXX) $(CXXFLAGS) -o typewriter main.o ActionStack ActionStack.o

ActionStack: ActionStack.o
	$(CXX) $(CXXFLAGS) -o ActionStack ActionStack.o

Editor: Editor.o ActionStack.o 
	$(CXX) $(CXXFLAGS) -o Editor Editor.o ActionStack.o 

main.o: main.cpp Editor.h ActionStack.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# This rule builds unit_tests.o
unit_tests.o: unit_tests.cpp ActionStack.h
	$(CXX) $(CXXFLAGS) -c unit_tests.cpp

# This rule builds ActionStack.o
ActionStack.o: ActionStack.cpp ActionStack.h
	$(CXX) $(CXXFLAGS) -c ActionStack.cpp

Editor.o: Editor.cpp ActionStack.h
	$(CXX) $(CXXFLAGS) -c Editor.cpp

# This rule builds Unit Tests
unit_tests: unit_tests.o ActionStack.o
	$(CXX) $(CXXFLAGS) -o unit_tests unit_tests.o ActionStack.o

# remove executables, object code, and temporary files from the current folder
# -- the executable created by unit_test is called a.out
clean: 
	rm -f *.o *~ a.out
