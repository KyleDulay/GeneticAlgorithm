//
// Created by KD on 3/22/2019.
//

#include <random>
#include <iterator>
#include <chrono>
#include <algorithm>
#include "GeneticAlgorithm.hpp"

GeneticAlgorithm::GeneticAlgorithm(int numCities, int sizePopulation) {

    //Define number of cities in tour
    this->CITIES_IN_TOUR = numCities;
    //Define number of tours in population
    this->POPULATION_SIZE = sizePopulation;
    //Generate the initial city master list
    makeCityList();

    //This is where we create our first population of tours
    for(int i = 0; i < POPULATION_SIZE; i++){
        Tour mTour = Tour(cityList, CITIES_IN_TOUR);
        //Check if current tour is the elite tour
        if (mTour.getFitness() < minFitness){
            //Set the minimum fitness
            minFitness = mTour.getFitness();
            //Insert at the front of the population
            population.insert(population.begin(), mTour);
        } else { //If this is not the elite tour, push to back
            population.push_back(mTour);
        }
    }

    //Keep track of our baseline fitness
    baseFitness = population.at(0).getFitness();

    //Now that we have our master city list and initial population,
    //we can run the findElite() function to iteratively improve our
    //population in order to find the fittest tour
    crossover();
}

//Crossover function
//Create array of tours that is size population - 1
//Replace everything but the first index in our current population
//Find elite
//Repeat
void GeneticAlgorithm::crossover() {

    //The number of crossed tours we need
    int numCrosses = POPULATION_SIZE - 1;

    int count = 0;

    while(count < 1000){

        //Create array for our crossed tours
        Tour crosses[numCrosses];

        //Generate crossed tours, there is a constructor in Tour class
        //which takes a population of tours as an argument and generates
        //a new tour based off the genetics of the population
        for(int i = 0; i < numCrosses; i++){
            Tour t = Tour(population);
            crosses[i] = t;
        }


        for(int i = 1; i < numCrosses + 1; i++){
            population.at(i) = crosses[i-1];
            if(crosses[i-1].getFitness() < population.at(0).getFitness()){
                double improvement = ((population.at(0).getFitness() - crosses[i-1].getFitness()) / population.at(0).getFitness()) * 100;
                std::swap(population.at(0), population.at(i));
                std::cout<< "New Elite Tour: " << population.at(0).getFitness() << "\tImprovement: " << improvement << "%" << std::endl;
            }
        }

        count++;

    }

    std::cout << "\n----------REPORT: Results after 1000 iterations---------" << std::endl;
    std::cout<< "First Elite Tour: " << baseFitness << std::endl;
    std::cout << "Current Elite Tour: " << population.at(0).getFitness() << std::endl;
    double improvement = ((baseFitness - population.at(0).getFitness()) / baseFitness) * 100;
    std::cout << "Overall Improvement: " << improvement << "%" << std::endl;
}

//makeCityList function will generate the initial master list
//of cities
void GeneticAlgorithm::makeCityList() {

    //Generate a list of cities
    char str[CITY_NAME_SIZE];
    int randX, randY;
    for(int i = 0; i < CITIES_IN_TOUR; i++){
        randX = randInt();
        randY = randInt();
        generateName(str);
        cityList.emplace_back(City(str, randX, randY));
    }
}

//generateName function will generate a random name for a city
//consisting of strings and numbers
void GeneticAlgorithm::generateName(char *s) {

    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < CITY_NAME_SIZE; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[CITY_NAME_SIZE] = 0;

}

//randInt will return a random integer within the range of
//0-1000, this is used for generating the x and y coordinates
//of each city
int GeneticAlgorithm::randInt() {

    //Obtain a random number from hardware
    std::random_device rd;
    //Seed the generator
    std::mt19937 eng(rd());
    //Set range which is inclusive
    std::uniform_int_distribution<> distr(0,1000);
    //Return a random number
    return distr(eng);
}