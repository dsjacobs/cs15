/*
 * ActionStack.cpp
 *
 * CS15 Proj 2: Typewriter
 * 
 * Interface for the ActionStack class.
 *
 * Author: Danielle Jacobs
 */

#include "ActionStack.h"
#include <stdexcept>

ActionStack::ActionStack() {};
ActionStack::~ActionStack() {};

bool ActionStack::isEmpty() const {
    return listStack.empty();
}
int ActionStack::size() const {
    return listStack.size();
}
ActionStack::Action ActionStack::top() const {
    if (isEmpty()) {
        throw std::runtime_error("empty_stack");
    }
    return listStack.front();
}
void ActionStack::pop() {
    if (isEmpty()) {
        throw std::runtime_error("empty_stack");
    }
    listStack.pop_front();
}
void ActionStack::push(ActionStack::Action elem) {
    listStack.push_front(elem);
}
void ActionStack::push(char c, bool was_delete, std::size_t line, std::size_t column) {
    ActionStack::Action elem;
    elem.character = c;
    elem.deleted = was_delete;
    elem.line = line;
    elem.column = column;
    push(elem);
}
void ActionStack::clear() {
    listStack.erase();
}
