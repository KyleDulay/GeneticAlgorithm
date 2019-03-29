#include "GeneticAlgorithm.hpp"
#include <chrono>

using namespace std::chrono;

int main() {

    auto start = high_resolution_clock::now();
    GeneticAlgorithm(32,32);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    std::cout<<"Duration: " << duration.count() << " ms" << std::endl;
}