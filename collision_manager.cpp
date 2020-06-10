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
            if (abs(entRef[i]->getPos().x - entRef[j]->getPos().x) > 20.f) continue;
            entityPairCount++; 
            // Loop over voxels of each entity to check for overlap
            for (auto e1_v : entRef[i]->getVox()) {
                for (auto e2_v : entRef[j]->getVox()) {
                    if (abs(e1_v.getPosition().x - e2_v.getPosition().x) > 6.f) continue;
                    collCheckCount++;
                    if(e1_v.getGlobalBounds().intersects(e2_v.getGlobalBounds())) {
                    }
                }
            } 
        }
    }
    //cout << "Entities: " << entRef.size() << " Entity Pairs: " << entityPairCount << endl ;
    //cout << "Voxels compared:" << collCheckCount << endl;
    
    /* with reduced # of voxels for the walls */
    /* Entities: 25 Entity Pairs: 300
     * Voxels compared:263'033 */
}

void CollisionManager::HandleCollisionsForThisFrame() {
    // loop over voxels
    // check voxel-voxel collisions for each entity pair
    // handle voxel-voxel collisions
    // each entity can have it's own collideWith(o_type) method that gets called from here
} 
