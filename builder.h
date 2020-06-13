//------------------------------------------------------------------------------
// builder.h, Blake Baird
//------------------------------------------------------------------------------
// Defines
//  Voxel struct
//  Builder namespace - Defines relative position and color of voxels
//                      for each Entity.
//------------------------------------------------------------------------------

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "entity.h"
#include "stdlibs.h"
#include "voxel.h"

namespace Builder {

void build_player(std::vector<Voxel> &vox);
void build_B1(std::vector<Voxel> &vox);  // called from constructor
void build_B2(std::vector<Voxel> &vox);  // called from constructor
void build_B3(std::vector<Voxel> &vox);  // called from constructor
void build_E1(std::vector<Voxel> &vox);  // called from constructor
void build_E2(std::vector<Voxel> &vox);  // called from constructor
void build_E3(std::vector<Voxel> &vox);  // called from constructor
void build_E4(std::vector<Voxel> &vox);  // called from constructor
void build_level(unsigned int &levelId);
float calc_dist(const Vec2 &va, const Vec2 &vb);
void build_wall1(Vec2 start, Vec2 end, std::vector<Voxel> &vox);

}  // namespace Builder
