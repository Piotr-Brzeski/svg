//
//  sphere16.cpp
//  sphere16
//
//  Created by Piotr Brzeski on 2021-08-16.
//

#include "../svg/spheres.h"
#include "model.h"
#include <array>
#include <iostream>

int main(int argc, const char * argv[]) {
  constexpr auto system_size = 20;
  auto image = spheres(system_size);
  
  image.color(156, 225, 52);
  image.model(circle16_model, 2, 2);
  
  image.color(0, 0, 0);
  image.grid();
  image.add_rect(0, 10*image.scale - 2, system_size*image.scale, 5);
  image.add_rect(10*image.scale - 2, 0, 5, system_size*image.scale);
  
  image.set_description("b");
  
  std::cout << image.get() << std::endl;
  return 0;
}
