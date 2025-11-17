/*
 * ActionStack.cpp
 *
 * CS15 Proj 2: Typewriter
 * 
 * Action stacks can be popped from or pushed to; their size and whether they
 * are empty can be checked, and they can be cleared/emptied.
 *
 * Author: Danielle Jacobs
 */

#include "ActionStack.h"
#include <stdexcept>

ActionStack::ActionStack() {};
ActionStack::~ActionStack() {};

// returns whether the action stack is empty
bool ActionStack::isEmpty() const {
    return listStack.empty();
}

// returns the size of the action stack
int ActionStack::size() const {
    return listStack.size();
}

// returns the first action in the action stack, or, if stack is empty,
// throws a runtime error.
ActionStack::Action ActionStack::top() const {
    if (isEmpty()) {
        throw std::runtime_error("empty_stack");
    }
    return listStack.front();
}

// removes the top action in the action stack, or, if stack is empty, throws
// a runtime error.
void ActionStack::pop() {
    if (isEmpty()) {
        throw std::runtime_error("empty_stack");
    }
    listStack.pop_front();
}

// Adds a provided action to the action stack.
void ActionStack::push(ActionStack::Action elem) {
    listStack.push_front(elem);
}

// Creates a new action based on its provided components, and adds it
// to the action stack.
void ActionStack::push(char c, bool was_delete, std::size_t line,
                                             std::size_t column) {
    ActionStack::Action elem;
    elem.character = c;
    elem.deleted = was_delete;
    elem.line = line;
    elem.column = column;
    push(elem);
}

// Clears or empties the action stack.
void ActionStack::clear() {
    listStack.clear();
}
