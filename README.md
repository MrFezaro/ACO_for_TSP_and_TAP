# 🐜 Ant Colony Optimization — Travelling Salesman Problem (Norway)

A C++ implementation of the Ant Colony Optimization (ACO) algorithm to solve the Travelling Salesman Problem (TSP) across 50 Norwegian cities, with a Python visualization script.

---

## Overview

This project uses ACO to find the shortest possible route visiting all 50 Norwegian cities exactly once and returning to the starting point. Ants build routes probabilistically based on pheromone trails and edge distances, with shorter routes reinforcing their pheromone trails over generations.

---

## How It Works

Each generation:
1. A fresh population of ants is placed at random starting cities
2. Each ant builds a complete route using pheromone levels and edge distances
3. Route distances are calculated using a precomputed cost matrix
4. Pheromone trails are updated — shorter routes deposit more pheromone
5. The best route found so far is tracked across all generations

The pheromone update follows the standard ACO formula:

$$\tau_{ij} = (1 - \rho)\tau_{ij} + \sum_{k=1}^{m} \Delta\tau_{ij}^k$$

Where $\rho$ is the evaporation rate and $\Delta\tau_{ij}^k = 1/L_k$ for edges used by ant $k$.

---

## Configuration

In `main.cpp`:

```cpp
int numberOfCities = 50;    // up to 50
int populationSize = 10;    // ants per generation
int maxGenerations = 10000;
float alpha = 1;            // pheromone weight
float beta  = 3;            // distance weight (higher = more greedy)
float rho   = 0.5;          // evaporation rate (0-1)
```

**Tuning tips:**
- `beta` should generally be higher than `alpha` (e.g. `alpha=1, beta=3-5`)
- Higher `beta` = greedier, converges faster
- Higher `alpha` = follows pheromones more strongly, can get stuck
- Higher `rho` = pheromones evaporate faster, more exploration

---

## Project Structure

```
├── main.cpp               # Entry point and ACO loop
├── makePopulation.hpp     # City data, population initialization, route building
├── travel.hpp             # Distance calculation using cost matrix
├── sortPopulation.hpp     # Sorting population by route distance
└── draw_route.py          # Python visualization script
```

---

## Requirements

**C++**
- C++20 or later
- Standard library only (no external dependencies)

**Python** (for visualization)
```
pip install matplotlib
```

---

## Building

```bash
g++ -std=c++20 -O2 -o aco main.cpp
./aco
```

---

## Visualization

Run the Python script and paste your route when prompted:

```bash
python draw_route.py
Enter route: 0 4 8 12 16 ...
```

The route is drawn on a coordinate map of Norway with directional arrows colored from start to finish.

---

## Cities

The dataset contains 50 Norwegian cities with approximate lat/lon coordinates, including Oslo, Bergen, Trondheim, Tromsø, and Kirkenes — spanning from Kristiansand in the south to Vardø in the far northeast.

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
