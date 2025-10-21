/*
 * Planet.cpp
 *
 * Comp 15 Lab 2
 * Edited by Elizabeth Hom, Sept 2020
 * Edited by Matt Russell, Juliana Vega, and Alexis Blair, Jan 2021
 *
 * The Planet class contains functions and info regarding a Planet object.
 */

#include "Planet.h"
#include <sstream>
#include <string>

/*
 * Default constructor
 */
Planet::Planet() {}

/* Parametrized constructor
 *    Purpose: Creates a Planet object with the given name and distanc
 * Parameters: string - name of planet
 *    Returns: None
 */
Planet::Planet(std::string name, int distance_from_sun) {
    this->name              = name;
    this->distance_from_sun = distance_from_sun;
}


/* Copy constructor
 *    Purpose: Updates the information of 'this' to be the same as that of
 *             'other'
 * Parameters: another planet object
 *    Returns: None
 */
Planet::Planet(const Planet &other) {
    this->name              = other.name;
    this->distance_from_sun = other.distance_from_sun;
}

/* Operator= overload
 *    Purpose: Updates the information of 'this' to be the same as that of
 *             'other'
 * Parameters: Another planet object
 *    Returns: Reference to 'this' object
 */
Planet &Planet::operator=(const Planet &other) {
    if (this != &other) {
        this->name              = other.name;
        this->distance_from_sun = other.distance_from_sun;
    }
    return *this;
}


/* toString
 *    Purpose: Returns a string with the planet's info
 * Parameters: None
 *    Returns: String with the name and distance to the sun of a given planet
 */
std::string Planet::toString() const {
    std::stringstream ss;
    ss << this->name << ": " << this->distance_from_sun;
    return ss.str();
}
