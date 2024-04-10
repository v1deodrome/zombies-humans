//
// Created by jamzc on 2023-12-11.
//

#include "../headers/Zombie.h"
#include "../headers/Human.h"

Zombie::~Zombie() = default;

void Zombie::turn(City &city) {
    // Check if zombie has moved
    if (!moved) {
        auto eatableTiles = getOccupiedSpaces(city);
        // Kill zombie if they're too hungry
        if (starvePoints >= ZOMBIE_STARVE) {
            city.setOrganism(nullptr,pair<int,int>(x,y));
            city.numZombies--;
        }
        // move zombie (if possible
        // get adjacent tiles containing a human
        else if (!eatableTiles.empty()) {
            int randomIndex = getRandomSelection(static_cast<int>(eatableTiles.size()));
            // Eat human
            city.moveOrganism(pair<int,int>(x,y), eatableTiles[randomIndex]);
            city.numHumans--;
            // reset hunger counter
            starvePoints = 0;
        }
        else {
            // get empty tiles
            auto emptyTiles = getEmptySpaces(city);
            if (!emptyTiles.empty()) {
                int randomIndex = getRandomSelection(static_cast<int>(emptyTiles.size()));
                // move zombie to empty space
                city.moveOrganism(pair<int,int>(x,y), emptyTiles[randomIndex]);
            }
            // add to starve counter
            starvePoints++;
        }
        breedPoints++;
        // Zombie breeding
        if (breedPoints >= ZOMBIE_BREED) {
            eatableTiles = getOccupiedSpaces(city);
            if (!eatableTiles.empty()) {
                int randomIndex = getRandomSelection(static_cast<int>(eatableTiles.size()));
                // Turn human into a zombie
                city.setOrganism(new Zombie(eatableTiles[randomIndex].first, eatableTiles[randomIndex].second), eatableTiles[randomIndex]);
                city.numHumans--;
                city.numZombies++;
                // reset # of turns left to breed
                breedPoints = 0;
            }
        }
        moved = true;
    }
}

vector<pair<int, int>> Zombie::getOccupiedSpaces(City &city) {
    // Initialize vector
    vector<pair<int, int>> emptySpaces;
    // Check GetOrganism and determine if a value is in the vertical coordinates
    if (y+1 < GRID_HEIGHT && dynamic_cast<Human*>(city.getOrganism(x,y+1)) != nullptr) {
        emptySpaces.emplace_back(x,y+1);
    }
    if (y-1 >= 0 && dynamic_cast<Human*>(city.getOrganism(x,y-1)) != nullptr) {
        emptySpaces.emplace_back(x,y-1);
    }
    // Check horizontal coordinates
    if (x+1 < GRID_WIDTH && dynamic_cast<Human*>(city.getOrganism(x+1,y)) != nullptr) {
        emptySpaces.emplace_back(x+1,y);
    }
    if (x-1 >= 0 && dynamic_cast<Human*>(city.getOrganism(x-1,y)) != nullptr) {
        emptySpaces.emplace_back(x-1,y);
    }
    // Check diagonal spaces
    if (x-1 >= 0 && y-1 >= 0 && dynamic_cast<Human*>(city.getOrganism(x-1,y-1))) {
        emptySpaces.emplace_back(x-1,y-1);
    }
    if (x+1 < GRID_WIDTH && y+1 < GRID_HEIGHT && dynamic_cast<Human*>(city.getOrganism(x+1,y+1)) != nullptr) {
        emptySpaces.emplace_back(x+1,y+1);
    }
    if (x-1 >= 0 && y+1 < GRID_HEIGHT && dynamic_cast<Human*>(city.getOrganism(x-1,y+1)) != nullptr) {
        emptySpaces.emplace_back(x-1,y+1);
    }
    if (x+1 < GRID_WIDTH && y-1 >= 0 && dynamic_cast<Human*>(city.getOrganism(x+1,y-1)) != nullptr) {
        emptySpaces.emplace_back(x+1,y-1);
    }
    return emptySpaces;
}

vector<pair<int, int>> Zombie::getEmptySpaces(City &city) {
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
    // Check diagonal spaces
    if (city.getOrganism(x-1,y-1) == nullptr && x-1 >= 0 && y-1 >= 0) {
        emptySpaces.emplace_back(x-1,y-1);
    }
    if (city.getOrganism(x+1,y+1) == nullptr && x+1 < GRID_WIDTH && y+1 < GRID_HEIGHT) {
        emptySpaces.emplace_back(x+1,y+1);
    }
    if (city.getOrganism(x-1,y+1) == nullptr && x-1 >= 0 && y+1 < GRID_HEIGHT) {
        emptySpaces.emplace_back(x-1,y+1);
    }
    if (city.getOrganism(x+1,y-1) == nullptr && x+1 < GRID_WIDTH && y-1 >= 0) {
        emptySpaces.emplace_back(x+1,y-1);
    }
    return emptySpaces;
}
