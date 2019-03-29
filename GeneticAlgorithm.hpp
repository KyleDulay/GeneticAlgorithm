//
// Created by KD on 3/22/2019.
//

#ifndef GENETICALGORITHM_GENETICALGORITHM_HPP
#define GENETICALGORITHM_GENETICALGORITHM_HPP

#include <vector>
#include "City.hpp"
#include "Tour.hpp"

class GeneticAlgorithm{

private:
    const int CITY_NAME_SIZE = 10;
    double minFitness = 100000; //We will use this as a baseline for the fittest tour
    double baseFitness;
    int NUMBER_PARENTS = 2;
    int CITIES_IN_TOUR;
    int POPULATION_SIZE;
    std::vector<City> cityList; //City master list
    std::vector<Tour> population; //List of tours


public:
    GeneticAlgorithm(int numCities, int sizePopulation);
    void makeCityList();
    void generateName(char *s);
    void crossover();
    int randInt();


};
#endif //GENETICALGORITHM_GENETICALGORITHM_HPP
