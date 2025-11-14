#########################################################
#             PROJECT 2  Typewriter          
# Danielle Jacobs
# November 2, 2025

# The Makefile defines relationships and dependencies
# between files, and how/what to run to ensure complete
# compilation.
#########################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

#builds and links the main Typewriter
typewriter: main.o Editor.o ActionStack.o TextUI.o
	$(CXX) $(CXXFLAGS) -o typewriter main.o Editor.o \
	ActionStack.o TextUI.o -lncurses

#builds and links the ActionStack
ActionStack: ActionStack.o
	$(CXX) $(CXXFLAGS) -o ActionStack ActionStack.o

#builds and links the Editor
Editor: Editor.o ActionStack.o 
	$(CXX) $(CXXFLAGS) -o Editor Editor.o ActionStack.o 

#This rule builds main.o
main.o: main.cpp Editor.h ActionStack.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# This rule builds unit_tests.o
unit_tests.o: unit_tests.cpp ActionStack.h
	$(CXX) $(CXXFLAGS) -c unit_tests.cpp

# This rule builds ActionStack.o
ActionStack.o: ActionStack.cpp ActionStack.h
	$(CXX) $(CXXFLAGS) -c ActionStack.cpp

# This rule builds Editor.o
Editor.o: Editor.cpp ActionStack.h
	$(CXX) $(CXXFLAGS) -c Editor.cpp

# This rule builds unit tests for Action Stacks
unit_tests: unit_tests.o ActionStack.o
	$(CXX) $(CXXFLAGS) -o unit_tests unit_tests.o ActionStack.o

# remove executables, object code, and temporary files from the current folder
# -- the executable created by unit_test is called a.out
clean: 
	rm -f *.o *~ a.out
