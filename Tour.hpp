//
// Created by KD on 3/21/2019.
//

#ifndef GENETICALGORITHM_TOUR_HPP
#define GENETICALGORITHM_TOUR_HPP

#include <vector>
#include "City.hpp"

class Tour{
private:
    int tourSize;
    double fitness;

public:
    std::vector<City*> tour;
    Tour(){};
    Tour(std::vector<City> c, int size);
    Tour(Tour a, Tour b, int size);
    int getTourSize();
    double tourFitness();
    double getFitness();

};
#endif //GENETICALGORITHM_TOUR_HPP
