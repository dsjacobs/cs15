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
ActionStack::ActionStack();
ActionStack::~ActionStack();

ActionStack::isEmpty() const {
    return listStack.empty();
}
ActionStack::size() const {
    return listStack.size();
}
ActionStack::Action::top() const {
    if isEmpty() {
        throw std::runtime_error('empty_stack');
    }
    return listStack.front();
}
ActionStack::pop() {
    if isEmpty() {
        throw std::runtime_error('empty_stack');
    }
    listStack.pop_front();
}
ActionStack::push(ActionStack::Action elem) {
    listStack.push_front(elem);
}
ActionStack::push(char c, bool was_delete, std::size_t line, std::size_t column) {
    ActionStack::Action elem;
    elem.character = c;
    elem.deleted = was_delete;
    elem.line = line;
    elem.column = column;
    push(elem);
}
ActionStack::clear() {
    listStack.erase();
}
