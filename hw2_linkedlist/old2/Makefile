CXX=clang++
CXXFLAGS=-g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS=-g3

default: unit_tests

timer: timer_main.o CharLinkedList.o
	${CXX} ${LDFLAGS} -o timer timer_main.o CharLinkedList.o

unit_tests: unit_tests.o CharLinkedList.o
	$(CXX) ${LDFLAGS} -o unit_tests unit_tests.o CharLinkedList.o

CharLinkedList.o: CharLinkedList.cpp CharLinkedList.h
	$(CXX) -c CharLinkedList.cpp

unit_test.o: unit_tests.cpp CharLinkedList.h
	${CXX} ${CXXFLAGS} -c unit_tests.cpp

timer_main.o: timer_main.cpp CharLinkedList.h
	${CXX} ${CXXFLAGS} -c timer_main.cpp

clean:
	@rm -r *~ *# *.o a.out core* vgcore*
