//
//  spheres.h
//  spheres
//
//  Created by Piotr Brzeski on 2021-08-16.
//

#pragma once

#include "svg.h"

class spheres: public svg::svg {
public:
  static constexpr auto scale = 100;
  int const system_size;
  
  spheres(int size)
    : system_size(size)
  {
  }
  
  void grid() {
    for(auto i = 0; i <= system_size*scale; i += scale) {
      add_line(i, 0, i, system_size*scale);
      add_line(0, i, system_size*scale, i);
    }
  }
  
  void color(int red, int green, int blue) {
    fill_color(red, green, blue);
    stroke_color(red, green, blue);
  }
  
  void fill(int x, int y) {
    add_rect(x*scale + 1, y*scale + 1, scale - 2, scale - 2);
  }
  
  template<typename ModelT>
  void model(ModelT const& model, int x, int y) {
    for(auto row = 0; row < model.size(); ++row) {
      for(auto column = 0; column < model[row].size(); ++column) {
        if(model[row][column] == 1) {
          fill(column + y, row + x);
        }
      }
    }
  }
  
  
};
