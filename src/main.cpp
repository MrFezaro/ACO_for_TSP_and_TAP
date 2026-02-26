#include "makePopulation.hpp"
#include <iostream>

int main() {
    // Configuration
    int numberOfCities = 3;
    int populationSize = 12;
    int maxGenerations = 100;
    float alpha = 1;
    float beta = 1;
    float goal = 1;

    // Create population
    vector<vector<int>> population = makePopulation(populationSize, numberOfCities);

    for (int i = 0; i < population.size(); i++) {
        cout << "Route " << i + 1<< ": ";
        for (int j = 0; j < population[i].size(); j++) {
            cout << cities[population[i][j]].name << " ";
        }
        cout << endl;
    }

    return 0;
}