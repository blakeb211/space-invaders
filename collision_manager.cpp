#include "collision_manager.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "globals.h"
#include "stdlibs.h"
#include "voxel.h"
using namespace std;
using namespace sf;

CollisionManager::CollisionManager() {
  cout << "Initializing Collision Manager" << endl;
}

// do all voxel collision checks between entities
void CollisionManager::CheckCollisionsForThisFrame() {
  // get ref to gloabl entity vector
  auto& entRef = G::entity;
  // find unique pairs of entities to test collisions
  int entityPairCount = 0;
  int collCheckCount = 0;
  for (int i = 0; i < entRef.size() - 1; i++) {
    for (int j = i + 1; j < entRef.size(); j++) {
      // dont compare voxels if delta(x_coord) is greater than 20
      if (entRef[i]->o_type == entRef[j]->o_type) continue;
      if (abs(entRef[i]->getCenter().x - entRef[j]->getCenter().x) > 140.f ||
          abs(entRef[i]->getCenter().y - entRef[j]->getCenter().y) > 100.f)
        continue;
      entityPairCount++;
      // Loop over voxels of each entity to check for overlap
      auto e1_vox = entRef[i]->getVox();
      auto e2_vox = entRef[j]->getVox();
      int e1_vox_size = e1_vox.size();
      int e2_vox_size = e2_vox.size();
      for (int vi1 = 0; vi1 < e1_vox_size; vi1++) {
        int index_vi2_that_collided = 0;
        for (int vi2 = 0; vi2 < e2_vox_size; vi2++) {
          collCheckCount++;
          if (e1_vox[vi1].getGlobalBounds().intersects(
                  e2_vox[vi2].getGlobalBounds())) {
            // collision occurred, so call the collideWith methods on both
            // entities
            entRef[j]->collideWith(*entRef[i], vi2, e1_vox[vi1].getPosition());
            entRef[i]->collideWith(*entRef[j], vi1, e2_vox[vi2].getPosition());
            // cout << "collision happening for " << (int)entRef[i]->o_type <<
            // "-" << (int)entRef[j]->o_type << endl;
          }
        }
      }
      entRef[j]->eraseDeadVoxel();
    }
    entRef[i]->eraseDeadVoxel();
  }
}
