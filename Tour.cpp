//
// Created by KD on 3/21/2019.
//

#include <chrono>
#include <algorithm>
#include <random>
#include "Tour.hpp"

//Constructor for a Tour
//Requires list of cities and size of vector as arguments
Tour::Tour(std::vector<City> c, int size) {
    //Assign copy of our city list to tour vector
    for(int i = 0; i < size; i++){

        //Create pointer to city
        City * city = &c.at(i);
        tour.push_back(city);
    }
    //Define the tour size for the tour
    this->tourSize = size;
    //Generate seed to randomly shuffle the tour
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    //Shuffle tour
    std::shuffle(std::begin(tour), std::end(tour), std::default_random_engine(seed));
    //Define the fitness of the new tour
    this->fitness = tourFitness();
}

//This constructor will construct a new tour based off the genetics
//of 2 parent tours
Tour::Tour(Tour a, Tour b, int size) {

    std::cout<<"A: " << a.tour.size() <<std::endl;
    std::cout<<"B: " << b.tour.size() <<std::endl;
    //Set the size of the tour
    this->tourSize = size;

    //Random integer
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0,a.getTourSize());
    int rand = distr(eng);

    //Get cities from first parent
    for(int i = 0; i < rand; i++){
        tour.push_back(a.tour.at(i));
    }
    //Get cities from second parent
    for(int i = 0; i < b.getTourSize(); i++){
        //If tour is empty or doesn't contain the city, add it
        if(tour.empty() || std::find(tour.begin(), tour.end(), b.tour.at(i)) == tour.end()){
            tour.push_back(b.tour.at(i));
        }
    }

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