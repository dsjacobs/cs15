# Makefile for HW1: ArrayList
# Matt Russell

CXX=clang++
CXXFLAGS=-g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS=-g3


timer: timer_main.o CharArrayList.o
	${CXX} ${LDFLAGS} -o timer timer_main.o CharArrayList.o

unit_tests: unit_tests.o CharArrayList.o
	${CXX} ${LDFLAGS} -o unit_tests unit_tests.o CharArrayList.o

CharArrayList.o: CharArrayList.cpp CharArrayList.h
	${CXX} ${CXXFLAGS} -c CharArrayList.cpp

unit_tests.o: unit_tests.cpp CharArrayList.h
	${CXX} ${CXXFLAGS} -c unit_tests.cpp

timer_main.o: timer_main.cpp CharArrayList.h
	${CXX} ${CXXFLAGS} -c timer_main.cpp

clean: 
	rm *.o a.out *~ *#
