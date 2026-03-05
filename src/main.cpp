#include "makePopulation.hpp"
#include "travelTCP.hpp"
#include "travelTAP.hpp"
#include <fstream>

int main() {
    bool solveTSP = false;  // true = TSP, false = TAP

    if (solveTSP) { // Traveling Salesman Problem
        int numberOfCities = 50;
        int populationSize = 10;
        int maxGenerations = 100;
        float alpha = 1;
        float beta = 5;
        float goal = 7115;

        int generation = 0;
        auto costMatrix = makeCostMatrix(cities);
        auto pheromones = makePheromoneMatrix(numberOfCities);
        vector<int> bestRoute;
        ofstream convergenceFile("convergence.txt");

        while (generation < maxGenerations) {
            vector<vector<int>> population = makePopulation(populationSize, numberOfCities);
            buildRoutes(population, pheromones, costMatrix, numberOfCities, alpha, beta);
            travelRoutes(population, costMatrix);
            updatePheromones(pheromones, population, numberOfCities);

            auto best = ranges::min_element(population, [](const vector<int>& a, const vector<int>& b) {
                return a.back() < b.back();
            });
            if (bestRoute.empty() || best->back() < bestRoute.back()) {
                bestRoute = *best;
            }
            convergenceFile << generation << " " << bestRoute.back() << endl;
            if (bestRoute.back() <= goal) break;
            if (generation % 10 == 0)
                cout << "Generation " << generation << ": Best distance = " << bestRoute.back() << endl;
            generation++;
        }
        convergenceFile.close();

        cout << "\nBest route found: ";
        for (int i = 0; i < bestRoute.size() - 1; i++)
            cout << bestRoute[i] << " ";
        cout << "\nTotal distance: " << bestRoute.back() << endl;

    } else { // Task Assignment Problem
        int n = 10;
        int populationSize = 10;
        int maxGenerations = 100;
        float alpha = 1;
        float beta = 1;

        auto costMatrix = makeAssignmentCostMatrix();
        auto pheromones = makePheromoneMatrix(n, 2.0);
        vector<int> bestAssignment;
        int generation = 0;
        ofstream convergenceFile("convergence_tap.txt");

        vector<double> scores;
        vector<double> bestScores;
        int bestIdx = -1;
        bool optimalFound = false;
        vector optimal = {1, 8, 2, 5, 9, 7, 3, 0, 6, 4};

        while (generation < maxGenerations) {
            vector population(populationSize, vector<int>());
            buildAssignments(population, pheromones, costMatrix, n, alpha, beta);
            scoreAssignments(population, costMatrix, scores);

            int minIdx = ranges::min_element(scores.begin(), scores.end()) - scores.begin();
            if (bestIdx == -1 || scores[minIdx] < bestScores[0]) {
                bestAssignment = population[minIdx];
                bestScores = {scores[minIdx]};
                bestIdx = minIdx;
            }

            updatePheromonesTAP(pheromones, population, scores, bestAssignment, bestScores[0], n);

            convergenceFile << generation << " " << bestScores[0] << endl;

            if (generation % 10 == 0)
                cout << "Generation " << generation << ": Best cost = " << bestScores[0] << endl;

            for (auto& assignment : population) {
                if (assignment == optimal) {
                    cout << "OPTIMAL FOUND in generation " << generation << endl;
                    optimalFound = true;
                    break;
                }
            }

            if (optimalFound) break;
            generation++;
        }
        convergenceFile.close();

        for (int taxi = 0; taxi < n; taxi++)
            cout << "Taxi " << taxis[taxi].name
                 << " -> Customer " << customers[bestAssignment[taxi]].name << "\n";
        cout << "Total distance: " << bestScores[0] << endl;
    }
    return 0;
}