#include "VND.h"
#include "objective_function.h"

void best_neighbor_1(BinaryKnapsack& binary_knapsack, std::vector<bool>& solution)
{
  long fo_original;
  long fo_max;
  long fo_vizinho;
  int melhor_bit;
    
  fo_original = objective_function(binary_knapsack,solution);
    
  fo_max = -DBL_MAX;
        
  for (long unsigned int j = 0; j < solution.size(); j++) {
            
    solution[j] = !solution[j];
            
    fo_vizinho = objective_function(binary_knapsack,solution);
            
    // armazena melhor vizinho
    if (fo_vizinho > fo_max) {
      melhor_bit = j;
      fo_max = fo_vizinho;
    }
            
    // volta a solucao inicial
    solution[j] = !solution[j];
  }
        
  // se encontrou algum vizinho melhor
  if (fo_max > fo_original) {
    solution[melhor_bit] = !solution[melhor_bit];
    // troca_bit(s,melhor_bit);
    printf("Vizinho melhor em N1! FO = %ld\n", fo_max);
  }

}

/* aplica busca local pela estrategia do melhor aprimorante */
void best_neighbor_2(BinaryKnapsack& binary_knapsack, std::vector<bool>& solution)
{
  long fo_max, fo_vizinho;
  int melhor_bit_1, melhor_bit_2;
    
  long fo_original = objective_function(binary_knapsack,solution);
    
  fo_max = -DBL_MAX;
        
  // para cada par de posicoes do vetor
  for (long unsigned int i = 0; i < solution.size(); i++) {
            
    // troca primeiro bit
    solution[i] = !solution[i];
            
    for (long unsigned int j = i+1; j < solution.size(); j++) {
                
                
      // troca segundo bit
      solution[j] = !solution[j];
                
      // fo vizinho
      fo_vizinho = objective_function(binary_knapsack,solution);
                
      // armazena melhor vizinho
      if (fo_vizinho > fo_max) {
        melhor_bit_1 = i;
        melhor_bit_2 = j;
        fo_max = fo_vizinho;
      }
                
      // volta segundo bit
      solution[j] = !solution[j];
                
    }
    // volta a solucao inicial
    solution[i] = !solution[i];
  }
        
  // se encontrou algum vizinho melhor
  if (fo_max > fo_original) {
    solution[melhor_bit_1] = !solution[melhor_bit_1];
    solution[melhor_bit_2] = !solution[melhor_bit_2];
    printf("Vizinho melhor em N2! FO = %ld\n", fo_max);
  }
}
void VND(BinaryKnapsack& binary_knapsack,std::vector<bool>& solution){
  int k=1;
  long ofv_s;
  while(k <= 2){
    ofv_s = objective_function(binary_knapsack,solution);
    switch(k){
    case 1: best_neighbor_1(binary_knapsack,solution);
      break;
    case 2: best_neighbor_2(binary_knapsack,solution);
      break;
    default:
      break;
    }
    if (objective_function(binary_knapsack,solution) > ofv_s){
      k = 1;
    }
    else k++;
  }
}
