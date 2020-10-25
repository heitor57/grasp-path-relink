#ifndef GRASP_H
#define GRASP_H
#include <vector> 
#include "BinaryKnapsack.h"
class Grasp
{
 public:
  float alpha;
  int iter_max;
  Grasp(float alpha_,int iter_max_);
  void construction(const BinaryKnapsack& binary_knapsack,
                    std::vector<bool>& solution);
  std::vector<bool> run(BinaryKnapsack binary_knapsack);
};

#endif
