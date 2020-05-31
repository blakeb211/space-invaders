#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
using Vec2 = sf::Vector2<float>;

struct Voxel : sf::RectangleShape { 
  Voxel(float mX, float mY, sf::Color c = sf::Color::White); 
  // member data 
  Vec2 vel;
  sf::Color color;
  std::optional<int> health; // voxel health
};


