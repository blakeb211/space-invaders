#include "globals.h"
#include "builder.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
using namespace std;
using namespace sf;
using Vec2 = Vector2<float>;
//-----------------------------------------
// Constructor 
// ----------------------------------------
Entity::Entity() : id{entityCount++}, destroyed{false}, hasDeadVoxel{false} {}
void Entity::update(FrameTime ftStep) { /* check for collision */ /* update pos */  }

void Entity::collideWith(EntityType et, unsigned int ivox) {
}
//-----------------------------------------
// Destructor 
// ----------------------------------------
Entity::~Entity() { }  
//-----------------------------------------
// Set position of entity as a whole 
// ----------------------------------------
void Entity::setPos(Vec2 pos) {
    this->move(pos - this->pos);
}
//-----------------------------------------
// Return position of entity as a whole
// ----------------------------------------
Vec2 Entity::getPos() const { return pos; }
//-----------------------------------------
// Move all voxels by an offset
// ----------------------------------------
void Entity::move(Vec2 offset) { 
    this->pos += offset;
    for(auto &v : vox) { 
        v.move(offset); }
}
//-----------------------------------------
// Return the pos + the origin = center 
// This fxn is only used for prefiltering
// the collision system
// ----------------------------------------
Vec2 Entity::getCenter() const {
    return Vec2(pos.x - origin.x, pos.y + origin.y); 
}
//-----------------------------------------
// Reset Origin: avg of min+max x and y
// ----------------------------------------
void Entity::resetOrigin() {
    set<int> x_coords {};
    set<int> y_coords {};
    Vec2 _pos;
    for(auto const &v : vox) {
        pos = v.getPosition();
        x_coords.insert(pos.x);
        y_coords.insert(pos.y);
    }
    auto minmax_x = minmax_element(x_coords.begin(), x_coords.end());
    auto minmax_y = minmax_element(y_coords.begin(), y_coords.end());
    origin.x = (*minmax_x.second - *minmax_x.first) / 2.f;
    origin.y = (*minmax_y.first - *minmax_y.second) / 2.f;
}
//-----------------------------------------
// Return the voxel vector  
// ----------------------------------------
vector<Voxel>& Entity::getVox() { return vox; }
//-----------------------------------------
// Erase one dead voxel is hasDeadVoxel flag
// is set
// ----------------------------------------
void Entity::eraseDeadVoxel() {
    if (o_type == EntityType::Wall1) return; 
    vox.erase(remove_if(begin(vox), end(vox), [] (const Voxel & v) { return *v.health <= 0;  }), end(vox));
    // add a voxel destruction animation
}
//-----------------------------------------
// Entity health is the voxel count 
// ----------------------------------------
size_t Entity::getHealth() const { return vox.size(); }
//-----------------------------------------
// Return the entity id  
// ----------------------------------------
const size_t& Entity::getId() const { return id; }
//-----------------------------------------
// Static method: Return the entity with the given id 
// ----------------------------------------
shared_ptr<Entity> Entity::withId(size_t id) {
    return *find_if(begin(G::entity),end(G::entity),
            [&id](const shared_ptr<Entity> & e) 
            { return e->id == id; });
}

//-----------------------------------------
// Static method: Set health of each voxel 
// ----------------------------------------
void Entity::setVoxelHealth(Entity & e, optional<unsigned int> health) { 
    if (e.vox.size() == 0) 
        throw exception("tried to set health of entity with 0 voxels");
    for(auto & v : e.vox) {
        v.health = health;
    }
}


// out of line static initializers
size_t Entity::entityCount = 0;

// Bullet types
Bullet::Bullet(Vec2 vv) : vel{vv} {
    o_type = EntityType::Bullet;
}

void Bullet::update(FrameTime ftStep){ 
    move(ftStep*vel);  
    move(ftStep*dvel);
    // mark for destruction if go off screen
    if (pos.x < 0 || pos.x > G::screenWidth || pos.y < 0 || pos.y > G::screenHeight) {
        destroyed = true;
    }
}

//-----------------------------------------
// Handle bullet collisions 
// ----------------------------------------
void Bullet::collideWith(EntityType et, unsigned int ivox) { 
    vox[ivox].setFillColor(sf::Color::Red);
    float xvel =((float)(0 + rand() % 12) - 6.0f) / 10.f;
    float yvel = +0.2f;
    dvel = Vec2(xvel, yvel); 
    *(vox[ivox].health) -= 1;
    // kill voxel elsewhere
}

B1::B1(Vec2 pos) : Bullet({0.f,-G::kBulletSpeed}) {
    Builder::build_B1(vox);
    resetOrigin();
    //vox.emplace_back(getCenter().x, getCenter().y, Color::Blue);
    setPos(pos);
    Entity::setVoxelHealth(*this, 1);
}

B2::B2(Vec2 pos) : Bullet({0.f,-G::kBulletSpeed}) {
    Builder::build_B2(vox);
    resetOrigin();
    //vox.emplace_back(getCenter().x, getCenter().y, Color::Blue);
    setPos(pos);
    Entity::setVoxelHealth(*this, 1);
}
B3::B3(Vec2 pos) : Bullet({0.f,-G::kBulletSpeed}) {
    Builder::build_B3(vox);
    resetOrigin();
    vox.emplace_back(getCenter().x, getCenter().y, Color::Blue);
    setPos(pos);
    // set bullet 3 voxel health
}

// Player methods
Player::Player(Vec2 pos) : mTimerMax{100.f}, mTimer{0.f}, mCanShoot{false}  {
    o_type = EntityType::Player;
    Builder::build_player(vox);
    resetOrigin();
    //vox.emplace_back(getCenter().x, getCenter().y, Color::Blue);
    setPos(pos);
    Entity::setVoxelHealth(*this, 5);
}

void Player::update(FrameTime ftStep) {
    mTimer += ftStep; 
    if (mTimer > mTimerMax) {
        mTimer = 0.f;
        mCanShoot = true;
    }
}

void Player::collideWith(EntityType et, unsigned int ivox) { 
    vox[ivox].setFillColor(sf::Color::Red);
    *(vox[ivox].health) -= 1;
    // kill voxel elsewhere
}
// Enemy types
Enemy::Enemy() : currPathPoint{0} {
    o_type = EntityType::Enemy;
}

void Enemy::update(FrameTime ftStep) {
    auto _pos = getPos();
    auto pathPoint = path[currPathPoint];
    float dist2goal = sqrt(pow(_pos.x - pathPoint.x,2) + pow(_pos.y - pathPoint.y,2));
    if (dist2goal < 3.f) {
        if (currPathPoint == path.size() - 1)
        {
            // move from last path point to first path point
            currPathPoint = 0; 
        }
        else {
            currPathPoint++;
        }
        pathPoint = path[currPathPoint];
    }
    auto moveDir = pathPoint - _pos;
    float length = sqrt(pow(moveDir.x,2) + pow(moveDir.y,2));
    auto unitVec = Vec2(moveDir.x / length, moveDir.y / length);
    float slowDownFactor = 0.15f;
    // move in direction of next goal position
    move(unitVec * slowDownFactor * ftStep); 
    // move by dvel, which dampens to 0 over time, as well
    move(dvel*ftStep);
}

void Enemy::collideWith(EntityType et, unsigned int ivox) {
    vox[ivox].setFillColor(sf::Color::Red);
    *(vox[ivox].health) -= 1;
    // kill voxel elsewhere
}

E1::E1(Vec2 pos) : Enemy() {
    Builder::build_E1(vox);
    resetOrigin();
    //vox.emplace_back(getCenter().x, getCenter().y, Color::Blue);
    setPos(pos);
    Entity::setVoxelHealth(*this, 2);
}

E2::E2(Vec2 pos) : Enemy() {
    Builder::build_E2(vox);
    resetOrigin();
    //vox.emplace_back(getCenter().x, getCenter().y, Color::Blue);
    setPos(pos);
    Entity::setVoxelHealth(*this, 2);
    //set all voxels to a fixed health value
}

E3::E3(Vec2 pos) : Enemy() {
    Builder::build_E3(vox);
    resetOrigin();
    //vox.emplace_back(getCenter().x, getCenter().y, Color::Blue);
    setPos(pos);
    Entity::setVoxelHealth(*this, 4);
    //set all voxels to a fixed health value
}

E4::E4(Vec2 pos) : Enemy() {
    Builder::build_E4(vox);
    resetOrigin();
    //vox.emplace_back(getCenter().x, getCenter().y, Color::Blue);
    setPos(pos);
    Entity::setVoxelHealth(*this, 4);
    //set all voxels to a fixed health value
}

// Wall types
Wall1::Wall1(Vec2 start, Vec2 end) {
    o_type = EntityType::Wall1;
    Builder::build_wall1(start, end, vox);
    resetOrigin();
    setPos(pos);
    vox.emplace_back(getCenter().x, getCenter().y, Color::Blue);
    // This is a bouncy wall so health == nullopt
    Entity::setVoxelHealth(*this, nullopt);
}

void Wall1::update(FrameTime ftStep) {
}

void Wall1::collideWith(EntityType et, unsigned int ivox) {
    vox[ivox].setFillColor(sf::Color::Green);
    // this is a bouncy wall for bullets
}

void Wall2::update(FrameTime ftStep) {
}

void Wall2::collideWith(EntityType et, unsigned int ivox) {
    vox[ivox].setFillColor(sf::Color::Red);
    *(vox[ivox].health) -= 1;
    // kill voxel elsewhere
}
