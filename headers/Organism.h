#ifndef _Organism_H
#define _Organism_H

#include "City.h"
#include <iostream>
#include <vector>

using namespace std;

class Organism
{
protected:
	int x;
	int y;
    // if >= ZOMBIE_BREED/HUMAN_BREED, organism makes a copy of itself
    int breedPoints;
public:
    // has moved once during the turn
    bool moved;

    // Default constructor (doesn't initialize coordinates)
    Organism();
    // Two parameter constructor (initializes coordinates
	Organism(int x, int y );

    // Destructor
	virtual ~Organism();

    // This method only serves to be overrided by subclasses.
    virtual void turn(City &city) = 0;

    // Get a random int (usually for getting a coordinate)
    static int getRandomSelection(int max);

    // Set the coordinates of an organism
    void setCoords(int inputX, int inputY);
};

#endif
