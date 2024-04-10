//
// Created by jamzc on 2023-12-11.
//

#include "../headers/Human.h"

Human::~Human() = default;

void Human::turn(City &city) {
    // Check if human has moved
    if (!moved) {
        // Attempt to move human
        // get adjacent tiles
        auto validTiles = getEmptySpaces(city);
        if (!validTiles.empty()) {
            int randomIndex = getRandomSelection(static_cast<int>(validTiles.size()));
            // Move organism
            city.moveOrganism(pair<int,int>(x,y),validTiles[randomIndex]);
        }
        // increment breed counter
        breedPoints++;
        // Birth new human if human has survived HUMAN_BREED turns
        if (breedPoints >= HUMAN_BREED) {
            // get adjacent tiles
            auto moreValidTiles = getEmptySpaces(city);
            if (!moreValidTiles.empty()) {
                int randomIndex = getRandomSelection(static_cast<int>(moreValidTiles.size()));
                city.setOrganism(new Human(moreValidTiles[randomIndex].first,moreValidTiles[randomIndex].second),moreValidTiles[randomIndex]);
                city.numHumans++;
                // reset # of turns left to breed
                breedPoints = 0;
            }
        }
        // set entity to moved
        moved = true;
    }
}

vector<pair<int, int>> Human::getEmptySpaces(City &city) {
    // Initialize vector
    vector<pair<int, int>> emptySpaces;
    // Check GetOrganism and determine if a value is in the vertical coordinates
    if (city.getOrganism(x,y+1) == nullptr && y+1 < GRID_HEIGHT) {
        emptySpaces.emplace_back(x,y+1);
    }
    if (city.getOrganism(x,y-1) == nullptr && y-1 >= 0) {
        emptySpaces.emplace_back(x,y-1);
    }
    // Check horizontal coordinates
    if (city.getOrganism(x+1,y) == nullptr && x+1 < GRID_WIDTH) {
        emptySpaces.emplace_back(x+1,y);
    }
    if (city.getOrganism(x-1,y) == nullptr && x-1 >= 0) {
        emptySpaces.emplace_back(x-1,y);
    }

    return emptySpaces;
}
