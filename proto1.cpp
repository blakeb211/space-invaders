#include "stdlibs.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;
using Vec2 = Vector2<float>; 
using FrameTime = float;
struct Entity;
//------------------------------------------------------------------------------------
// Globals 
//------------------------------------------------------------------------------------
constexpr int screenWidth{1024}, screenHeight{768};
const string screenTitle{"Shooter - Prototype #2"};
constexpr float blockWidth{3.f}, blockHeight{3.f};
constexpr float countBlocksX{screenWidth / blockWidth},countBlocksY{screenHeight/blockHeight}; 
// Entity mega array
vector<shared_ptr<Entity>> entity;
//------------------------------------------------------------------------------------
// Global Structs
//------------------------------------------------------------------------------------
struct Voxel : RectangleShape { 
    Voxel(float mX, float mY, Color c = Color::White) : color{c}, vel(0,0) {
        setPosition(mX, mY);
        setSize({blockWidth, blockHeight});
        setFillColor(c);
        setOrigin(blockWidth / 2.f, blockHeight / 2.f);
    }
    // member data 
    Vec2 vel;
    Color color;
    optional<int> health; // voxel health
};

struct Entity {
    Entity() : id{entityCount++} {}
    virtual void update(FrameTime ftStep) { /* check for collision */ /* update pos */  }

    virtual void draw() { }
    virtual ~Entity() { }  
    //-----------------------------------------
    // Set position of entity as a whole 
    // ----------------------------------------
    void setPos(Vec2 pos) {
        this->move(pos - this->pos);
    }
    Vec2& getPos() { return pos; }

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
    const size_t& getId() const { return id; }
    //-----------------------------------------
    // Return the entity with the given id 
    // ----------------------------------------
    static shared_ptr<Entity> withId(size_t id) {
        return *find_if(begin(entity),end(entity),
                [&id](const shared_ptr<Entity> & e) 
                { return e->id == id; });
    }
    protected:
    vector<Voxel> vox;
    Vec2 vel;
    private:
    Vec2 pos; // overall position of entity
    static size_t entityCount;
    // is there a way to make this const and make a copy constructor?
    size_t id; 
};
// out of line static initializers
size_t Entity::entityCount = 0;

// Bullet types
struct Bullet : Entity { 
    Bullet(Vec2 vv) : vel{vv} {}
    Vec2 vel;    
    virtual void update(FrameTime ftStep) override { 
        move(ftStep*vel);  
    }
};

struct B1 : Bullet {
    B1(Vec2 pos) : Bullet({0.f,-1.f}) {
        vox.emplace_back(1.f * blockWidth, 0.f * blockHeight, Color(209,181,190,255));
        vox.emplace_back(0.f * blockWidth, 1.f * blockHeight, Color(209,181,190,255));
        vox.emplace_back(1.f * blockWidth, 1.f * blockHeight, Color(209,181,190,255));
        vox.emplace_back(2.f * blockWidth, 1.f * blockHeight, Color(209,181,190,255));
        vox.emplace_back(1.f * blockWidth, 2.f * blockHeight, Color(209,181,190,255));
        setPos(pos);
    }
};

struct B2 : Bullet {
    B2(Vec2 pos) : Bullet({0.f,-1.f}) {
        vox.emplace_back(2.f * blockWidth, 0.f * blockHeight, Color(112,1,209,255));
        vox.emplace_back(3.f * blockWidth, 0.f * blockHeight, Color(112,1,209,255));
        vox.emplace_back(1.f * blockWidth, 1.f * blockHeight, Color(112,1,209,255));
        vox.emplace_back(2.f * blockWidth, 1.f * blockHeight, Color(112,1,209,255));
        vox.emplace_back(3.f * blockWidth, 1.f * blockHeight, Color(112,1,209,255));
        vox.emplace_back(4.f * blockWidth, 1.f * blockHeight, Color(112,1,209,255));
        vox.emplace_back(1.f * blockWidth, 2.f * blockHeight, Color(112,1,209,255));
        vox.emplace_back(4.f * blockWidth, 2.f * blockHeight, Color(112,1,209,255));
        vox.emplace_back(0.f * blockWidth, 3.f * blockHeight, Color(112,1,209,255));
        vox.emplace_back(5.f * blockWidth, 3.f * blockHeight, Color(112,1,209,255));
        setPos(pos);
    }
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
    E1(Vec2 pos) {
        vox.emplace_back(9.f * blockWidth, 0.f * blockHeight, Color::Cyan);
        vox.emplace_back(10.f * blockWidth, 0.f * blockHeight, Color::Cyan);
        vox.emplace_back(11.f * blockWidth, 0.f * blockHeight, Color::Cyan);
        vox.emplace_back(12.f * blockWidth, 0.f * blockHeight, Color::Cyan);
        vox.emplace_back(7.f * blockWidth, 1.f * blockHeight, Color::Cyan);
        vox.emplace_back(8.f * blockWidth, 1.f * blockHeight, Color::Cyan);
        vox.emplace_back(9.f * blockWidth, 1.f * blockHeight, Color::Cyan);
        vox.emplace_back(10.f * blockWidth, 1.f * blockHeight, Color::Cyan);
        vox.emplace_back(11.f * blockWidth, 1.f * blockHeight, Color::Cyan);
        vox.emplace_back(12.f * blockWidth, 1.f * blockHeight, Color::Cyan);
        vox.emplace_back(13.f * blockWidth, 1.f * blockHeight, Color::Cyan);
        vox.emplace_back(14.f * blockWidth, 1.f * blockHeight, Color::Cyan);
        vox.emplace_back(6.f * blockWidth, 2.f * blockHeight, Color::Cyan);
        vox.emplace_back(7.f * blockWidth, 2.f * blockHeight, Color::Cyan);
        vox.emplace_back(8.f * blockWidth, 2.f * blockHeight, Color::Cyan);
        vox.emplace_back(9.f * blockWidth, 2.f * blockHeight, Color::Cyan);
        vox.emplace_back(10.f * blockWidth, 2.f * blockHeight, Color::Cyan);
        vox.emplace_back(11.f * blockWidth, 2.f * blockHeight, Color::Cyan);
        vox.emplace_back(12.f * blockWidth, 2.f * blockHeight, Color::Cyan);
        vox.emplace_back(13.f * blockWidth, 2.f * blockHeight, Color::Cyan);
        vox.emplace_back(14.f * blockWidth, 2.f * blockHeight, Color::Cyan);
        vox.emplace_back(15.f * blockWidth, 2.f * blockHeight, Color::Cyan);
        vox.emplace_back(5.f * blockWidth, 3.f * blockHeight, Color::Cyan);
        vox.emplace_back(6.f * blockWidth, 3.f * blockHeight, Color::Cyan);
        vox.emplace_back(9.f * blockWidth, 3.f * blockHeight, Color::Cyan);
        vox.emplace_back(10.f * blockWidth, 3.f * blockHeight, Color::Cyan);
        vox.emplace_back(11.f * blockWidth, 3.f * blockHeight, Color::Cyan);
        vox.emplace_back(12.f * blockWidth, 3.f * blockHeight, Color::Cyan);
        vox.emplace_back(15.f * blockWidth, 3.f * blockHeight, Color::Cyan);
        vox.emplace_back(16.f * blockWidth, 3.f * blockHeight, Color::Cyan);
        vox.emplace_back(5.f * blockWidth, 4.f * blockHeight, Color::Cyan);
        vox.emplace_back(6.f * blockWidth, 4.f * blockHeight, Color::Cyan);
        vox.emplace_back(7.f * blockWidth, 4.f * blockHeight, Color::Cyan);
        vox.emplace_back(8.f * blockWidth, 4.f * blockHeight, Color::Cyan);
        vox.emplace_back(9.f * blockWidth, 4.f * blockHeight, Color::Cyan);
        vox.emplace_back(10.f * blockWidth, 4.f * blockHeight, Color::Cyan);
        vox.emplace_back(11.f * blockWidth, 4.f * blockHeight, Color::Cyan);
        vox.emplace_back(12.f * blockWidth, 4.f * blockHeight, Color::Cyan);
        vox.emplace_back(13.f * blockWidth, 4.f * blockHeight, Color::Cyan);
        vox.emplace_back(14.f * blockWidth, 4.f * blockHeight, Color::Cyan);
        vox.emplace_back(15.f * blockWidth, 4.f * blockHeight, Color::Cyan);
        vox.emplace_back(16.f * blockWidth, 4.f * blockHeight, Color::Cyan);
        vox.emplace_back(8.f * blockWidth, 5.f * blockHeight, Color::Cyan);
        vox.emplace_back(13.f * blockWidth, 5.f * blockHeight, Color::Cyan);
        vox.emplace_back(7.f * blockWidth, 6.f * blockHeight, Color::Cyan);
        vox.emplace_back(9.f * blockWidth, 6.f * blockHeight, Color::Cyan);
        vox.emplace_back(10.f * blockWidth, 6.f * blockHeight, Color::Cyan);
        vox.emplace_back(11.f * blockWidth, 6.f * blockHeight, Color::Cyan);
        vox.emplace_back(12.f * blockWidth, 6.f * blockHeight, Color::Cyan);
        vox.emplace_back(14.f * blockWidth, 6.f * blockHeight, Color::Cyan);
        vox.emplace_back(6.f * blockWidth, 7.f * blockHeight, Color::Cyan);
        vox.emplace_back(9.f * blockWidth, 7.f * blockHeight, Color::Cyan);
        vox.emplace_back(12.f * blockWidth, 7.f * blockHeight, Color::Cyan);
        vox.emplace_back(15.f * blockWidth, 7.f * blockHeight, Color::Cyan);
        setPos(pos);
    }
};
struct E2: Enemy {
    E2(Vec2 pos) {
        vox.emplace_back(3.f * blockWidth, 0.f * blockHeight, Color::Magenta);
        vox.emplace_back(4.f * blockWidth, 0.f * blockHeight, Color::Magenta);
        vox.emplace_back(17.f * blockWidth, 0.f * blockHeight, Color::Magenta);
        vox.emplace_back(18.f * blockWidth, 0.f * blockHeight, Color::Magenta);
        vox.emplace_back(6.f * blockWidth, 1.f * blockHeight, Color::Magenta);
        vox.emplace_back(16.f * blockWidth, 1.f * blockHeight, Color::Magenta);
        vox.emplace_back(5.f * blockWidth, 2.f * blockHeight, Color::Magenta);
        vox.emplace_back(6.f * blockWidth, 2.f * blockHeight, Color::Magenta);
        vox.emplace_back(7.f * blockWidth, 2.f * blockHeight, Color::Magenta);
        vox.emplace_back(8.f * blockWidth, 2.f * blockHeight, Color::Magenta);
        vox.emplace_back(9.f * blockWidth, 2.f * blockHeight, Color::Magenta);
        vox.emplace_back(10.f * blockWidth, 2.f * blockHeight, Color::Magenta);
        vox.emplace_back(11.f * blockWidth, 2.f * blockHeight, Color::Magenta);
        vox.emplace_back(12.f * blockWidth, 2.f * blockHeight, Color::Magenta);
        vox.emplace_back(13.f * blockWidth, 2.f * blockHeight, Color::Magenta);
        vox.emplace_back(14.f * blockWidth, 2.f * blockHeight, Color::Magenta);
        vox.emplace_back(15.f * blockWidth, 2.f * blockHeight, Color::Magenta);
        vox.emplace_back(16.f * blockWidth, 2.f * blockHeight, Color::Magenta);
        vox.emplace_back(17.f * blockWidth, 2.f * blockHeight, Color::Magenta);
        vox.emplace_back(4.f * blockWidth, 3.f * blockHeight, Color::Magenta);
        vox.emplace_back(5.f * blockWidth, 3.f * blockHeight, Color::Magenta);
        vox.emplace_back(6.f * blockWidth, 3.f * blockHeight, Color::Magenta);
        vox.emplace_back(8.f * blockWidth, 3.f * blockHeight, Color::Magenta);
        vox.emplace_back(9.f * blockWidth, 3.f * blockHeight, Color::Magenta);
        vox.emplace_back(10.f * blockWidth, 3.f * blockHeight, Color::Magenta);
        vox.emplace_back(11.f * blockWidth, 3.f * blockHeight, Color::Magenta);
        vox.emplace_back(12.f * blockWidth, 3.f * blockHeight, Color::Magenta);
        vox.emplace_back(13.f * blockWidth, 3.f * blockHeight, Color::Magenta);
        vox.emplace_back(14.f * blockWidth, 3.f * blockHeight, Color::Magenta);
        vox.emplace_back(16.f * blockWidth, 3.f * blockHeight, Color::Magenta);
        vox.emplace_back(17.f * blockWidth, 3.f * blockHeight, Color::Magenta);
        vox.emplace_back(18.f * blockWidth, 3.f * blockHeight, Color::Magenta);
        vox.emplace_back(2.f * blockWidth, 4.f * blockHeight, Color::Magenta);
        vox.emplace_back(3.f * blockWidth, 4.f * blockHeight, Color::Magenta);
        vox.emplace_back(4.f * blockWidth, 4.f * blockHeight, Color::Magenta);
        vox.emplace_back(5.f * blockWidth, 4.f * blockHeight, Color::Magenta);
        vox.emplace_back(6.f * blockWidth, 4.f * blockHeight, Color::Magenta);
        vox.emplace_back(7.f * blockWidth, 4.f * blockHeight, Color::Magenta);
        vox.emplace_back(8.f * blockWidth, 4.f * blockHeight, Color::Magenta);
        vox.emplace_back(9.f * blockWidth, 4.f * blockHeight, Color::Magenta);
        vox.emplace_back(10.f * blockWidth, 4.f * blockHeight, Color::Magenta);
        vox.emplace_back(11.f * blockWidth, 4.f * blockHeight, Color::Magenta);
        vox.emplace_back(12.f * blockWidth, 4.f * blockHeight, Color::Magenta);
        vox.emplace_back(13.f * blockWidth, 4.f * blockHeight, Color::Magenta);
        vox.emplace_back(14.f * blockWidth, 4.f * blockHeight, Color::Magenta);
        vox.emplace_back(15.f * blockWidth, 4.f * blockHeight, Color::Magenta);
        vox.emplace_back(16.f * blockWidth, 4.f * blockHeight, Color::Magenta);
        vox.emplace_back(17.f * blockWidth, 4.f * blockHeight, Color::Magenta);
        vox.emplace_back(18.f * blockWidth, 4.f * blockHeight, Color::Magenta);
        vox.emplace_back(19.f * blockWidth, 4.f * blockHeight, Color::Magenta);
        vox.emplace_back(20.f * blockWidth, 4.f * blockHeight, Color::Magenta);
        vox.emplace_back(5.f * blockWidth, 5.f * blockHeight, Color::Magenta);
        vox.emplace_back(6.f * blockWidth, 5.f * blockHeight, Color::Magenta);
        vox.emplace_back(7.f * blockWidth, 5.f * blockHeight, Color::Magenta);
        vox.emplace_back(8.f * blockWidth, 5.f * blockHeight, Color::Magenta);
        vox.emplace_back(9.f * blockWidth, 5.f * blockHeight, Color::Magenta);
        vox.emplace_back(10.f * blockWidth, 5.f * blockHeight, Color::Magenta);
        vox.emplace_back(11.f * blockWidth, 5.f * blockHeight, Color::Magenta);
        vox.emplace_back(12.f * blockWidth, 5.f * blockHeight, Color::Magenta);
        vox.emplace_back(13.f * blockWidth, 5.f * blockHeight, Color::Magenta);
        vox.emplace_back(14.f * blockWidth, 5.f * blockHeight, Color::Magenta);
        vox.emplace_back(15.f * blockWidth, 5.f * blockHeight, Color::Magenta);
        vox.emplace_back(16.f * blockWidth, 5.f * blockHeight, Color::Magenta);
        vox.emplace_back(17.f * blockWidth, 5.f * blockHeight, Color::Magenta);
        vox.emplace_back(5.f * blockWidth, 6.f * blockHeight, Color::Magenta);
        vox.emplace_back(17.f * blockWidth, 6.f * blockHeight, Color::Magenta);
        vox.emplace_back(6.f * blockWidth, 7.f * blockHeight, Color::Magenta);
        vox.emplace_back(7.f * blockWidth, 7.f * blockHeight, Color::Magenta);
        vox.emplace_back(8.f * blockWidth, 7.f * blockHeight, Color::Magenta);
        vox.emplace_back(9.f * blockWidth, 7.f * blockHeight, Color::Magenta);
        vox.emplace_back(14.f * blockWidth, 7.f * blockHeight, Color::Magenta);
        vox.emplace_back(15.f * blockWidth, 7.f * blockHeight, Color::Magenta);
        vox.emplace_back(16.f * blockWidth, 7.f * blockHeight, Color::Magenta);
        vox.emplace_back(17.f * blockWidth, 7.f * blockHeight, Color::Magenta);
        setPos(pos);
    }
};
struct E3: Enemy {
    E3(Vec2 pos) {
        vox.emplace_back(9.f * blockWidth, 0.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(10.f * blockWidth, 0.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(11.f * blockWidth, 0.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(12.f * blockWidth, 0.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(13.f * blockWidth, 0.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(5.f * blockWidth, 1.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(6.f * blockWidth, 1.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(7.f * blockWidth, 1.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(8.f * blockWidth, 1.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(9.f * blockWidth, 1.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(10.f * blockWidth, 1.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(11.f * blockWidth, 1.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(12.f * blockWidth, 1.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(13.f * blockWidth, 1.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(14.f * blockWidth, 1.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(15.f * blockWidth, 1.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(16.f * blockWidth, 1.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(4.f * blockWidth, 2.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(5.f * blockWidth, 2.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(6.f * blockWidth, 2.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(7.f * blockWidth, 2.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(8.f * blockWidth, 2.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(9.f * blockWidth, 2.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(10.f * blockWidth, 2.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(11.f * blockWidth, 2.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(12.f * blockWidth, 2.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(13.f * blockWidth, 2.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(14.f * blockWidth, 2.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(15.f * blockWidth, 2.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(16.f * blockWidth, 2.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(17.f * blockWidth, 2.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(18.f * blockWidth, 2.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(4.f * blockWidth, 3.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(5.f * blockWidth, 3.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(6.f * blockWidth, 3.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(9.f * blockWidth, 3.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(10.f * blockWidth, 3.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(11.f * blockWidth, 3.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(12.f * blockWidth, 3.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(13.f * blockWidth, 3.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(16.f * blockWidth, 3.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(17.f * blockWidth, 3.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(18.f * blockWidth, 3.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(4.f * blockWidth, 4.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(5.f * blockWidth, 4.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(6.f * blockWidth, 4.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(7.f * blockWidth, 4.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(8.f * blockWidth, 4.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(9.f * blockWidth, 4.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(10.f * blockWidth, 4.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(11.f * blockWidth, 4.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(12.f * blockWidth, 4.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(13.f * blockWidth, 4.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(14.f * blockWidth, 4.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(15.f * blockWidth, 4.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(16.f * blockWidth, 4.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(17.f * blockWidth, 4.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(18.f * blockWidth, 4.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(6.f * blockWidth, 5.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(7.f * blockWidth, 5.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(8.f * blockWidth, 5.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(14.f * blockWidth, 5.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(15.f * blockWidth, 5.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(16.f * blockWidth, 5.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(5.f * blockWidth, 6.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(6.f * blockWidth, 6.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(7.f * blockWidth, 6.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(15.f * blockWidth, 6.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(16.f * blockWidth, 6.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(17.f * blockWidth, 6.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(3.f * blockWidth, 7.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(4.f * blockWidth, 7.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(5.f * blockWidth, 7.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(17.f * blockWidth, 7.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(18.f * blockWidth, 7.f * blockHeight, Color::Red + Color::Yellow);
        vox.emplace_back(19.f * blockWidth, 7.f * blockHeight, Color::Red + Color::Yellow);
        setPos(pos);
    }
};
struct E4: Enemy {
    E4(Vec2 pos) {
        vox.emplace_back(9.f * blockWidth, 0.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(10.f * blockWidth, 0.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(11.f * blockWidth, 0.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(12.f * blockWidth, 0.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(13.f * blockWidth, 0.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(14.f * blockWidth, 0.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(15.f * blockWidth, 0.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(16.f * blockWidth, 0.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(17.f * blockWidth, 0.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(18.f * blockWidth, 0.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(19.f * blockWidth, 0.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(6.f * blockWidth, 1.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(7.f * blockWidth, 1.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(8.f * blockWidth, 1.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(9.f * blockWidth, 1.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(10.f * blockWidth, 1.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(11.f * blockWidth, 1.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(12.f * blockWidth, 1.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(13.f * blockWidth, 1.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(14.f * blockWidth, 1.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(15.f * blockWidth, 1.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(16.f * blockWidth, 1.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(17.f * blockWidth, 1.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(18.f * blockWidth, 1.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(19.f * blockWidth, 1.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(20.f * blockWidth, 1.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(21.f * blockWidth, 1.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(22.f * blockWidth, 1.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(23.f * blockWidth, 1.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(4.f * blockWidth, 2.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(5.f * blockWidth, 2.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(6.f * blockWidth, 2.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(7.f * blockWidth, 2.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(8.f * blockWidth, 2.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(9.f * blockWidth, 2.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(10.f * blockWidth, 2.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(11.f * blockWidth, 2.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(12.f * blockWidth, 2.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(13.f * blockWidth, 2.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(14.f * blockWidth, 2.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(15.f * blockWidth, 2.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(16.f * blockWidth, 2.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(17.f * blockWidth, 2.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(18.f * blockWidth, 2.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(19.f * blockWidth, 2.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(20.f * blockWidth, 2.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(21.f * blockWidth, 2.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(22.f * blockWidth, 2.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(23.f * blockWidth, 2.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(24.f * blockWidth, 2.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(25.f * blockWidth, 2.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(3.f * blockWidth, 3.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(4.f * blockWidth, 3.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(5.f * blockWidth, 3.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(6.f * blockWidth, 3.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(8.f * blockWidth, 3.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(9.f * blockWidth, 3.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(10.f * blockWidth, 3.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(11.f * blockWidth, 3.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(13.f * blockWidth, 3.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(14.f * blockWidth, 3.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(15.f * blockWidth, 3.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(16.f * blockWidth, 3.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(18.f * blockWidth, 3.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(19.f * blockWidth, 3.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(20.f * blockWidth, 3.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(21.f * blockWidth, 3.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(23.f * blockWidth, 3.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(24.f * blockWidth, 3.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(25.f * blockWidth, 3.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(26.f * blockWidth, 3.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(0.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(1.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(2.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(3.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(4.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(5.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(6.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(7.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(8.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(9.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(10.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(11.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(12.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(13.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(14.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(15.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(16.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(17.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(18.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(19.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(20.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(21.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(22.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(23.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(24.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(25.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(26.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(27.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(28.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(29.f * blockWidth, 4.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(5.f * blockWidth, 5.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(6.f * blockWidth, 5.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(7.f * blockWidth, 5.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(8.f * blockWidth, 5.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(9.f * blockWidth, 5.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(13.f * blockWidth, 5.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(14.f * blockWidth, 5.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(15.f * blockWidth, 5.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(16.f * blockWidth, 5.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(20.f * blockWidth, 5.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(21.f * blockWidth, 5.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(22.f * blockWidth, 5.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(23.f * blockWidth, 5.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(24.f * blockWidth, 5.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(7.f * blockWidth, 6.f * blockHeight, Color(255,140,0,245));
        vox.emplace_back(22.f * blockWidth, 6.f * blockHeight, Color(255,140,0,245));
        setPos(pos);
    }
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



struct Game {
    // These members are related to the control of the game.
    RenderWindow window{{screenWidth, screenHeight}, screenTitle};
    FrameTime lastFt{0.f}, currentSlice{0.f};
    FrameTime ftStep{1.f}, ftSlice{1.f};
    bool gameOver{false}, pause{false};

    // These members are game entities.
    unsigned int levelId{1};

    //-----------------------------------------
    // Game construction 
    // ----------------------------------------
    Game() {
        gameOver = false;
        window.setFramerateLimit(150);
        // create the player
        entity.push_back(make_shared<Player>(Vec2(3.f*screenWidth / 4.f, screenHeight - 20.f))); 
        // Load level 1
        entity.push_back(make_shared<E1>(Vec2(1.f*screenWidth / 6.f, 1.f * screenHeight / 8.f)));
        entity.push_back(make_shared<E2>(Vec2(2.f*screenWidth / 6.f, 1.f * screenHeight / 8.f)));
        entity.push_back(make_shared<E3>(Vec2(3.f*screenWidth / 6.f, 1.f * screenHeight / 8.f)));
        entity.push_back(make_shared<E4>(Vec2(4.f*screenWidth / 6.f, 1.f * screenHeight / 8.f)));
    }
    //-----------------------------------------
    // Input phase : called every frame
    // ----------------------------------------
    void inputPhase() {
        Event event;
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
                break;
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::Key::Escape)) gameOver = true;
        if(Keyboard::isKeyPressed(Keyboard::Key::Left)) { 
            Entity::withId(0)->move({ftStep * -8.f,0.f}); 
        }
        if(Keyboard::isKeyPressed(Keyboard::Key::Right)) { 
            Entity::withId(0)->move({ftStep * +8.f,0.f}); 
        }
        if(Keyboard::isKeyPressed(Keyboard::Key::Space)) { 
            entity.push_back(make_shared<B1>(Entity::withId(0)->getPos()));
        }
        if(Keyboard::isKeyPressed(Keyboard::Key::LShift)) { 
            entity.push_back(make_shared<B2>(Entity::withId(0)->getPos()));
        }
    }

    //-----------------------------------------
    // Update phase 
    // ----------------------------------------
    void updatePhase() {
        window.clear(Color::Black);
        // Update using ftStep for framerate 
        // independent gameplay
        for(auto & e  : entity) { e->update(ftStep); }
    }

    //-----------------------------------------
    // Draw phase 
    // ----------------------------------------
    void drawPhase() {
        for(auto & e  : entity) {
            for (auto & v : e->getVox()) {
                window.draw(v);
            }
        }
        window.display();
    }
    //-----------------------------------------
    // Run phase 
    // ----------------------------------------
    void Run() {
        while(!gameOver)
        {
            auto timePoint1(chrono::high_resolution_clock::now());

            inputPhase();

            currentSlice += lastFt;
            for(; currentSlice >= ftSlice; currentSlice -= ftSlice) {
                updatePhase();
                // check for collisions
                // remove dead entities
            }
            drawPhase();
            // calculate FPS 
            auto timePoint2(chrono::high_resolution_clock::now());
            auto elapsedTime(timePoint2 - timePoint1);
            FrameTime ft{chrono::duration_cast<chrono::duration<float, milli>>(
                    elapsedTime)
                .count()};
            lastFt = ft;

            auto fSeconds = ft / 1000.f;
            auto fps = 1.f / fSeconds;
            auto fps2 = static_cast<int>(round(fps));
            window.setTitle(screenTitle + " FPS: " + to_string(fps2));
        }
    }

};

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    Game{}.Run();
    return 0;
}
