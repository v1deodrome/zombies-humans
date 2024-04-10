//
// Created by jamzc on 2023-12-11.
//

#include "../headers/Organism.h"
#include "../headers/Human.h"
#include "../headers/Zombie.h"
#include <chrono>
#include <random>


Organism::Organism() {
    this->x = 0;
    this->y = 0;
    this->moved = false;
    this->breedPoints = 0;
}

Organism::Organism(int x, int y) {
    this->x = x;
    this->y = y;
    this->moved = false;
    this->breedPoints = 0;
}

Organism::~Organism() = default;

void Organism::setCoords(int inputX, int inputY) {
    this->x = inputX;
    this->y = inputY;
}

int Organism::getRandomSelection(int max) {
    // generate random seed using system clock
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    srand(seed);
    // generate from 0 - max
    return rand() % max;
}
