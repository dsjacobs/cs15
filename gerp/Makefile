###
### Makefile for Gerp Project
###
### Author:  Danielle Jacobs

## Note, you do NOT need rules for
## FSTree.o and DirNode.o as those (pre-compiled) object files are 
## provided to you.
## 
## At the end, you can delete this comment
## 

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

gerp: gerp.o main.o processing.o WordTable.o WordTableEntry.o DirNode.o FSTree.o
	$(CXX) $(CXXFLAGS) -o gerp gerp.o main.o processing.o WordTable.o \
	WordTableEntry.o DirNode.o FSTree.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp gerp.h

gerp.o: gerp.cpp gerp.h processing.h 
	$(CXX) $(CXXFLAGS) -c gerp.cpp

processing.o: processing.cpp FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) -c processing.cpp

WordTable.o: WordTable.cpp WordTableEntry.h
	$(CXX) $(CXXFLAGS) -c WordTable.cpp

WordTableEntry.o: WordTableEntry.cpp
	$(CXX) $(CXXFLAGS) -c WordTableEntry.cpp

unit_tests.o: unit_tests.cpp processing.h
	$(CXX) $(CXXFLAGS) -c unit_tests.cpp

unit_tests: unit_tests.o 
	$(CXX) $(CXXFLAGS) -o unit_tests unit_tests.o \
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
