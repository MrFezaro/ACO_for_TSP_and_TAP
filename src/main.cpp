#include "makePopulation.hpp"
#include "travel.hpp"

int main() {
    // Configuration
    int numberOfCities = 50;
    int populationSize = 100;
    int maxGenerations = 500;
    float alpha = 1; // Default 1
    float beta = 5; // Default 1
    float goal =  7130; // 7115 is the best known solution for 50 cities, but we can set a higher goal to allow for more exploration

    // Create population with random starting points
    vector<vector<int>> population = makePopulation(populationSize, numberOfCities);

    // Ant Colony Optimization Loop
    int generation = 0;
    auto costMatrix = makeCostMatrix(cities);
    auto pheromones = makePheromoneMatrix(numberOfCities);
    vector<int> bestRoute;

    while (generation < maxGenerations) {
        population = makePopulation(populationSize, numberOfCities);
        buildRoutes(population, pheromones, costMatrix, numberOfCities, alpha, beta);
        travelRoutes(population, costMatrix);
        updatePheromones(pheromones, population, numberOfCities);

        // Find best in this generation
        auto best = ranges::min_element(population, [](const vector<int>& a, const vector<int>& b) {
            return a.back() < b.back();
        });
        // Update global best
        if (bestRoute.empty() || best->back() < bestRoute.back()) {
            bestRoute = *best;
        }
        if (bestRoute.back() <= goal) {
            break;
        }
        if (generation % 10 == 0) {
            cout << "Generation " << generation << ": Best distance = " << bestRoute.back() << endl;
        }
        generation++;
    }

    // Print best route
    cout << "\nBest route found: ";
    for (int i = 0; i < bestRoute.size() - 1; i++) {
        cout << bestRoute[i] << " ";
    }
    cout << "\nTotal distance: " << bestRoute.back() << endl;
}

