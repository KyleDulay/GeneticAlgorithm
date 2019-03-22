#include <iostream>
#include <map>
#include <random>
#include <algorithm>
#include <chrono>
#include <cmath>
#include "City.hpp"

//Random generate string names
void randString(char *s, const int len) {
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

//Random number generator
int randInt(){
    //Obtain a random number from hardware
    std::random_device rd;
    //Seed the generator
    std::mt19937 eng(rd());
    //Set range which is inclusive
    std::uniform_int_distribution<> distr(0,1000);
    //Return a random number
    return distr(eng);
}

int main() {
    //Initialize constants
    int CITIES_IN_TOUR = 32;
    int POPULATION_SIZE = 32;
    int NAME_SIZE = 10;

    //City list
    std::vector<City> cityList;

    //Generate a list of cities
    char str[NAME_SIZE];
    int randX, randY;
    for(int i = 0; i < CITIES_IN_TOUR; i++){
        randX = randInt();
        randY = randInt();
        randString(str, NAME_SIZE);
        cityList.push_back(City(str, randX, randY));
    }

}