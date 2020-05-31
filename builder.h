#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "stdlibs.h"
#include "globals.h"
using namespace sf;
using namespace std;
using Vec2 = Vector2<float>; 

struct Voxel : RectangleShape { 
    Voxel(float mX, float mY, Color c = Color::White) : color{c}, vel(0,0) {
        setPosition(mX, mY);
        setSize({G::bW, G::bW});
        setFillColor(c);
        setOrigin(G::bW / 2.f, G::bW / 2.f);
    }
    // member data 
    Vec2 vel;
    Color color;
    optional<int> health; // voxel health
};

namespace Builder {

void build_B1(vector<Voxel> &vox, const float & bW) { 
        vox.emplace_back(1.f * G::bW, 0.f * G::bW, Color(209,181,190,255));
        vox.emplace_back(0.f * G::bW, 1.f * G::bW, Color(209,181,190,255));
        vox.emplace_back(1.f * G::bW, 1.f * G::bW, Color(209,181,190,255));
        vox.emplace_back(2.f * G::bW, 1.f * G::bW, Color(209,181,190,255));
        vox.emplace_back(1.f * G::bW, 2.f * G::bW, Color(209,181,190,255));
}

} // namespace Builder
