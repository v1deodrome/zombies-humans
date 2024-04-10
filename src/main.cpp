#include <iostream>
#include <thread>
#include "../headers/City.h"

void ctimeClockExample();

int main() {
    City *city = new City();
    string newline(GRID_HEIGHT - 1, '\n');

    // Timer functionality provided by David Russell
    // https://nscconline.brightspace.com/d2l/le/content/279262/viewContent/4023730/View
    int iteration = 0;
    double counter = 0;
    double pauseInterval = ITERATION_TIME;
    clock_t startTime = clock();
    clock_t previousTime = startTime;

    // While iterations is running
    while (iteration < ITERATIONS) {
        startTime = clock();
        counter += startTime - previousTime;
        previousTime = startTime;
        if (counter > pauseInterval * CLOCKS_PER_SEC) {
            counter -= pauseInterval * CLOCKS_PER_SEC;
            // Make turn and print city
            cout << newline << *city << endl;
            cout << "ITERATION #" + to_string(iteration+1) + "\nHUMANS - " + to_string(city->numHumans) + " | ZOMBIES - " + to_string(city->numZombies) << endl;
            iteration++;
            // Break from loop if the game ends prematurely
            if (city->numHumans == 0) {
                cout << "GAME OVER - ZOMBIES WIN";
                break;
            }
            if (city->numZombies == 0) {
                cout << "GAME OVER - HUMANS WIN";
                break;
            }
            // Continue if game hasn't ended
            else {
                city->turn();
            }
        }
    }
}