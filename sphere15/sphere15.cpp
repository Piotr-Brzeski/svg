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
  
  image.color(0, 255, 0);
  image.model(circle15_model, 2, 2);
  
  image.color(0, 0, 0);
  image.grid();
  image.fill_none();
  image.add_rect(9*image.scale - 1, 9*image.scale - 1, image.scale + 2, image.scale + 2);
  image.add_rect(9*image.scale + 1, 9*image.scale + 1, image.scale - 2, image.scale - 2);
  
  std::cout << image.get() << std::endl;
  return 0;
}
