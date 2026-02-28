#ifndef TRAVEL_HPP
#define TRAVEL_HPP

#include <cmath>

// costMatrix[i][j] = distance between city i and city j
inline vector<vector<double>> makeCostMatrix(const vector<City>& cities) {
    int n = cities.size();
    vector cost(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cost[i][j] = hypot(cities[j].lon - cities[i].lon, cities[j].lat - cities[i].lat);
        }
    }
    return cost;
}

// pheromoneMatrix[i][j] = pheromone level on edge i->j
inline vector<vector<double>> makePheromoneMatrix(int numberOfCities, double initialValue = 1.0) {
    return vector(numberOfCities, vector(numberOfCities, initialValue));
}

// Calculate total distance for each route and append it to the end of the route vector
inline void travelRoutes(vector<vector<int>>& population, const vector<vector<double>>& costMatrix) {
    for (auto& route : population) {
        double totalDistance = 0;
        for (int i = 0; i < route.size() - 1; i++) {
            totalDistance += costMatrix[route[i]][route[i + 1]];
        }
        route.push_back(static_cast<int>(totalDistance));
    }
}

inline void updatePheromones(vector<vector<double>>& pheromones,
                              const vector<vector<int>>& population,
                              int numberOfCities,
                              double rho = 0.5) {  // rho = evaporation rate (0-1)

    // (1 - rho) * tau_ij  — evaporation
    for (auto& row : pheromones) {
        for (auto& p : row) {
            p *= (1.0 - rho);
        }
    }

    // Sum of delta_tau_ij for each ant k
    for (const auto& route : population) {
        double distance = route.back();
        if (distance <= 0) continue;
        double deltaTau = 1.0 / distance;  // delta_tau^k_ij = 1/distance for edges used, 0 otherwise

        for (int i = 0; i < numberOfCities; i++) {
            int from = route[i];
            int to = route[i + 1];
            pheromones[from][to] += deltaTau;
            pheromones[to][from] += deltaTau;  // undirected
        }
    }
}

inline void buildRoutes(vector<vector<int>>& population,
                         const vector<vector<double>>& pheromones,
                         const vector<vector<double>>& costMatrix,
                         int numberOfCities,
                         double alpha,  // pheromone weight
                         double beta)   // distance weight
{
    mt19937 rng{random_device{}()};

    for (auto& route : population) {
        vector<bool> visited(numberOfCities, false);
        int current = route[0];
        visited[current] = true;

        while (route.size() < numberOfCities) {
            // Calculate probability for each unvisited city
            vector probs(numberOfCities, 0.0);
            double total = 0.0;
            for (int j = 0; j < numberOfCities; j++) {
                if (!visited[j] && costMatrix[current][j] > 0) {
                    probs[j] = pow(pheromones[current][j], alpha) *
                               pow(1.0 / costMatrix[current][j], beta);
                    total += probs[j];
                }
            }

            // Pick next city probabilistically
            uniform_real_distribution dist(0.0, total);
            double pick = dist(rng);
            double cumulative = 0.0;
            for (int j = 0; j < numberOfCities; j++) {
                if (!visited[j]) {
                    cumulative += probs[j];
                    if (cumulative >= pick) {
                        route.push_back(j);
                        visited[j] = true;
                        current = j;
                        break;
                    }
                }
            }
        }
        route.push_back(route[0]);  // close the loop
    }
}
#endif //TRAVEL_HPP
