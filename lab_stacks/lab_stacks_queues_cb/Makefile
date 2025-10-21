# Makefile for CircularBuffer, Stack, and Queue lab

CXX      = clang++
CXXFLAGS = -g3 -std=c++11 -Wall -Wextra 

default: main.cpp CircularBuffer.h Stack.h Queue.h
	${CXX} ${CXXFLAGS} -o partyPlaylist main.cpp

clean:
	rm -rf partyPlaylist *.dSYM *.o