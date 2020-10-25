#include "Grasp.h"

#include <iostream>
#include <random>
#include <cfloat>
#include <list>
#include "objective_function.h"
#include "VND.h"

Grasp::Grasp(float alpha_, int iter_max_):
  alpha(alpha_), iter_max(iter_max_) {}

void Grasp::construction(const BinaryKnapsack& binary_knapsack,
                                      std::vector<bool>& solution){
  std::list<Item> sorted_items(binary_knapsack.items.begin(), binary_knapsack.items.end());
  sorted_items.sort([](const Item &a,const Item& b) {
              return a.utility < b.utility;
  });
  int total_weight = 0;
  int threshold;
  long unsigned int i;
  std::default_random_engine generator;
  while(sorted_items.size()>0 && total_weight < binary_knapsack.capacity){
    // compute the threshold
    threshold = sorted_items.front().utility-
      alpha*(sorted_items.front().utility - sorted_items.back().utility);
    // compute the limit of the list to sort
    std::list<Item>::iterator item_iterator = sorted_items.begin();
    for(i = 0; i < sorted_items.size() && item_iterator->utility >= threshold; i++){
      ++item_iterator;
    }
    // sort one index in the range of items
    int j = std::uniform_int_distribution<int>(0,(int)i)(generator);
    // Test if can put the item in the knapsack
    item_iterator=std::next(sorted_items.begin(),j);
    if(solution[item_iterator->id] != 1 && item_iterator->weight <= total_weight){
      solution[item_iterator->id]=1;
      total_weight+= item_iterator->weight;
    }
    // remove the item of the candidate items list
    sorted_items.erase(item_iterator);
  }
}


std::vector<bool> Grasp::run(BinaryKnapsack binary_knapsack)
{
  double fo_star = -DBL_MAX;
        
  std::vector<bool> solution(binary_knapsack.items.size(),false);
  std::vector<bool> aux_solution(binary_knapsack.items.size(),false);

  for (int i = 0; i<iter_max; i++) {
    // Limpa solucao
    for (long unsigned int j=0; j<binary_knapsack.items.size(); j++) aux_solution[j] = false;
    // Constroi solucao parcialmente gulosa
    construction(binary_knapsack,aux_solution);
    // constroi_solucao_grasp(n,aux_solution,p,w,b,alfa);
    printf("solucao construida: %lf\t", objective_function(binary_knapsack,aux_solution));
    // Aplica busca local na solucao construida
    VND(binary_knapsack,aux_solution);
    printf("solucao refinada: %lf\n", objective_function(binary_knapsack,aux_solution));
    // Atualiza melhor solucao
    if (objective_function(binary_knapsack,aux_solution) > fo_star) {
                        
      // copia em s a melhor solucao
      for (long unsigned int i = 0; i < binary_knapsack.items.size(); i++)
        solution[i] = aux_solution[i];
      fo_star = objective_function(binary_knapsack,aux_solution);
    }
  }
  return solution;
}
