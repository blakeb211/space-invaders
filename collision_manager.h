#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "stdlibs.h"
#include "voxel.h"
#include "globals.h"

struct CollisionManager {

    CollisionManager();
    // init
    CollisionManager(); 
    // per frame method call
    void CheckCollisionsForThisFrame();
    void HandleCollisionsForThisFrame();
};
