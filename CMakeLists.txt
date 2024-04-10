cmake_minimum_required(VERSION 3.26)
project(Assignment_4)

set(CMAKE_CXX_STANDARD 17)

add_executable(Assignment_4 src/main.cpp
        headers/GameSpecs.h
        headers/City.h
        headers/Organism.h
        headers/Zombie.h
        src/City.cpp
        src/Human.cpp
        src/Organism.cpp
        src/Zombie.cpp
)
