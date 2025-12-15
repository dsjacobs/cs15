###
### Makefile for Gerp Project
###
### Author:  Danielle Jacobs
### November 2025
###
### This Makefile defines relationships and dependencies
### between files, and how/what to run to ensure complete
### compilation.

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

#This rule builds the gerp executable
gerp: gerp.o main.o processing.o WordTable.o WordTableEntry.o DirNode.o FSTree.o
	$(CXX) $(CXXFLAGS) -o gerp gerp.o main.o processing.o WordTable.o \
	WordTableEntry.o DirNode.o FSTree.o

#This rule build main.o
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp gerp.h

#This rule builds gerp.o
gerp.o: gerp.cpp gerp.h processing.h 
	$(CXX) $(CXXFLAGS) -c gerp.cpp

#This rule builds processing.o
processing.o: processing.cpp FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) -c processing.cpp

#This rule builds WordTable.o
WordTable.o: WordTable.cpp WordTableEntry.h
	$(CXX) $(CXXFLAGS) -c WordTable.cpp

#This rule builds WordTableEntry.o
WordTableEntry.o: WordTableEntry.cpp
	$(CXX) $(CXXFLAGS) -c WordTableEntry.cpp

#This rule builds unit_tests.o
unitTests.o: unitTests.cpp processing.h
	$(CXX) $(CXXFLAGS) -c unitTests.cpp

#This rule builids the unit_tests executable
unitTests: unitTests.o 
	$(CXX) $(CXXFLAGS) -o unitTests unitTests.o \
	processing.o DirNode.o FSTree.o gerp.o WordTable.o
##
## Here is a special rule that removes all .o files besides the provided ones 
## (DirNode.o and FSTree.o), all temporary files (ending with ~), and 
## a.out produced by running unit_test. First, we find all .o files 
## that are not provided files, then we run rm -f on each found file 
## using the -exec find flag. Second, we delete the temporary files
## and a.out. @ is used to suppress stdout.
## 
## You do not need to modify or further comment this rule!
##
clean:
	@find . -type f \( \
		-name '*.o' ! -name 'FSTree.o' ! -name 'DirNode.o' \
		\) -exec rm -f {} \;
	@rm -f *~ a.out

# # DO NOT DELETE

# gerp.o: gerp.h processing.h
# main.o: gerp.h 
# processing.o: processing.h FSTree.h DirNode.h
# FSTree.o: DirNode.h
