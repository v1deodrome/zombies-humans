#ifndef _Human_H
#define _Human_H

#include "Organism.h"

class Human : public Organism
{
public:
    // Constructor
    Human() : Organism() {};
	Human(int x, int y) : Organism(x,y) {};

    // Destructor
	~Human() override;

    // Takes all necessary actions the human can take in a turn
	void turn(City &city) override;

    // Get all valid directions that a human can move in
    vector<pair<int,int>> getEmptySpaces(City &city);
};

#endif
