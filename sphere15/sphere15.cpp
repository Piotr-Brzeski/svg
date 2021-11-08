//
//  sphere15.cpp
//  sphere15
//
//  Created by Piotr Brzeski on 2021-08-16.
//

#include "spheres.h"
#include <array>
#include <iostream>

namespace {

constexpr auto circle15_model = std::array<std::array<int, 15>, 15>{{
  {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0}
}};

}


int main(int argc, const char * argv[]) {
  constexpr auto system_size = 19;
  auto image = spheres(system_size);
  
  image.color(156, 225, 52);
  image.model(circle15_model, 2, 2);
  
  image.color(0, 0, 0);
  image.grid();
  image.add_rect(0, 9.5*image.scale - 2, system_size*image.scale, 5);
  image.add_rect(9.5*image.scale - 2, 0, 5, system_size*image.scale);
  
  image.set_description("a");
  
  std::cout << image.get() << std::endl;
  return 0;
}
