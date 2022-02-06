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
    : svg::svg(false)
    , system_size(size)
  {
  }
  
  void grid() {
    for(auto i = 0; i <= system_size*scale; i += scale) {
      add_line(i, 0, i, system_size*scale);
      add_line(0, i, system_size*scale, i);
    }
    add_line(1, 1, 1, system_size*scale - 1);
    add_line(1, 1, system_size*scale - 1, 1);
    add_line(system_size*scale - 1, 1, system_size*scale - 1, system_size*scale - 1);
    add_line(1, system_size*scale - 1, system_size*scale - 1, system_size*scale - 1);
  }
  
  void color(int red, int green, int blue) {
    fill_color(red, green, blue);
    stroke_color(red, green, blue);
  }
  
  void fill(int x, int y) {
    add_rect(x*scale + 1, y*scale + 1, scale - 2, scale - 2);
  }
  
  void set_description(const char* description) {
    fill_color(255, 255, 255);
    add_rect(1, 1, 2*scale - 2, 2*scale - 2);
    fill_color(0, 0, 0);
    auto text_field = add_text_field(1, 1, 2*scale - 2, 2*scale - 2, svg::svg::text_mode::h_center);
    text_field.add_small(description);
  }
  
  void set_big_description(const char* description) {
    fill_color(255, 255, 255);
    add_rect(scale + 1, scale + 1, 3*scale - 2, 3*scale - 2);
    fill_color(0, 0, 0);
    auto text_field = add_text_field(scale + 1, scale + 1, 3*scale - 2, 3*scale - 2, svg::svg::text_mode::h_center);
    text_field.add(description);
  }
  
  template<typename ModelT>
  void model(ModelT const& model, int x, int y) {
    for(auto row = 0; row < model.size(); ++row) {
      for(auto column = 0; column < model[row].size(); ++column) {
        if(model[row][column] > 0) {
          fill(column + y, row + x);
        }
      }
    }
  }
  
  template<typename ModelT>
  void contour(ModelT const& model, int x, int y) {
    for(auto row = 0; row < model.size(); ++row) {
      for(auto column = 0; column < model[row].size(); ++column) {
        if(model[row][column] > 0) {
          auto pos_x = column + y;
          auto pos_y = row + x;
          if(column == 0 || model[row][column - 1] == 0) {
            add_rect(pos_x*scale - 2, pos_y*scale - 2, 5, scale + 5);
          }
          if(column == model[row].size() - 1 || model[row][column + 1] == 0) {
            add_rect((pos_x + 1)*scale - 2, pos_y*scale - 2, 5, scale + 5);
          }
          if(row == 0 || model[row - 1][column] == 0) {
            add_rect(pos_x*scale - 2, pos_y*scale - 2, scale + 5, 5);
          }
          if(row == model.size() - 1 || model[row + 1][column] == 0) {
            add_rect(pos_x*scale - 2, (pos_y + 1)*scale - 2, scale + 5, 5);
          }
        }
      }
    }
  }
  
  template<typename ModelT>
  void periodic(ModelT const& model, int x, int y) {
    for(auto row = 0; row < model.size(); ++row) {
      for(auto column = 0; column < model[row].size(); ++column) {
        if(model[row][column] > 0) {
          auto pos_x = position(column + x);
          auto pos_y = position(row + y);
          fill(pos_x, pos_y);
        }
      }
    }
  }
  
private:
  int position(int pos) {
    while(pos < 0) {
      pos += system_size;
    }
    while(pos >= system_size) {
      pos -= system_size;
    }
    return pos;
  }
  
};
