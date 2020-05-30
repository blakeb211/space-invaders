#include "stdlibs.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;
using Vec2 = Vector2<float>; 
struct Entity;
//------------------------------------------------------------------------------------
// Globals 
//------------------------------------------------------------------------------------
constexpr int screenWidth{1024}, screenHeight{768};
constexpr float blockWidth{4.f}, blockHeight{4.f};
constexpr float countBlocksX{screenWidth / blockWidth},countBlocksY{screenHeight/blockHeight}; 
static bool gameOver{false};
static bool pause{false};
// Mega Entity Array
vector<shared_ptr<Entity>> entity;
unsigned int levelId = 1;

//------------------------------------------------------------------------------------
// Global Structs
//------------------------------------------------------------------------------------
// TODO: Inherit from SFML RectangleShape
struct Voxel { 
    Voxel(float mX, float mY, Color c = Color::White) : color{c}, vel(0,0) {
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
    Entity() : id{entityCount++} {}
    virtual void update() { /* check for collision */ pos += vel;/* update pos */  }

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
        return *find_if(begin(entity),end(entity),[&id](const shared_ptr<Entity> & e) { return e->id == id; });
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
    virtual void update() override { }
};

struct B1 : Bullet {
    B1(Vec2 pos) : Bullet({0.f,-3.f}) {
        vox.emplace_back(1.f * blockWidth, 0.f * blockHeight, Color(209,181,190,255));
        vox.emplace_back(0.f * blockWidth, 1.f * blockHeight, Color(209,181,190,255));
        vox.emplace_back(1.f * blockWidth, 1.f * blockHeight, Color(209,181,190,255));
        vox.emplace_back(2.f * blockWidth, 1.f * blockHeight, Color(209,181,190,255));
        vox.emplace_back(1.f * blockWidth, 2.f * blockHeight, Color(209,181,190,255));
        setPos(pos);
    }
    virtual void update() override {
        move(vel);  
    }
};

struct B2 : Bullet {
    B2(Vec2 pos) : Bullet({0.f,-3.f}) {
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
    virtual void update() override {
        move(vel);  
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

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    RenderWindow window{{screenWidth, screenHeight}, "Shooter - Prototype #2"};
    window.setFramerateLimit(100);
    //-----------------------------------------
    // Create the player 
    // ----------------------------------------
    entity.push_back(make_shared<Player>(Vec2(3.f*screenWidth / 4.f, screenHeight - 20.f))); 
    entity.push_back(make_shared<E1>(Vec2(1.f*screenWidth / 6.f, 1.f * screenHeight / 8.f)));
    entity.push_back(make_shared<E2>(Vec2(2.f*screenWidth / 6.f, 1.f * screenHeight / 8.f)));
    entity.push_back(make_shared<E3>(Vec2(3.f*screenWidth / 6.f, 1.f * screenHeight / 8.f)));
    entity.push_back(make_shared<E4>(Vec2(4.f*screenWidth / 6.f, 1.f * screenHeight / 8.f)));
    while(true)
    {
        window.clear(Color::Black);

        if(Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;
        if(Keyboard::isKeyPressed(Keyboard::Key::Left)) { 
            Entity::withId(0)->move({-10.f,0.f}); 
        }
        if(Keyboard::isKeyPressed(Keyboard::Key::Right)) { 
            Entity::withId(0)->move({+10.f,0.f}); 
        }
        if(Keyboard::isKeyPressed(Keyboard::Key::Space)) { 
            entity.push_back(make_shared<B1>(Entity::withId(0)->getPos()));
        }

        for(auto & e  : entity) {
            e->update();
            for (auto & v : e->getVox()) {
                window.draw(v.shape);
            }
        }
        window.display();
    }
    return 0;
}
