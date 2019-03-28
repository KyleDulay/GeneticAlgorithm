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

    //Print out the baseline fitness
    std::cout<<"BASELINE FITNESS LEVEL: "<<population.at(0).getFitness()<<std::endl;

    //Now that we have our master city list and initial population,
    //we can run the findElite() function to iteratively improve our
    //population in order to find the fittest tour
    findElite();
}

//findElite will implement the genetic algorithm to find the fittest tour
void GeneticAlgorithm::findElite() {

    std::vector<Tour> crosses;
    int iter = 0;

    while (iter < 1000){

        crosses.clear();
        std::cout<<"POP SIZE: " << population.size() << std::endl;
        for(int i = 1; i < population.size(); i++){
            crosses.push_back(crossover());
        }

        for(int i = 1; i < crosses.size(); i++){
            if(crosses.at(i).getFitness() < population.at(0).getFitness()){
                population.insert(population.begin(), crosses.at(i));
            } else {
                population[i] = crosses[i];
            }
        }

        std::cout << "Elite: " << population[0].getFitness() << std::endl;
        iter++;
    }

}

Tour GeneticAlgorithm::crossover() {

    int subsetSize = 5;
    double min = 100000;
    Tour eliteOne;
    Tour eliteTwo;
    std::vector<Tour> populationCopy = population;
    std::vector<Tour> subset;

    //Get 2 parents
    for(int i = 0; i < NUMBER_PARENTS; i++){
        //Create variable for parent of current subset
        Tour elite;
        //Generate seed to randomly shuffle the tour
        long seed = std::chrono::system_clock::now().time_since_epoch().count();
        //Shuffle tour
        std::shuffle(std::begin(populationCopy), std::end(populationCopy), std::default_random_engine(seed));

        //Randomly select 5 tours after shuffling
        for(int j = 0; j < subsetSize; j++){
            //Add first element to subset
            subset.push_back(populationCopy.at(j));
        }

        //Find the most elite of the 5 tours
        for(int k = 0; k < subset.size(); k++){
            if (subset.at(k).getFitness() < min){
                elite = subset.at(k);
                min = elite.getFitness();
            }
        }

        //Define the elite parents
        if(i == 0){
            eliteOne = elite;
        } else {
            eliteTwo = elite;
        }

        subset.clear();
        min = 100000;
    }

    std::cout<<"Elite One: " << eliteOne.getFitness() << std::endl;
    std::cout<<"Elite Two: " << eliteTwo.getFitness() << std::endl;
    return Tour(eliteOne, eliteTwo, CITIES_IN_TOUR);
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
        cityList.push_back(City(str, randX, randY));
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