//
// Created by jamzc on 2023-12-11.
//

#include <algorithm>
#include <random>
#include <windows.h>
#include <chrono>

#include "../headers/City.h"
#include "../headers/Human.h"
#include "../headers/Zombie.h"

City::City() {
    // Initialize number of zombies in the list
    numHumans = 0;
    numZombies = 0;
    // Loop through the array
    for (auto & row : grid) {
        for (auto & item : row) {
            // Generate humans first, then zombies
            if (numHumans < HUMAN_STARTCOUNT) {
                item = new Human();
                numHumans++;
            }
            else if (numZombies < ZOMBIE_STARTCOUNT) {
                item = new Zombie();
                numZombies++;
            }
            // The rest will be null pointers
            else {
                item = nullptr;
            }
        }
    }
    // Flatten the 2-dimensional array for shuffling.
    Organism *shuffleArray[GRID_WIDTH*GRID_HEIGHT];
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            shuffleArray[i * GRID_HEIGHT + j] = grid[i][j];
        }
    }
    // Create random seed (via system clock) and shuffle
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();//create random seed using system clock
    shuffle(&shuffleArray[0],&shuffleArray[GRID_WIDTH*GRID_HEIGHT-1],default_random_engine(seed));

    // Copy 1D array back into 2D array
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            grid[i][j] = shuffleArray[i * GRID_HEIGHT + j];
            // Update organisms with coordinates
            if (grid[i][j] != nullptr) {
                grid[i][j]->setCoords(j,i);
            }
        }
    }
}

City::~City() = default;

Organism *City::getOrganism(int x, int y) {
    return grid[y][x];
}

void City::setOrganism(Organism *organism, pair<int,int> coord) {
    // Deallocate the item before overwriting it with a different object
    if (organism != nullptr) {
        delete grid[coord.second][coord.first];
    }
    grid[coord.second][coord.first] = organism;
}

void City::moveOrganism(pair<int, int> location, pair<int, int> destination) {
    // Deallocate the item before overwriting it with a different object
    if (grid[destination.second][destination.first] != nullptr) {
        delete grid[destination.second][destination.first];
        grid[destination.second][destination.first] = nullptr;
    }
    // Move the two items and update coordinates
    swap(grid[destination.second][destination.first],grid[location.second][location.first]);
    grid[destination.second][destination.first]->setCoords(destination.first,destination.second);
}

void City::turn() {
    // Zombies get first priority
    for (auto & row : grid) {
        for (auto & index : row) {
            if (dynamic_cast<Zombie*>(index)) {
                index->turn(*this);
            }
        }
    }
    for (auto & row : grid) {
        for (auto & index : row) {
            if (dynamic_cast<Human*>(index)) {
                index->turn(*this);
            }
        }
    }
    // Loop again to set all moved bool to false
    for (auto & row : grid) {
        for (auto & index : row) {
            if (index != nullptr) {
                index->moved = false;
            }
        }
    }
}

ostream &operator<<(ostream &output, City &city) {
    // initialize containing output
    string outputString;
    // loop through array
    for (auto & y : city.grid) {
        outputString.append("\n");
        for (auto & x : y) {
            // Check what object type x points to
            if (auto* hmnPtr = dynamic_cast<Human*>(x)) {
                outputString.append(1,HUMAN_CH);
                outputString.append(1,' ');
            }
            if (auto* zmbPtr = dynamic_cast<Zombie*>(x)) {
                outputString.append(1,ZOMBIE_CH);
                outputString.append(1,' ');
            }
            if (x == nullptr) {
                outputString.append(1,SPACE_CH);
                outputString.append(1,' ');
            }
        }
    }
    // output the whole string
    output << outputString;
    return output;
}

