#include "Grasp.h"

#include <iostream>
#include <random>
#include <climits>
#include <list>
#include <string>
#include "objective_function.h"
#include "VND.h"

Grasp::Grasp(float alpha_, int iter_max_, long unsigned int num_elite_,bool use_path_relinking_):
  alpha(alpha_), iter_max(iter_max_), num_elite(num_elite_), use_path_relinking(use_path_relinking_) {}

void Grasp::construction(const BinaryKnapsack& binary_knapsack,
                                      std::vector<bool>& solution){
  // std::cout << "aaaasd\n";
  std::list<Item> sorted_items(binary_knapsack.items.begin(), binary_knapsack.items.end());
  sorted_items.sort([](const Item &a,const Item& b) {
              return a.utility < b.utility;
  });
  for(auto& i: sorted_items){
    if(i.utility == 0)
      std::cout <<i.to_string() << std::endl;
  }
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
    for(i = 0; i < sorted_items.size(); i++){
      if(item_iterator->utility >= threshold){
        ++item_iterator;
      }
    }
    // sort one index in the range of items
    int j = std::uniform_int_distribution<int>(0,(int)i-1)(generator);
    // Test if can put the item in the knapsack
    item_iterator=std::next(sorted_items.begin(),j);
    if(solution[item_iterator->id] != 1 && item_iterator->weight <= total_weight){
      solution[item_iterator->id]=true;
      total_weight+= item_iterator->weight;
    }
    // remove the item of the candidate items list
    sorted_items.erase(item_iterator);
  }
}

std::vector<bool> Grasp::path_relinking(BinaryKnapsack& binary_knapsack,std::vector<bool>& s1,std::vector<bool>& s2){
  std::vector<bool> aux_solution = s1;
  std::vector<bool> best_solution(s1.size());
  std::vector<bool> best_local_solution(s1.size());
  long best_ofv=LONG_MIN,best_local_ofv=LONG_MIN,current_ofv=LONG_MIN;
  std::list<long unsigned int> different_values_positions;
  for(long unsigned int i=0; i<s1.size();i++){
    if(s1[i]!=s2[i]){
      different_values_positions.push_back(i);
    }
  }

  auto best_local_element= different_values_positions.begin();// just to initialize
  for(long unsigned int i=0;i < different_values_positions.size();i++){
    current_ofv = LONG_MIN;
    best_local_ofv = LONG_MIN;
    for(auto j=different_values_positions.begin();j!=different_values_positions.end();++j){
      aux_solution[*j]= !aux_solution[*j];
      current_ofv = objective_function(binary_knapsack,aux_solution);
      if(current_ofv > best_local_ofv){
        best_local_ofv = current_ofv;
        best_local_solution = aux_solution;
        best_local_element = j;
      }
      aux_solution[*j]= !aux_solution[*j];
    }
    different_values_positions.erase(best_local_element);
    if(best_local_ofv > best_ofv){
      best_ofv = best_local_ofv;
      best_solution = best_local_solution;
    }
    
  }
  return best_solution;
}


std::vector<bool> Grasp::run(BinaryKnapsack binary_knapsack)
{
  long fo_star = LONG_MIN;
  std::vector<long> elites_ofv;
  std::vector<std::vector<bool>> elites_solution;
        
  std::vector<bool> solution(binary_knapsack.items.size(),false);
  std::vector<bool> aux_solution(binary_knapsack.items.size(),false);
  

  for (int i = 0; i<iter_max; i++) {
    // Limpa solucao
    for (long unsigned int j=0; j<binary_knapsack.items.size(); j++)
      aux_solution[j] = false;
    // Constroi solucao parcialmente gulosa
    construction(binary_knapsack,aux_solution);
    // constroi_solucao_grasp(n,aux_solution,p,w,b,alfa);
    printf("Constructed solution: %ld\t", objective_function(binary_knapsack,aux_solution));
    // Aplica busca local na solucao construida
    VND(binary_knapsack,aux_solution);
    printf("Refined solution: %ld\n", objective_function(binary_knapsack,aux_solution));
    if(use_path_relinking){
      if(elites_solution.size()>=2){
        std::vector<bool>& best_path_relinking_solution=aux_solution;
        for(long unsigned int i=1;i<elites_solution.size();i++){
          std::vector<bool> current_path_relinking_solution=path_relinking(binary_knapsack,elites_solution[i],aux_solution);
          if(objective_function(binary_knapsack,current_path_relinking_solution)>
             objective_function(binary_knapsack,best_path_relinking_solution)){
            best_path_relinking_solution=current_path_relinking_solution;
          }
        }
        aux_solution=best_path_relinking_solution;
      }

      if(elites_solution.size()<num_elite){
        elites_solution.push_back(aux_solution);
        elites_ofv.push_back(objective_function(binary_knapsack,aux_solution));
      }else{
        auto min_element_index = std::min_element(elites_ofv.begin(),elites_ofv.end()) - elites_ofv.begin();
        elites_solution[min_element_index] = aux_solution;
        elites_ofv[min_element_index] = objective_function(binary_knapsack,aux_solution);
      }
    }
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
