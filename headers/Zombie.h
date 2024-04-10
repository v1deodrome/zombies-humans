#ifndef _Zombie_H
#define _Zombie_H

#include "Organism.h"

class Zombie : public Organism
{
    // if >= ZOMBIE_STARVE, zombie dies
    int starvePoints;
public:
    // Constructor
    Zombie() : Organism() { this->starvePoints = 0; };
    Zombie(int x, int y) : Organism(x,y) { this->starvePoints = 0; };

    // Destructor
	~Zombie() override;

    // Move the Zombie
	void turn(City &city) override;

    // Get all valid directions that a zombie can eat in
    vector<pair<int,int>> getOccupiedSpaces(City &city);

    // Get all empty directions that a zombie can move in
    vector<pair<int,int>> getEmptySpaces(City &city);
};

#endif
