#include "stdlibs.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;
using Vec3 = Vector3<float>; 

// GLOBALS
constexpr int screenWidth{1024}, screenHeight{768};
constexpr float blockWidth{3}, blockHeight{3};
constexpr float countBlocksX{screenWidth / blockWidth},countBlocksY{screenHeight/blockHeight}; 
static bool gameOver{false};
static bool pause{false};


struct Voxel { 
    Vec3 pos;  //x, y , theta
    int color;
    int health; // voxel health
    RectangleShape shape;
};

struct Entity {
    virtual void Update(float fElapsed) { /* check for collision */ /* update pos */  }
    virtual void Draw() { }
    virtual ~Entity() { }  
    const list<Voxel>& Vox() const { return vox; }
    private:
    // should this be shared_ptr?
    list<Voxel> vox;
};

// Bullet types
struct Bullet : Entity { // base

};
struct B1 : Bullet {

};

struct B2 : Bullet {

};

struct Player : Entity {


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
    //vector<Wall1> w1; // walltype 1
    //vector<Wall2> w2; // walltype 2
    //vector<E1> e1; // enemy type 1
    //vector<E2> e2; 
    vector<shared_ptr<Entity>> entity; 
    RenderWindow window{{screenWidth, screenHeight}, "Shooter - Prototype #2"};
    window.setFramerateLimit(100);

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
