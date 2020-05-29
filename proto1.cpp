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
constexpr float blockWidth{5.f}, blockHeight{5.f};
constexpr float countBlocksX{screenWidth / blockWidth},countBlocksY{screenHeight/blockHeight}; 
static bool gameOver{false};
static bool pause{false};

//------------------------------------------------------------------------------------
// Global Structs
//------------------------------------------------------------------------------------
struct Voxel { 
    Voxel(float mX, float mY, Color c = Color::Black + Color::Blue) : color{c}, vel(0,0) {
      shape.setPosition(mX, mY);
      shape.setSize({blockWidth, blockHeight});
      shape.setFillColor(c);
      shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
    }
    void setPos(Vec2 pos) { shape.setPosition(pos); }
    void move(Vec2 offset) { shape.move(offset); }
    Vec2 getPos() const { return shape.getPosition(); }
    // member data 
    Vec2 vel;
    Color color;
    optional<int> health; // voxel health
    RectangleShape shape;
};

struct Entity {
    virtual void update() { /* check for collision */ /* update pos */  }
    virtual void draw() { }
    virtual ~Entity() { }  
    //-----------------------------------------
    // Set position of entity as a whole 
    // ----------------------------------------
    virtual void setPos(Vec2 pos) {
      this->move(pos - this->pos);
      this->pos = pos;
    }
    //-----------------------------------------
    // Move all voxels by an offset
    // ----------------------------------------
    virtual void move(Vec2 offset) { 
      this->pos += offset;
     for(auto &v : vox) { 
       v.move(offset); }
     }
    vector<Voxel>& getVox() { return vox; }
    //-----------------------------------------
    // Entity health is the voxel count 
    // ----------------------------------------
    virtual size_t getHealth() const { return vox.size(); }
    protected:
    vector<Voxel> vox;
    Vec2 pos;
    Vec2 vel;
};

// Bullet types
struct Bullet : Entity { // base
   
};
struct B1 : Bullet {

};

struct B2 : Bullet {

};

struct Player : public Entity {
   // define the relative positions of the player voxels
   Player(Vec2 pos) {
     vox.emplace_back(0.f,0.f);
     vox.emplace_back(0.f+1.f * blockWidth, 0.f);
     vox.emplace_back(0.f+2.f * blockWidth, 0.f);
     vox.emplace_back(0.f+1.f * blockWidth, 0.f - 1.f* blockHeight, Color::Cyan);
     setPos(pos);
   }
};
// Enemy types
struct Enemy: Entity { // base
  vector<Vec2> path;
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
 
void removeDestroyedEntities(vector<Entity> & vec) {
  // TODO: consider a threshold for different entity types
  vec.erase(remove_if(begin(vec), end(vec), [] (const Entity & e) { return e.getHealth() <= 0u; }), end(vec));
}


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    vector<Entity> entity;
    entity.reserve(300);
    unsigned int levelId = 1;
    RenderWindow window{{screenWidth, screenHeight}, "Shooter - Prototype #2"};
    window.setFramerateLimit(100);
    //-----------------------------------------
    // Create the player 
    // ----------------------------------------
    entity.emplace_back(Player{Vec2(screenWidth / 2.f, screenHeight - 20.f)}); 
    
    while(true)
    {
        window.clear(Color::Black);

        if(Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;
        if(Keyboard::isKeyPressed(Keyboard::Key::Left)) { entity[0].move({-10.f,0.f}); }
        if(Keyboard::isKeyPressed(Keyboard::Key::Right)) { entity[0].move({+10.f,0.f}); }
        
        for(auto & e  : entity) {
            e.update();
            for (auto & v : e.getVox()) {
                               
                window.draw(v.shape);
            }
        }
        window.display();
    }
    return 0;
}
