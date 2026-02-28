#ifndef MAKEPOPULATION_HPP
#define MAKEPOPULATION_HPP

#include <vector>
#include <string>
#include <numeric>
#include <random>
#include <iostream>
#include <algorithm>
using namespace std;

struct City {
    string name;
    int lat, lon;
};

inline vector<vector<int>> makePopulation(int populationSize, int numberOfCities) {
    if (numberOfCities > 50) {
        cerr << "The number of Cities must be 50 or less" << endl;
        return {};
    }

    mt19937 rng{random_device{}()};
    uniform_int_distribution<int> dist(0, numberOfCities - 1);

    vector<vector<int>> population;
    for (int i = 0; i < populationSize; i++) {
        int startCity = dist(rng);
        population.push_back({startCity});
    }

    return population;
}

inline vector<City> cities = {
    {"Oslo",          5991, 1075},  // ~700,000
    {"Bergen",        6039,  527},  // ~285,000
    {"Trondheim",     6339, 1040},  // ~205,000
    {"Stavanger",     5846,  643},  // ~145,000
    {"Bærum",         5995, 1054},  // ~127,000
    {"Kristiansand",  5872,  944},  // ~112,000
    {"Fredrikstad",   5921, 1108},  // ~83,000
    {"Tromsø",        6984, 1874},  // ~78,000
    {"Drammen",       5973, 1004},  // ~72,000
    {"Sandnes",       5886,  659},  // ~65,000
    {"Sarpsborg",     5921, 1100},  // ~60,000
    {"Bodø",          6829, 1512},  // ~52,000
    {"Sandefjord",    5921, 1073},  // ~48,000
    {"Ålesund",       6286,  952},  // ~47,000
    {"Tønsberg",      5919, 1073},  // ~46,000
    {"Skien",         5903, 1059},  // ~45,000
    {"Moss",          5927, 1075},  // ~33,000
    {"Haugesund",     5985,  612},  // ~37,000
    {"Arendal",       5878,  964},  // ~35,000
    {"Hamar",         6069, 1108},  // ~32,000
    {"Larvik",        5904, 1009},  // ~25,000
    {"Halden",        5912, 1148},  // ~25,000
    {"Lillehammer",   6061, 1131},  // ~24,000
    {"Molde",         6260,  743},  // ~20,000
    {"Horten",        5941, 1032},  // ~19,000
    {"Harstad",       6861, 1662},  // ~18,000
    {"Gjøvik",        6073, 1038},  // ~18,000
    {"Kristiansund",  6310,  798},  // ~17,000
    {"Narvik",        6842, 1748},  // ~14,000
    {"Steinkjer",     6421, 1108},  // ~13,000
    {"Levanger",      6358, 1113},  // ~12,000
    {"Porsgrunn",     5988,  959},  // ~12,000
    {"Alta",          6997, 2330},  // ~11,000
    {"Mo i Rana",     6632, 1422},  // ~11,000
    {"Elverum",       6087, 1130},  // ~10,500
    {"Namsos",        6445, 1156},  // ~10,000
    {"Kongsvinger",   6020, 1201},  // ~10,000
    {"Mosjøen",       6583, 1317},  // ~9,500
    {"Verdal",        6339, 1125},  // ~9,000
    {"Røros",         6257, 1163},  // ~5,500
    {"Svolvær",       6825, 1483},  // ~4,500
    {"Grimstad",      5827,  826},  // ~12,000
    {"Florø",         6160,  495},  // ~8,000
    {"Førde",         6188,  572},  // ~6,500
    {"Sogndal",       6124,  764},  // ~4,500
    {"Sunndalsøra",   6222,  864},  // ~3,500
    {"Hammerfest",    7040, 2363},  // ~7,000
    {"Vardø",         7037, 3105},  // ~2,000
    {"Kirkenes",      6942, 3005},  // ~3,500
    {"Vadsø",         7006, 2940},  // ~5,000
};


#endif //MAKEPOPULATION_HPP
