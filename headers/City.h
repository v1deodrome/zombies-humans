#ifndef _CITY_H
#define _CITY_H

#include <iostream>
#include "GameSpecs.h"

using namespace std;

class Organism;

const int GRID_WIDTH = GRIDSIZE;
const int GRID_HEIGHT = GRIDSIZE;

class City
{
protected:
    // Grid where the whole game plays out on
	Organism *grid[GRID_HEIGHT][GRID_WIDTH]{};

public:
    // Number of zombies and humans
    int numHumans = 0;
    int numZombies = 0;

    // Constructor
	City();

    // Destructor
    virtual ~City();

    // Gets an organism by their coordinates
	Organism *getOrganism( int x, int y );

    // Sets an organism as another (or a nullptr)
    void setOrganism(Organism *organism, pair<int,int> coord);

    // Moves an organism to a coordinate, replacing original position with a null pointer
    void moveOrganism(pair<int,int> location, pair<int,int> destination);

    // Call every zombie/human, and have them take their actions
    void turn();

    // Print grid to output
	friend ostream& operator<<( ostream &output, City &city );
};

#endif

