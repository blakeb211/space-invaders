#include <SFML/Graphics.hpp>
#include "collision_manager.h"
#include <SFML/System.hpp>
#include "stdlibs.h"
#include "voxel.h"
#include "globals.h"
using namespace std;
using namespace sf;

CollisionManager::CollisionManager() { cout << "Initializing Collision Manager" << endl; }
// init

// do all voxel collision checks between entities 
void CollisionManager::CheckCollisionsForThisFrame() {
    // get ref to gloabl entity vector
    auto & entRef = G::entity;
    // find unique pairs of entities to test collisions
    int entityPairCount = 0;
    int collCheckCount = 0;
    for (int i = 0; i < entRef.size() - 1; i++) {
        for (int j = i + 1; j < entRef.size(); j++) {
            // dont compare voxels if delta(x_coord) is greater than 20 
            if (entRef[i]->o_type == entRef[j]->o_type) continue;
            if (abs(entRef[i]->getPos().x - entRef[j]->getPos().x) > 180.f || abs(entRef[i]->getPos().y - entRef[j]->getPos().y) > 180.f) continue;
            entityPairCount++; 
            // Loop over voxels of each entity to check for overlap
            auto e1_vox = entRef[i]->getVox();
            auto e2_vox = entRef[j]->getVox();
            int e1_vox_size = e1_vox.size();
            int e2_vox_size = e2_vox.size();
            bool vi1_collided = false;
            for (int vi1 = 0; vi1 < e1_vox_size; vi1++) {
                vi1_collided = false;
                for (int vi2 = 0; vi2 < e2_vox_size; vi2++) {
                    collCheckCount++;
                    if(e1_vox[vi1].getGlobalBounds().intersects(e2_vox[vi2].getGlobalBounds())) {
                        vi1_collided = true;
                        // collision occurred, so call the collideWith methods on both entities
                        entRef[j]->collideWith(entRef[i]->o_type, vi2); 
                        //cout << "collision happening for " << (int)entRef[i]->o_type << "-" << (int)entRef[j]->o_type << endl;
                    }
                }
                if (vi1_collided) {
                    entRef[i]->collideWith(entRef[j]->o_type, vi1);  
                }
            }
            entRef[j]->eraseDeadVoxel();
        }
        entRef[i]->eraseDeadVoxel();
    }
}

void CollisionManager::HandleCollisionsForThisFrame() {
    // loop over voxels
    // check voxel-voxel collisions for each entity pair
    // handle voxel-voxel collisions
    // each entity can have it's own collideWith(o_type) method that gets called from here
} 
