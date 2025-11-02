/*
 * Makefile
 *
 * CS15 Proj 2: Typewriter
 * 
 * TODO: Purpose
 *
 * Author: Danielle Jacobs
 */

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

ActionStack: ActionStack.o
	$(CXX) $(CXXFLAGS) -o ActionStack ActionStack.o

ActionStack.o: ActionStack.cpp ActionStack.h
	$(CXX) $(CXXFLAGS) -c ActionStack.cpp