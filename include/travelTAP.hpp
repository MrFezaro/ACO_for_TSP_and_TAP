#ifndef TRAVELTAP_HPP
#define TRAVELTAP_HPP

#include <string>
#include <numeric>
#include <vector>
#include <random>
using namespace std;

struct Location {
    string name;
    double x, y;
};

inline vector<Location> taxis = {
    {"Aalesund Station",         62.4722, 6.1495},
    {"Brosundet Quay",          62.4706, 6.1512},
    {"Aalesund Hospital",        62.4780, 6.1620},
    {"Moa Shopping Centre",     62.4782, 6.2301},
    {"Borgundvegen Stand",      62.4745, 6.1890},
    {"Aspoy Ferry Terminal",    62.4658, 6.1423},
    {"Hessa Beach",             62.4601, 6.0987},
    {"Nurvasund Bridge",        62.4831, 6.1723},
    {"Aalesund Airport Vigra",   62.5600, 6.1197},
    {"Skarbovik Harbour",       62.4689, 6.1834},
};

inline vector<Location> customers = {
    {"Hotel Brosundet",         62.4710, 6.1530},
    {"Jugendstilsenteret",      62.4718, 6.1487},
    {"Aksla Viewpoint",         62.4739, 6.1552},
    {"Atlantic Sea Park",       62.4648, 6.0921},
    {"Aalesund University",      62.4716, 6.2028},
    {"Storfjord Hotel",         62.4923, 6.9823},
    {"Molovegen Pier",          62.4695, 6.1468},
    {"Buholmen Island",         62.4672, 6.1389},
    {"Storgata Shopping",       62.4727, 6.1512},
    {"Roysa Residential",       62.4850, 6.1901},
};

inline vector<vector<double>> makeAssignmentCostMatrix() {
    int n = taxis.size();

    vector cost(n, vector(n, 0.0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cost[i][j] = hypot(customers[j].x - taxis[i].x,
                               customers[j].y - taxis[i].y);
        }
    }
    return cost;
}

inline void scoreAssignments(vector<vector<int>>& population,
                              const vector<vector<double>>& costMatrix,
                              vector<double>& scores) {
    scores.resize(population.size());
    for (int i = 0; i < population.size(); i++) {
        double totalCost = 0;
        for (int taxi = 0; taxi < population[i].size(); taxi++) {
            int customer = population[i][taxi];
            totalCost += costMatrix[taxi][customer];
        }
        scores[i] = totalCost;
    }
}

inline void buildAssignments(vector<vector<int>>& population,
                              const vector<vector<double>>& pheromones,
                              const vector<vector<double>>& costMatrix,
                              int n, float alpha, float beta) {
    static mt19937 rng{random_device{}()};

    for (auto& assignment : population) {
        assignment.assign(n, -1);
        vector customerTaken(n, false);

        // Randomize taxi order each time
        vector<int> taxiOrder(n);
        iota(taxiOrder.begin(), taxiOrder.end(), 0);
        ranges::shuffle(taxiOrder, rng);

        for (int taxi : taxiOrder) {
            vector probs(n, 0.0);
            double total = 0.0;
            for (int c = 0; c < n; c++) {
                if (!customerTaken[c] && costMatrix[taxi][c] > 0) {
                    probs[c] = pow(pheromones[taxi][c], alpha) *
                               pow(1.0 / costMatrix[taxi][c], beta);
                    total += probs[c];
                }
            }

            uniform_real_distribution dist(0.0, total);
            double pick = dist(rng);
            double cumulative = 0.0;
            for (int c = 0; c < n; c++) {
                if (!customerTaken[c]) {
                    cumulative += probs[c];
                    if (cumulative >= pick) {
                        assignment[taxi] = c;
                        customerTaken[c] = true;
                        break;
                    }
                }
            }
        }
    }
}

inline void updatePheromonesTAP(vector<vector<double>>& pheromones,
                                 const vector<vector<int>>& population,
                                 const vector<double>& scores,
                                 const vector<int>& bestAssignment,
                                 double bestScore,
                                 int n,
                                 double rho = 0.5) {
    // Evaporate
    for (auto& row : pheromones) {
        for (auto& p : row) {
            p *= (1.0 - rho);
        }
    }
    // Regular deposit
    for (int k = 0; k < population.size(); k++) {
        if (scores[k] <= 0) continue;
        double deltaTau = 1.0 / scores[k];
        for (int taxi = 0; taxi < n; taxi++) {
            pheromones[taxi][population[k][taxi]] += deltaTau;
        }
    }

    // Elite deposit - best known solution gets extra reinforcement
    if (!bestAssignment.empty()) {
        double eliteTau = 1.0 / bestScore;  // 5x bonus
        for (int taxi = 0; taxi < n; taxi++) {
            pheromones[taxi][bestAssignment[taxi]] += eliteTau;
        }
    }
}

#endif //TRAVELTAP_HPP
