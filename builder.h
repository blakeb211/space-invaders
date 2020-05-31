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
#include "stdlibs.h"
#include "voxel.h"

namespace Builder {
    
    void build_player(std::vector<Voxel> &vox);
    void build_B1(std::vector<Voxel> &vox);
    void build_B2(std::vector<Voxel> &vox);
    void build_E1(std::vector<Voxel> &vox);
    void build_E2(std::vector<Voxel> &vox);
    void build_E3(std::vector<Voxel> &vox);
    void build_E4(std::vector<Voxel> &vox);

} // namespace Builder
