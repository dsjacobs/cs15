/*
 * unit_tests.cpp
 *
 * CS15 Proj 2: Typewriter
 * 
 * TODO: Purpose
 *
 * Author: Danielle Jacobs
 */

#include "ActionStack.h"
#include <cassert>
#include <iostream>

void isEmpty_test() {
    std::cout << "Test 1: isEmpty" << std::endl;
    ActionStack my_stack;
    assert(my_stack.isEmpty());
}

void isEmpty_false() {
    std::cout << "Test 2: is not Empty" << std::endl;
    ActionStack my_stack;
    my_stack.push('j',false,0,0);
    assert(not my_stack.isEmpty());
}

void size_zero() {
    std::cout << "Test 3: size 0" << std::endl;
    ActionStack my_stack;
    assert(my_stack.size()==0);
}

void size_one() {
    std::cout << "Test 4: size 1" << std::endl;
    ActionStack my_stack;
    my_stack.push('j',false,0,0);
    assert(my_stack.size()==1);
}

void size_many() {
    std::cout << "Test 5: size many" << std::endl;
    ActionStack my_stack;
    my_stack.push('j',false,0,0);
    my_stack.push('k',false,0,1);
    my_stack.push('l',false,0,2);
    assert(my_stack.size()==3);
}

int main() {
    isEmpty_test();
    isEmpty_false();
    size_zero();
    size_one();
    size_many();
    return 0;
}