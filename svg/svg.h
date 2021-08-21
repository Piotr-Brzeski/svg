//
//  svg.h
//  svg
//
//  Created by Piotr Brzeski on 2017-02-04.
//

#pragma once

#include <string>
#include <vector>
#include <map>

namespace svg
{

/// XML Tag class
class tag
{
public:
  explicit tag(std::string&& name)
  : m_name(std::move(name))
  {
  }
  
  template<class text_t>
  void add_text(text_t&& text)
  {
    m_text += std::forward<text_t>(text);
  }
  
  tag& add_child(std::string&& name)
  {
    m_children.push_back(tag(std::move(name)));
    return m_children.back();
  }
  
  tag& add_child(tag&& tag)
  {
    m_children.push_back(std::move(tag));
    return m_children.back();
  }
  
  template<typename value_t>
  typename std::enable_if<!std::is_arithmetic<typename std::remove_reference<value_t>::type>::value>::type set_attribute(std::string&& name, value_t&& value)
  {
    m_attributes[std::move(name)] = std::forward<value_t>(value);
  }
  
  template<typename value_t>
  typename std::enable_if<std::is_integral<typename std::remove_reference<value_t>::type>::value>::type set_attribute(std::string&& name, value_t value)
  {
    m_attributes[std::move(name)] = std::to_string(value);
  }
  
  template<typename value_t>
  typename std::enable_if<std::is_floating_point<typename std::remove_reference<value_t>::type>::value>::type set_attribute(std::string&& name, value_t value)
  {
    std::string string_value = to_string(value);
    m_attributes[std::move(name)] = string_value;
  }
  
  template<typename value_t>
  void set_attribute(std::string&& name, value_t* value)
  {
    m_attributes[std::move(name)] = value;
  }
  
  std::string get() const
  {
    std::string content = '<' + m_name;
    for (auto& attribute : m_attributes) {
      content += ' ';
      content += attribute.first;
      content += "=\"";
      content += attribute.second;
      content += '"';
    }
    if (m_text.empty() && m_children.empty()) {
      content += "/>";
    }
    else {
      content += '>';
      content += m_text;
      for (auto& child : m_children) {
        content += child.get();
      }
      content += "</";
      content += m_name;
      content += '>';
    }
    return content;
  }
  
  template<typename value_t>
  static typename std::enable_if<std::is_floating_point<typename std::remove_reference<value_t>::type>::value, std::string>::type to_string(value_t value)
  {
    std::string string = std::to_string(value);
    while (string.back() == '0') {
      string.pop_back();
    }
    if (string.back() == '.') {
      string.pop_back();
    }
    return string;
  }
  template<typename value_t>
  static typename std::enable_if<std::is_integral<typename std::remove_reference<value_t>::type>::value, std::string>::type to_string(value_t value)
  {
    return std::to_string(value);
  }
  template<typename value_t>
  static typename std::enable_if<!std::is_arithmetic<typename std::remove_reference<value_t>::type>::value, std::string>::type to_string(value_t&& value)
  {
    return std::string(std::forward<value_t>(value));
  }
  
private:
  std::string                         m_name;
  std::string                         m_text;
  std::vector<tag>                    m_children;
  std::map<std::string, std::string>  m_attributes;
  
};  //  class tag


struct point
{
  template<typename x_t, typename y_t>
  point(x_t&& x, y_t&& y)
  : position(tag::to_string(std::forward<x_t>(x)) + ',' + tag::to_string(std::forward<y_t>(y)))
  {
  }
  
  const std::string position;
  
};  //  struct point

// SVG Image
class svg
{
public:
  enum class text_mode { horizontal, vertical, h_center, v_center };
  
  class text_field
  {
  public:
    text_field(double size,tag& text, text_mode mode)
    : m_size(size)
    , m_text(text)
    , m_mode(mode)
    {
    }
    
    template<class text_t>
    void add(text_t&& text)
    {
      double y = (m_mode == text_mode::vertical || m_mode == text_mode::v_center) ? -0.2*m_size : 0.8*m_size;
      auto& tspan = m_text.add_child("tspan");
      tspan.set_attribute("y", y);
      tspan.add_text(std::forward<text_t>(text));
    }
    
    template<class text_t>
    void add_subscript(text_t&& text)
    {
      double y = (m_mode == text_mode::vertical || m_mode == text_mode::v_center) ? -0.145*m_size : 0.875*m_size;
      auto& tspan = m_text.add_child("tspan");
      tspan.set_attribute("y", y);
      tspan.set_attribute("style", "font-size:65%");
      tspan.add_text(std::forward<text_t>(text));
    }
    
    template<class text_t>
    void add_superscript(text_t&& text)
    {
      double y = (m_mode == text_mode::vertical || m_mode == text_mode::v_center) ? -0.5*m_size : 0.5*m_size;
      auto& tspan = m_text.add_child("tspan");
      tspan.set_attribute("y", y);
      tspan.set_attribute("style", "font-size:65%");
      tspan.add_text(std::forward<text_t>(text));
    }
    
  private:
    double      m_size;
    tag&        m_text;
    text_mode   m_mode;
    
  };  //  class text_field
  
  svg(bool grayscale = false)
    : m_definitions(m_svg.add_child("defs"))
    , m_grayscale(grayscale)
  {
    m_svg.set_attribute("xmlns", "http://www.w3.org/2000/svg");
  }
  
  void fill_none()
  {
    m_fill = "none";
  }
  template<class text_t>
  void fill_color(text_t&& color)
  {
    m_fill = std::forward<text_t>(color);
  }
  void fill_color(uint8_t red, uint8_t green, uint8_t blue)
  {
    set_color(m_fill, red, green, blue);
  }
  
  template<typename string_t>
  void fill_pattern(string_t&& pattern)
  {
    m_fill = "url(#";
    m_fill += std::forward<string_t>(pattern);
    m_fill += ')';
  }
  
  void stroke_none()
  {
    m_stroke_color = "none";
  }
  template<class text_t>
  void stroke_color(text_t&& color)
  {
    m_stroke_color = std::forward<text_t>(color);
  }
  void stroke_color(uint8_t red, uint8_t green, uint8_t blue)
  {
    set_color(m_stroke_color, red, green, blue);
  }
  void stroke_width(double width)
  {
    m_stroke_width = width;
  }
  
  template<typename x1_t, typename y1_t, typename x2_t, typename y2_t>
  typename std::enable_if<std::is_arithmetic<typename std::remove_reference<x1_t>::type>::value &&
  std::is_arithmetic<typename std::remove_reference<y1_t>::type>::value &&
  std::is_arithmetic<typename std::remove_reference<x2_t>::type>::value &&
  std::is_arithmetic<typename std::remove_reference<y2_t>::type>::value>::type
  add_line(x1_t&& x1, y1_t&& y1, x2_t&& x2, y2_t&& y2)
  {
    auto& line = m_svg.add_child("line");
    line.set_attribute("x1", std::forward<x1_t>(x1));
    line.set_attribute("y1", std::forward<y1_t>(y1));
    line.set_attribute("x2", std::forward<x2_t>(x2));
    line.set_attribute("y2", std::forward<y2_t>(y2));
    add_drawing_attributes(line);
    update_size(std::min<double>(x1, x2), std::min<double>(y1, y2), std::abs(x1 - x2), std::abs(y1 - y2));
  }
  
  
  template<typename x_t, typename y_t, typename width_t, typename height_t>
  typename std::enable_if<std::is_arithmetic<typename std::remove_reference<x_t>::type>::value &&
  std::is_arithmetic<typename std::remove_reference<y_t>::type>::value &&
  std::is_arithmetic<typename std::remove_reference<width_t>::type>::value &&
  std::is_arithmetic<typename std::remove_reference<height_t>::type>::value>::type
  add_rect(x_t&& x, y_t&& y, width_t&& width, height_t&& height)
  {
    auto& rect = m_svg.add_child("rect");
    rect.set_attribute("x", std::forward<x_t>(x));
    rect.set_attribute("y", std::forward<y_t>(y));
    rect.set_attribute("width", std::forward<width_t>(width));
    rect.set_attribute("height", std::forward<height_t>(height));
    add_drawing_attributes(rect);
    update_size(x, y, width, height);
  }
  
  template<typename x_t, typename y_t, typename r_t>
  typename std::enable_if<std::is_arithmetic<typename std::remove_reference<x_t>::type>::value &&
  std::is_arithmetic<typename std::remove_reference<y_t>::type>::value &&
  std::is_arithmetic<typename std::remove_reference<r_t>::type>::value>::type
  add_circle(x_t&& x, y_t&& y, r_t&& r)
  {
    auto& circle = m_svg.add_child("circle");
    circle.set_attribute("cx", std::forward<x_t>(x));
    circle.set_attribute("cy", std::forward<y_t>(y));
    circle.set_attribute("r", std::forward<r_t>(r));
    add_drawing_attributes(circle);
    update_size(x - r, y - r, 2*r, 2*r);
  }
  
  void add_polygon(const std::vector<point>& points)
  {
    std::string positions;
    for(auto& point : points) {
      if (!positions.empty()) {
        positions += ' ';
      }
      positions += point.position;
    }
    auto& polygon = m_svg.add_child("polygon");
    polygon.set_attribute("points", std::move(positions));
    add_drawing_attributes(polygon);
    // TODO: update_size somehow
  }
  
  template<typename x_t, typename y_t, typename width_t, typename height_t>
  typename std::enable_if<std::is_arithmetic<typename std::remove_reference<x_t>::type>::value &&
  std::is_arithmetic<typename std::remove_reference<y_t>::type>::value &&
  std::is_arithmetic<typename std::remove_reference<width_t>::type>::value &&
  std::is_arithmetic<typename std::remove_reference<height_t>::type>::value, text_field>::type
  add_text_field(x_t&& x, y_t&& y, width_t&& width, height_t&& height, text_mode mode = text_mode::horizontal)
  {
    tag& field = m_svg.add_child("svg");
    field.set_attribute("x", std::forward<x_t>(x));
    field.set_attribute("y", std::forward<y_t>(y));
    field.set_attribute("width", std::forward<width_t>(width));
    field.set_attribute("height", std::forward<height_t>(height));
    double size = (mode == text_mode::vertical || mode == text_mode::v_center) ? width : height;
    tag& text = field.add_child("text");
    text.set_attribute("font-size", 0.9*size);
    add_drawing_attributes(text);
    switch (mode) {
      case text_mode::horizontal:
        text.set_attribute("x", 0);
        break;
      case text_mode::h_center:
        text.set_attribute("x", 0.5*width);
        text.set_attribute("text-anchor", "middle");
        break;
      case text_mode::vertical:
        text.set_attribute("x", 0);
        text.set_attribute("transform", "rotate(90)");
        break;
      case text_mode::v_center:
        text.set_attribute("x", 0.5*height);
        text.set_attribute("transform", "rotate(90)");
        text.set_attribute("text-anchor", "middle");
        break;
    }
    update_size(x, y, width, height);
    return text_field(size, text, mode);
  }
  
  template<typename id_t, typename def_t>
  void add_pattern(id_t&& id, double size, def_t&& definition)
  {
    std::string string_size = tag::to_string(size);
    std::string pattern = "<pattern id=\"";
    pattern += std::forward<id_t>(id);
    pattern += "\" x=\"0\" y=\"0\" width=\"";
    pattern += string_size;
    pattern += "\" height=\"";
    pattern += string_size;
    pattern += "\" patternUnits=\"userSpaceOnUse\">";
    pattern += std::forward<def_t>(definition);
    pattern += "</pattern>";
    m_definitions.add_text(std::move(pattern));
  }
  
  std::string get()
  {
    std::string content = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 20010904//EN\" \"http://www.w3.org/TR/2001/REC-SVG-20010904/DTD/svg10.dtd\">\n";
    double width = m_x < std::numeric_limits<double>::max() ? m_width + m_x : m_width;
    double height = m_y < std::numeric_limits<double>::max() ? m_height + m_y : m_height;
    m_svg.set_attribute("width", width);
    m_svg.set_attribute("height", height);
    content += m_svg.get();
    return content;
  }
  
  void set_color(std::string& color, uint8_t red, uint8_t green, uint8_t blue)
  {
    color = "rgb(";
    if (m_grayscale) {
      std::string s_value = std::to_string((red + green + blue)/3);
      color += s_value;
      color += ',';
      color += s_value;
      color += ',';
      color += s_value;
    }
    else {
      color += std::to_string(red);
      color += ',';
      color += std::to_string(green);
      color += ',';
      color += std::to_string(blue);
    }
    color += ')';
  }
  
private:
  void add_drawing_attributes(tag& t)
  {
    t.set_attribute("fill", m_fill);
    t.set_attribute("stroke", m_stroke_color);
    t.set_attribute("stroke-width", m_stroke_width);
  }
  
  void update_size(double x, double y, double width, double height)
  {
    m_x = std::max(0.0, std::min(m_x, x));
    m_y = std::max(0.0, std::min(m_y, y));
    m_width = std::max(m_width, x + width);
    m_height = std::max(m_height, y + height);
  }
  
  tag                                 m_svg           {"svg"};
  tag&                                m_definitions;
  std::string                         m_fill          = "none";
  std::string                         m_stroke_color  = "rgb(0,0,0)";
  double                              m_stroke_width  = 1.0;
  double                              m_x             = std::numeric_limits<double>::max();
  double                              m_y             = std::numeric_limits<double>::max();
  double                              m_width         = 0.0;
  double                              m_height        = 0.0;
  bool                                m_grayscale     = false;
  
};  //  class svg

} //  namespace svg

