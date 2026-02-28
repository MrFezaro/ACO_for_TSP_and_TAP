# Ant Colony Optimization for Travelling Salesman Problem (Norway)

A C++ implementation of the Ant Colony Optimization (ACO) algorithm to solve the Travelling Salesman Problem (TSP) across 50 Norwegian cities, with a Python visualization script.

---

## Overview

This project uses ACO to find the shortest possible route visiting all 50 Norwegian cities exactly once and returning to the starting point. Ants build routes probabilistically based on pheromone trails and distances, with shorter routes reinforcing their pheromone trails over generations.

---

## How It Works

Each generation:
1. A fresh population of ants is placed at random starting cities
2. Each ant builds a complete route using pheromone levels and edge distances
3. Route distances are calculated using a precomputed cost matrix
4. Pheromone trails are updated where shorter routes deposit more pheromone
5. The best route found so far is tracked across all generations

The pheromone update follows the standard ACO formula:

$$\tau_{ij} = (1 - \rho)\tau_{ij} + \sum_{k=1}^{m} \Delta\tau_{ij}^k$$

Where $\rho$ is the evaporation rate and $\Delta\tau_{ij}^k = 1/L_k$ for edges used by ant $k$.

---

## Configuration

In `main.cpp`:

```cpp
int numberOfCities = 50;    // up to 50
int populationSize = 100;    // ants per generation
int maxGenerations = 500;
float alpha = 1;            // pheromone weight
float beta  = 5;            // distance weight (higher = more greedy)
```

**Tuning tips:**
- `beta` should generally be higher than `alpha` (e.g. `alpha=1, beta=3-5`)
- Higher `beta` = greedier, converges faster
- Higher `alpha` = follows pheromones more strongly, can get stuck
- Higher `rho` = pheromones evaporate faster, more exploration. Can be adjusted in travel.hpp

---

## Project Structure

```
├── main.cpp               # Entry point and ACO loop
├── makePopulation.hpp     # City data, population initialization, route building
├── travel.hpp             # Checks route distances and updates pheromone matrix
└── draw_route.py          # Python visualization script
```

---

## Requirements

**C++**
- C++26 or later
- Standard library only (no external dependencies)

**Python** (for visualization)
```
pip install matplotlib
```

---

## Visualization

Run the Python script and paste your route when prompted:

```bash
python testRoute.py
Enter route: 0 4 8 12 16 ...
```

The route is drawn on a coordinate map of Norway with directional arrows colored from start to finish.

---

## Cities

The dataset contains 50 of the largest Norwegian cities with approximate lat/lon coordinates.

---

## Example Output

```
Generation 0: Best distance = 14823
Generation 100: Best distance = 11240
Generation 500: Best distance = 9871
...
Best route found: 0 4 16 10 6 21 12 14 15 ...
Total distance: 8943
```
![Route visualization](aco_tsp.png)
