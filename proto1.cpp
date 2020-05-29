#include "stdlibs.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;
using Vec2 = Vector2<float>; 

//------------------------------------------------------------------------------------
// Globals 
//------------------------------------------------------------------------------------
constexpr int screenWidth{1024}, screenHeight{768};
constexpr float blockWidth{3}, blockHeight{3};
constexpr float countBlocksX{screenWidth / blockWidth},countBlocksY{screenHeight/blockHeight}; 
static bool gameOver{false};
static bool pause{false};

//------------------------------------------------------------------------------------
// Global Structs
//------------------------------------------------------------------------------------
struct Voxel { 
    Voxel(float mX, float mY, Color c = Color::Red) : pos{mX,mY}, color{c}, vel{0.f,0.f} {
      shape.setPosition(mX, mY);
      shape.setSize({blockWidth, blockHeight});
      shape.setFillColor(c);
    }
    Vec2 pos;  //x, y , theta
    Vec2 vel;
    Color color;
    optional<int> health; // voxel health
    RectangleShape shape;
};

struct Entity {
    virtual void Update(float fElapsed) { /* check for collision */ /* update pos */  }
    virtual void Draw() { }
    virtual ~Entity() { }  
    const vector<Voxel>& Vox() const { return vox; }
    protected:
    // should this be shared_ptr?
    vector<Voxel> vox;
};

// Bullet types
struct Bullet : Entity { // base
  
};
struct B1 : Bullet {

};

struct B2 : Bullet {

};

struct Player : public Entity {
   Player() {
     vox.emplace_back(1.f,1.f);
     vox.emplace_back(1.f,2.f);
     vox.emplace_back(2.f,1.f);
     vox.emplace_back(2.f,2.f);
     vox.emplace_back(2.f,3.f);
     vox.emplace_back(3.f,1.f);
     vox.emplace_back(3.f,2.f);
   }
};
// Enemy types
struct Enemy: Entity { // base
};

struct E1: Enemy {

};
struct E2: Enemy {

};
struct E3: Enemy {

};
struct E4: Enemy {

};

// Wall types
struct Wall : Entity { // base
};
struct Wall1 : Wall {
};
struct Wall2 : Wall {
};


//------------------------------------------------------------------------------------
// Global Functions
//------------------------------------------------------------------------------------
template<class T1, class T2> bool isIntersecting(T1& a, T2& b) {
    return true;
}

void testCollision(Entity &e1, Entity &e2) {
    if (!isIntersecting(e1, e2)) return;
    // handle collision
}

//vector.erase(remove_if(begin(vec), end(vec)), [] (    ) { return o.destroyed; };, end(vec));


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    vector<shared_ptr<Entity>> entity{};
    unsigned int levelId = 1;
    RenderWindow window{{screenWidth, screenHeight}, "Shooter - Prototype #2"};
    window.setFramerateLimit(100);
    // Game loading
    entity.push_back(make_shared<Player>());
    while(true)
    {
        window.clear(Color::Black);

        if(Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;
        
        for(auto & e  : entity) {
            for (auto & v : e->Vox()) {
                window.draw(v.shape);
            }
        }
        window.display();
    }

    return 0;
}
