#
# Makefile for Heap Lab
#
CXX      = clang++
CXXFLAGS = -Wall -Wextra -Wreturn-type -g -std=c++11
LDFLAGS  = -g

heapSort: main.o Heap.o
	${CXX} ${CXXFLAGS} -o heapSort main.o Heap.o

main.o:  main.cpp Heap.h
Heap.o:  Heap.cpp Heap.h

clean:
	rm -rf heapSort *.o *.dSYM
