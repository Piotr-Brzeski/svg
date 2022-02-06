//
//  main.cpp
//  percolation
//
//  Created by Piotr Brzeski on 2021-09-05.
//

#include "../svg/spheres.h"
#include <array>
#include <iostream>

namespace {

constexpr auto circle16_model = std::array<std::array<int, 16>, 16>{{
  {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0}
}};

constexpr auto system_size = 64;
auto image = spheres(system_size);

void add(int x, int y) {
  image.periodic(circle16_model, x, y);
}

void cluster1() {
  image.color(156, 225, 52); // Green 433
}

void cluster2() {
  image.color(250, 240, 71); // Yellow 561
}

void cluster3() {
  image.color(69, 31, 96); // Purple 196
}

void cluster4() {
  image.color(225, 54, 0); // Red 279
}

void img1() {
  cluster1();
  add(12, 31);
}

void img2() {
  img1();
  add(28, 51);
  add(22, 36);
  add(13, 58);
  add(9, 5);
  add(7, 15);
}

void img3(bool merged = false) {
  img2();
  add(56, 51);
  add(42, 59);
  add(7, 39);
  
  if(!merged) {
    cluster2();
  }
  add(48, 33);
  
  cluster3();
  add(29, 17);
  
  cluster4();
  add(54, 14);
}

void img4() {
  img3(true);
  
  cluster1();
  add(35, 36);
  add(4, 60);
  add(19, 42);

  cluster3();
  add(35, 11);
}

void grid() {
  image.color(0, 0, 0);
  image.grid();
}

void image1() {
  img1();
  grid();
  image.set_big_description("a");
}

void image2() {
  img2();
  grid();
  image.set_big_description("b");
}

void image3() {
  img3();
  grid();
  image.set_big_description("c");
}

void image4() {
  img4();
  grid();
  image.set_big_description("d");
}

}


int main(int argc, const char * argv[]) {
//  image1(); // 1
//  image2(); // 6
  image3(); // 12
//  image4();   // 16
  
  std::cout << image.get() << std::endl;
  return 0;
}
