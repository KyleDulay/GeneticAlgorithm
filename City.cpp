//
// Created by KD on 3/8/2019.
//

#include "City.hpp"

City::City() {
    this->name = "";
    this->x = 0;
    this->y = 0;
}

City::City(std::string name, int x, int y) {
    //Check if x and y are within range
    if(x >= 0 && x <= MAP_BOUNDARY && y >= 0 && y <= MAP_BOUNDARY){
        this->name = name;
        this->x = x;
        this->y = y;
    } else {
        std::cerr << "Coordinates are not in range" << std::endl;
    }
}

//Getter for x coordinate
int City::getX() const {return this->x;}

//Getter for Y coordinate
int City::getY() const {return this->y;}

//Getter for city name
std::string City::getName() {return this->name;}