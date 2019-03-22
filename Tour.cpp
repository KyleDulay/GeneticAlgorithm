//
// Created by KD on 3/21/2019.
//

#include <chrono>
#include <algorithm>
#include <random>
#include "Tour.hpp"

Tour::Tour(std::vector<City> c, int size) {
    //Define the tour size for the tour
    this->tourSize = size;
    //Generate seed to randomly shuffle the city list
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    //Shuffle city list
    std::shuffle(std::begin(c), std::end(c), std::default_random_engine(seed));
    //Populate tour
    for(int j = 0; j < tourSize; j++){
        tour.push_back(c.at(j));
    }

    //Define the fitness of the new tour
    this->fitness = tourFitness();
}

double Tour::tourFitness() {

    //Fitness is the combined distance between all points
    double fitness = 0.0;
    double power = 2.0;
    double x1;
    double x2;
    double y1;
    double y2;

    for (int i = 0; i < tourSize - 1; i++){

        x1 = tour.at(i).getX();
        x2 = tour.at(i+1).getX();
        y1 = tour.at(i).getY();
        y2 = tour.at(i+1).getY();

        //Calculate the distance between the 2 points
        fitness+=sqrt(pow((x2-x1),power) + pow((y2-y1),power));
    }

    //Add the distance from end point to start point
    //First get the coordinates of the first point again
    //We already have the coordinates of the second point
    x1 = tour.at(0).getX();
    y1 = tour.at(0).getY();
    fitness+=sqrt(pow((x2-x1),power) + pow((y2-y1),power));

    return fitness;
}