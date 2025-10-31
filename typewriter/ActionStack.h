/*
 * ActionStack.h
 *
 * CS15 Proj 2: Typewriter
 * 
 * Interface for the ActionStack class.
 *
 * Author: Milod Kazerounian (Sept 2025)
 * Edited By: Danielle Jacobs (Oct 2025)
 */

#ifndef __ACTIONSTACK_H__
#define __ACTIONSTACK_H__

class ActionStack {
public:
    /* The ActionStack will store Action instances, which capture actions
     * performed by the user. An Action comprises of: a `character`,
     * a bool denoting whether or not that character was `deleted`, and
     * a `line` and `column` for the character.
     */ 
    struct Action {
        char character;
        bool deleted;
        std::size_t line;
        std::size_t column;
    };

    /* Constructor, destructor, and member functions.
     * See the spec for the expected behavior of each of these.
     */
    ActionStack();
    ~ActionStack();

    bool isEmpty() const;
    int size() const;
    Action top() const;
    void pop();
    void push(Action elem);
    void push(char c, bool was_delete, std::size_t line, std::size_t column);
    void clear();

private:
    // Add any private member variables or functions as you see fit.
};





#endif
