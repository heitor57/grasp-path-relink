#ifndef ITEM_H
#define ITEM_H

#include <string>
class Item
{
 public:
  int weight, utility, id;
  Item(int weight_, int utility_);
  Item();
  std::string to_string();
};



#endif
