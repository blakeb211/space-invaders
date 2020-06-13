#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "globals.h"
#include "stdlibs.h"
#include "voxel.h"

struct CollisionManager {
  CollisionManager();
  // per frame method call
  void CheckCollisionsForThisFrame();
};
