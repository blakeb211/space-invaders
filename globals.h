#pragma once
#include "stdlibs.h"

struct Entity;

namespace G {
    //------------------------------------------------------------------------------------
    // Globals 
    //------------------------------------------------------------------------------------
    constexpr int screenWidth{1024}, screenHeight{768};
    const std::string screenTitle{"Shooter - Prototype #2"};
    constexpr float blockWidth{3.f}, bW{blockWidth};
    constexpr float countBlocksX{screenWidth / blockWidth},countBlocksY{screenHeight/blockWidth}; 
    std::vector<std::shared_ptr<Entity>> entity;

} // globals namespace
