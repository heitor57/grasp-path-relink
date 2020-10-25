#include "Item.h"
#include <string>
Item::Item(int weight_, int utility_):weight(weight_),utility(utility_){}
Item::Item():weight(0),utility(0){}

std::string Item::to_string(){
  return "w="+std::to_string(weight)+",u="+std::to_string(utility)+",id="+std::to_string(id);
}
