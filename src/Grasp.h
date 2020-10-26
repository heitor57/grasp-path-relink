#ifndef GRASP_H
#define GRASP_H
#include <vector> 
#include "BinaryKnapsack.h"
class Grasp
{
 public:
  float alpha;
  int iter_max;
  long unsigned int num_elite;
  bool use_path_relinking;
  Grasp(float alpha_,int iter_max_, long unsigned int num_elite_, bool use_path_relinking_);
  void construction(const BinaryKnapsack& binary_knapsack,
                    std::vector<bool>& solution);
  std::vector<bool> run(BinaryKnapsack binary_knapsack);
  std::vector<bool> path_relinking(BinaryKnapsack& binary_knapsack,const std::vector<bool>& s1,const std::vector<bool>& s2);
};

#endif
