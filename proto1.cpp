#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "stdlibs.h"
#include "globals.h"
#include "builder.h" 

using namespace std;
using namespace sf;
using Vec2 = Vector2<float>; 
using FrameTime = float;

struct Entity;
//------------------------------------------------------------------------------------
// Globals 
//------------------------------------------------------------------------------------
vector<shared_ptr<Entity>> entity;
//------------------------------------------------------------------------------------
// Global Structs
//------------------------------------------------------------------------------------

struct Entity {
  //-----------------------------------------
  // Constructor 
  // ----------------------------------------
  Entity() : id{entityCount++}, destroyed{false} {}
  virtual void update(FrameTime ftStep) { /* check for collision */ /* update pos */  }
  //-----------------------------------------
  // Destructor 
  // ----------------------------------------
  virtual ~Entity() { }  
  //-----------------------------------------
  // Set position of entity as a whole 
  // ----------------------------------------
  void setPos(Vec2 pos) {
    this->move(pos - this->pos);
  }
  //-----------------------------------------
  // Return position of entity as a whole
  // ----------------------------------------
  Vec2& getPos() { return pos; }
  //-----------------------------------------
  // Move all voxels by an offset
  // ----------------------------------------
  virtual void move(Vec2 offset) { 
    this->pos += offset;
    for(auto &v : vox) { 
      v.move(offset); }
  }
  //-----------------------------------------
  // Return the voxel vector  
  // ----------------------------------------
  vector<Voxel>& getVox() { return vox; }
  //-----------------------------------------
  // Entity health is the voxel count 
  // ----------------------------------------
  virtual size_t getHealth() const { return vox.size(); }
  //-----------------------------------------
  // Return the entity id  
  // ----------------------------------------
  const size_t& getId() const { return id; }
  //-----------------------------------------
  // Return the entity with the given id 
  // ----------------------------------------
  static shared_ptr<Entity> withId(size_t id) {
    return *find_if(begin(entity),end(entity),
        [&id](const shared_ptr<Entity> & e) 
        { return e->id == id; });
  }
  bool destroyed;
  protected:
  vector<Voxel> vox;
  Vec2 vel;
  Vec2 pos; // overall position of entity
  size_t id; 
  private:
  static size_t entityCount;
  // is there a way to make this const and make a copy constructor?
};
// out of line static initializers
size_t Entity::entityCount = 0;

// Bullet types
struct Bullet : Entity { 
  Bullet(Vec2 vv) : vel{vv} {}
  Vec2 vel;    
  virtual void update(FrameTime ftStep) override { 
    move(ftStep*vel);  
    // mark for destruction if go off screen
    if (pos.x < 0 || pos.x > G::screenWidth || pos.y < 0 || pos.y > G::screenHeight) {
      destroyed = true;
    }
  }
};

struct B1 : Bullet {
  B1(Vec2 pos) : Bullet({0.f,-1.f}) {
    Builder::build_B1(vox);
    setPos(pos);
  }
};

struct B2 : Bullet {
  B2(Vec2 pos) : Bullet({0.f,-1.f}) {
    Builder::build_B2(vox);
    setPos(pos);
  }
};

struct Player : public Entity {
  Player(Vec2 pos) : mTimerMax{30.f}, mTimer{0.f}, mCanShoot{false} {
    Builder::build_player(vox);
    setPos(pos);
  }
  virtual void update(FrameTime ftStep) override {
    mTimer += ftStep; 
    if (mTimer > mTimerMax) {
      mTimer = 0.f;
      mCanShoot = true;
    }
  }
  bool mCanShoot;
  float mTimer;
  const float mTimerMax;
};
// Enemy types
struct Enemy: Entity { // base
  vector<Vec2> path;
};

struct E1: Enemy {
  E1(Vec2 pos) {
    Builder::build_E1(vox);
    setPos(pos);
  }
};
struct E2: Enemy {
  E2(Vec2 pos) {
    Builder::build_E2(vox);
    setPos(pos);
  }
};
struct E3: Enemy {
  E3(Vec2 pos) {
    Builder::build_E3(vox);
    setPos(pos);
  }
};
struct E4: Enemy {
  E4(Vec2 pos) {
    Builder::build_E4(vox);
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

void removeDestroyedEntities(vector<shared_ptr<Entity>> & vec) {
  // TODO: consider a threshold for different entity types
  vec.erase(remove_if(begin(vec), end(vec), [] (const shared_ptr<Entity> & e) { return e->destroyed; }), end(vec));
}

struct Game {
  // These members are related to the control of the game.
  RenderWindow window{{G::screenWidth, G::screenHeight}, G::screenTitle};
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
    window.setFramerateLimit(80);
    // create the player
    entity.push_back(make_shared<Player>(Vec2(3.f*G::screenWidth / 4.f, G::screenHeight - 20.f))); 
    // Load level 1
    entity.push_back(make_shared<E1>(Vec2(1.f*G::screenWidth / 6.f, 1.f * G::screenHeight / 8.f)));
    entity.push_back(make_shared<E2>(Vec2(2.f*G::screenWidth / 6.f, 1.f * G::screenHeight / 8.f)));
    entity.push_back(make_shared<E3>(Vec2(3.f*G::screenWidth / 6.f, 1.f * G::screenHeight / 8.f)));
    entity.push_back(make_shared<E4>(Vec2(4.f*G::screenWidth / 6.f, 1.f * G::screenHeight / 8.f)));
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
      Entity::withId(0)->move({ftStep * -11.f,0.f}); 
    }
    if(Keyboard::isKeyPressed(Keyboard::Key::Right)) { 
      Entity::withId(0)->move({ftStep * +11.f,0.f}); 
    }
    if(Keyboard::isKeyPressed(Keyboard::Key::Space)) { 
      // player shoot
      shared_ptr<Player> p_ptr = dynamic_pointer_cast<Player> (Entity::withId(0));
      if (p_ptr->mCanShoot) {
        entity.push_back(make_shared<B1>(p_ptr->getPos()));
        p_ptr->mCanShoot = false;
      }
    }
    if(Keyboard::isKeyPressed(Keyboard::Key::LShift)) { 
      // player shoot 
      shared_ptr<Player> p_ptr = dynamic_pointer_cast<Player> (Entity::withId(0));
      if (p_ptr->mCanShoot) {
        entity.push_back(make_shared<B2>(Entity::withId(0)->getPos()));
        p_ptr->mCanShoot = false;
      }
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
        removeDestroyedEntities(entity);
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
      window.setTitle(G::screenTitle + " FPS: " + to_string(fps2));
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
