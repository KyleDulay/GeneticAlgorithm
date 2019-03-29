//
// Created by KD on 3/21/2019.
//

#include <chrono>
#include <algorithm>
#include <random>
#include "Tour.hpp"

//Constructor for a Tour
//Requires list of cities and size of vector as arguments
Tour::Tour(std::vector<City>& c, int size) {
    //Define the tour size for the tour
    this->tourSize = size;
    //Assign copy of our city list to tour vector
    for(int i = 0; i < size; i++){

        //Create pointer to city
        City* city = &c.at(i);
        tour.push_back(city);
    }

    //Generate seed to randomly shuffle the tour
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    //Shuffle tour
    std::shuffle(std::begin(tour), std::end(tour), std::default_random_engine(seed));
    //Define the fitness of the new tour
    this->fitness = tourFitness();
}

//This constructor will construct a new tour based off the genetics
//of 2 parent tours
Tour::Tour(std::vector<Tour> p) {
    //Obtain a random number from hardware
    std::random_device rd;
    //Seed the generator
    std::mt19937 eng(rd());
    //Random number for mutation
    //Set the tour size, it will be the same as the tours in the existing population
    this->tourSize = p.at(0).tourSize;

    //Subsets for our chosen tours
    int subsetSize = 5;
    Tour subset1[subsetSize];
    Tour subset2[subsetSize];

    //The two elite parents need to be tracked
    Tour eliteOne;
    Tour eliteTwo;

    //Generate seed to randomly shuffle the tour
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    //Shuffle population
    std::shuffle(std::begin(p), std::end(p), std::default_random_engine(seed));
    //Select 5 parents for subset1
    for(int i = 0; i < subsetSize; i++){
        subset1[i] = p[i];
    }

    //Shuffle population
    std::shuffle(std::begin(p), std::end(p), std::default_random_engine(seed));
    //Select 5 parents
    for(int i = 0; i < subsetSize; i++){
        subset2[i] = p[i];
    }

    //Baseline for the fitness
    double fitBaseline= 100000;
    //Find elite parent
    for(int i = 0; i < subsetSize; i++){
        if(subset1[i].getFitness() < fitBaseline){
            fitBaseline = subset1[i].getFitness();
            eliteOne = subset1[i];
        }
    }

    //Baseline for the fitness
    fitBaseline = 100000;
    //find elite parent
    for(int i = 0; i < subsetSize; i++){
        if(subset2[i].getFitness() < fitBaseline){
            fitBaseline = subset2[i].getFitness();
            eliteTwo = subset2[i];
        }
    }

    //Set range which is inclusive
    std::uniform_int_distribution<> distr(0,eliteOne.getTourSize());
    int rand = distr(eng);

    //Populate with cities from eliteOne
    for(int i = 0; i < rand; i++){
        tour.push_back(eliteOne.tour.at(i));
    }

    //Populate with cities from eliteTwo
    for(int i = 0; i < eliteTwo.tour.size(); i++){
        if(std::find(std::begin(this->tour), std::end(this->tour), eliteTwo.tour[i]) == std::end(this->tour)){
            this->tour.push_back(eliteTwo.tour[i]);
        }
    }

    //Mutate if necessary
    //Distribution for mutation
    std::uniform_int_distribution<> distrMutation(0,100);
    //Distribution for swapping elements
    std::uniform_int_distribution<> distrSwap(0,eliteOne.getTourSize() - 1);
    for(int i = 0; i < tourSize; i++){
        int mutate = distrMutation(eng);
        //15 percent mutation rate
        if(mutate <= 15){
            int cityOne = distrSwap(eng);
            int cityTwo = distrSwap(eng);
            std::swap(tour.at(cityOne), tour.at(cityTwo));
        }
    }

    //Set fitness for the tour
    this->fitness = tourFitness();
}

//Return the size of the tour
int Tour::getTourSize() {
    return tourSize;
}

//tourFitness calculates the fitness of a tour
double Tour::tourFitness() {

    //Fitness is the combined distance between all points
    double fitness = 0.0;
    double power = 2.0;
    double x1;
    double x2;
    double y1;
    double y2;

    for (int i = 0; i < tourSize - 1; i++){

        x1 = tour.at(i)->getX();
        x2 = tour.at(i+1)->getX();
        y1 = tour.at(i)->getY();
        y2 = tour.at(i+1)->getY();
        //Calculate the distance between the 2 points
        fitness+=sqrt(pow((x2-x1),power) + pow((y2-y1),power));
    }

    //Add the distance from end point to start point
    //First get the coordinates of the first point again
    //We already have the coordinates of the second point
    x1 = tour.at(0)->getX();
    y1 = tour.at(0)->getY();
    fitness+=sqrt(pow((x2-x1),power) + pow((y2-y1),power));

    return fitness;
}

//Getter for the fitness
double Tour::getFitness() {

    return this->fitness;
}