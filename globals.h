#pragma once
#include "stdlibs.h"
#include "entity.h"
//------------------------------------------------------------------------------------
// Globals 
//------------------------------------------------------------------------------------
namespace G {
  //------------------------------------------------------------------------------------
  // Globals 
  //------------------------------------------------------------------------------------
  // inline tells the compiler that only one instance of this variable / possibly a function should exist
  // constexpr and const are inline by default.
  constexpr int screenWidth{1024}, screenHeight{768};
  const std::string screenTitle{"Shooter - Prototype #2"};
  constexpr float blockWidth{6.f}, bW{blockWidth};
  constexpr float kPlayerSpeed{1.70f};
  constexpr float kBulletSpeed{0.8f};
  constexpr float countBlocksX{screenWidth / blockWidth},countBlocksY{screenHeight/blockWidth}; 
  inline std::vector<std::shared_ptr<Entity>> entity;
  inline std::vector<std::shared_ptr<Voxel>> free_voxels;

} // globals namespace
