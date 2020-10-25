#ifndef VND_H
#define VND_H
#include <vector> 
#include "BinaryKnapsack.h"
#include "objective_function.h"
#include <cfloat>
#include <cstdio>

void best_neighbor_1(BinaryKnapsack& binary_knapsack, std::vector<bool>& solution);
void best_neighbor_2(BinaryKnapsack& binary_knapsack, std::vector<bool>& solution);
void VND(BinaryKnapsack& binary_knapsack,std::vector<bool>& solution);

#endif
