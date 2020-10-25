#include "objective_function.h"
#include <iostream>

long objective_function(BinaryKnapsack& binary_knapsack, std::vector<bool>& solution){
  long weight=0,utility=0,penalty=0;
  for (long unsigned int i = 0; i < binary_knapsack.items.size(); i++) {
    if (solution[i]) {
      utility += binary_knapsack.items[i].utility;
      weight += binary_knapsack.items[i].weight;
    }
    penalty += binary_knapsack.items[i].weight;
  }
  // std::cout<< utility<< " "<< penalty<< " " << weight<< " "<< binary_knapsack.capacity<< " " <<"\n";

  return utility - penalty * std::max((long)0, weight - binary_knapsack.capacity);
}
