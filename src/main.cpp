#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "Item.h"
#include "BinaryKnapsack.h"
#include "Grasp.h"
#include "objective_function.h"
#include <ostream>
#include <ctime>

int main(int argc, char **argv){
  std::string data_dir = "../data/";
  std::string results_dir =  data_dir+"results/";

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
    binary_knapsack.items[i].id = i;
    binary_knapsack.items[i].profit = binary_knapsack.items[i].utility/binary_knapsack.items[i].weight;
  }
  Grasp grasp(0.7,50,10,true);

  clock_t begin = clock();
  auto solution = grasp.run(binary_knapsack);
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

  std::cout << "Best solution: "
            << objective_function(binary_knapsack,solution)
            << std::endl;
  std::cout << "Elapsed time: " << elapsed_secs << " seconds\n";
  std::string output_file_name = std::to_string(binary_knapsack.items.size())
    +"-"+ std::to_string(binary_knapsack.capacity)
    +"-"+ std::to_string(grasp.alpha)
    +"-"+ std::to_string(grasp.iter_max)
    +"-"+ std::to_string(grasp.num_elite)
    +"-"+ std::to_string(grasp.use_path_relinking)
    + ".txt";
  return 0;
}
