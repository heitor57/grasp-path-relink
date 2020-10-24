#ifndef BINARYKNAPSACK_H
#define BINARYKNAPSACK_H
#include <vector> 
#include "Item.h" 
class BinaryKnapsack
{
 public:
  std::vector<Item> items;
  int capacity;
  BinaryKnapsack(int num_items, int capacity);
};

#endif
