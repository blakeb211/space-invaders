#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "stdlibs.h"
#include "voxel.h"

using Vec2 = sf::Vector2<float>;
using FrameTime = float;
//------------------------------------------------------------------------------------
// Enums 
//------------------------------------------------------------------------------------
enum struct EntityType { Player = 1, Bullet = 2, Wall1 = 3, Wall2 = 4, Enemy = 5 };
//------------------------------------------------------------------------------------
// Structs 
//------------------------------------------------------------------------------------
struct Entity {
  //-----------------------------------------
  // Constructor 
  // ----------------------------------------
  Entity();
  virtual void update(FrameTime ftStep); 
  //-----------------------------------------
  // Destructor 
  // ----------------------------------------
  virtual ~Entity();
  //-----------------------------------------
  // Set position of entity as a whole 
  // ----------------------------------------
  void setPos(Vec2 pos); 
  virtual void collideWith(Entity& e, unsigned int ivox, Vec2 voxPos);
  //-----------------------------------------
  // Erase a voxel 
  // ----------------------------------------
  void eraseDeadVoxel();
  //-----------------------------------------
  // Return position of entity as a whole
  // ----------------------------------------
  Vec2 getPos() const; 
  //-----------------------------------------
  // Return center of entity as whole
  // ----------------------------------------
  Vec2 getCenter() const; 
  //-----------------------------------------
  // Reset Origin: avg of min+max x and y
  // ----------------------------------------
  void resetOrigin(); 
  //-----------------------------------------
  // Move all voxels by an offset
  // ----------------------------------------
  virtual void move(Vec2 offset);  
  //-----------------------------------------
  // Return the voxel vector  
  // ----------------------------------------
  std::vector<Voxel>& getVox();
  //-----------------------------------------
  // Entity health is the voxel count 
  // ----------------------------------------
  virtual size_t getHealth() const; 
  //-----------------------------------------
  // Return the entity id  
  // ----------------------------------------
  const size_t& getId() const;
  //-----------------------------------------
  // Return the entity with the given id 
  // ----------------------------------------
  static std::shared_ptr<Entity> withId(size_t id); 
  //-----------------------------------------
  // Set health of each voxel 
  // ----------------------------------------
  static void setVoxelHealth(Entity & e, std::optional<unsigned int> health); 
  bool destroyed;
  bool hasDeadVoxel;
  EntityType o_type;
  Vec2 vel;
  Vec2 dvel;
  protected:
  std::vector<Voxel> vox;
  Vec2 pos; // overall position of entity
  Vec2 origin; // add this to pos when returning the center of the entity
  // is there a way to make this const and make a copy constructor?
  size_t id; 
  private:
  static size_t entityCount; // defined in cpp file
};

// Bullet types
struct Bullet : Entity { 
  Bullet(Vec2 vv);
  Vec2 vel;    
  virtual void update(FrameTime ftStep) override;  
  virtual void collideWith(Entity& e, unsigned int ivox, Vec2 voxPos) override;
};

struct B1 : Bullet {
  B1(Vec2 pos);
};

struct B2 : Bullet {
  B2(Vec2 pos);
};

struct B3 : Bullet {
  B3(Vec2 pos);
};

struct Player : public Entity {
  Player(Vec2 pos); 
  virtual void update(FrameTime ftStep) override;
  virtual void collideWith(Entity& e, unsigned int ivox, Vec2 voxPos) override;
  bool mCanShoot;
  float mTimer;
  const float mTimerMax; // reload timer
};

// Enemy types
struct Enemy: Entity { // base
  Enemy();
  virtual void update(FrameTime ftStep) override;
  virtual void collideWith(Entity& e, unsigned int ivox, Vec2 voxPos) override;
  std::vector<Vec2> path;
  unsigned int currPathPoint;
};

struct E1: Enemy {
  E1(Vec2 pos); 
};

struct E2: Enemy {
  E2(Vec2 pos); 
};

struct E3: Enemy {
  E3(Vec2 pos); 
};

struct E4: Enemy {
  E4(Vec2 pos);
};

// Wall types - they do not have a position
struct Wall : Entity { // base
};

struct Wall1 : Wall { // bouncy wall 
    Wall1(Vec2 start, Vec2 end);
    virtual void update(FrameTime ftStep) override; // test for collision 
    virtual void collideWith(Entity& e, unsigned int ivox, Vec2 voxPos) override;
};

struct Wall2 : Wall { // destructible wall
    virtual void update(FrameTime ftStep) override; // test for collision 
    virtual void collideWith(Entity& e, unsigned int ivox, Vec2 voxPos) override;
};
