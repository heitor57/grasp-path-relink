#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "Item.h"
#include "BinaryKnapsack.h"
#include "Grasp.h"
#include "objective_function.h"
#include <ostream>

std::ostream& operator<<(std::ostream &stream, const Item &a) {
  return stream << "[u=" << a.utility << ",w="<<a.weight<<std::endl;
}

int main(int argc, char **argv){
  if(argc == 1){
    return 1;
  }
  std::ifstream in_file (argv[1]);
  std::string line;
  int num_items,capacity;
  in_file >> num_items >> capacity;
  BinaryKnapsack binary_knapsack = BinaryKnapsack(num_items,capacity);
  for(int i=0; i<num_items; i++){
    in_file >> binary_knapsack.items[i].utility >>binary_knapsack.items[i].weight;
  }
  for(long unsigned int i = 0;i<binary_knapsack.items.size() ;i++){
    binary_knapsack.items[i].id = i;
  }
  Grasp grasp(0.5,5);
  auto solution = grasp.run(binary_knapsack);
  objective_function(binary_knapsack,solution);
  return 0;
}
