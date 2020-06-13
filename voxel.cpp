#include "voxel.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "globals.h"
#include "stdlibs.h"
using namespace std;
using namespace sf;

Voxel::Voxel(float mX, float mY, Color c) {
  color = c;
  vel = Vec2{0.f, 0.f};
  dvel = Vec2{0.f, 0.f};
  setPosition(mX, mY);
  setSize({G::bW, G::bW});
  setFillColor(c);
  setOrigin(G::bW / 2.f, G::bW / 2.f);
}

