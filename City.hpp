//
// Created by KD on 3/8/2019.
//

#ifndef GENETICALGORITHM_CITY_HPP
#define GENETICALGORITHM_CITY_HPP
#include <string>
#include <iostream>

class City{

private:

    std::string name; //City name
    const static int MAP_BOUNDARY = 1000; //Maximum for x and y coordinates
    int x; //City x coordinate
    int y; //City y coordinate

public:
    City();
    City(std::string name, int x, int y);
    int getX() const;
    int getY() const;

};
#endif //GENETICALGORITHM_CITY_HPP
