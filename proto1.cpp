#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "stdlibs.h"
#include "entity.h"
#include "globals.h"
#include "builder.h" 

using namespace std;
using namespace sf;
using Vec2 = Vector2<float>; 
using FrameTime = float;

//------------------------------------------------------------------------------------
// Globals 
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
// Global Structs
//------------------------------------------------------------------------------------

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
    G::entity.push_back(make_shared<Player>(Vec2(3.f*G::screenWidth / 4.f, G::screenHeight - 20.f))); 
    // Load level
    Builder::build_level(levelId);
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
        G::entity.push_back(make_shared<B1>(p_ptr->getPos()));
        p_ptr->mCanShoot = false;
      }
    }
    if(Keyboard::isKeyPressed(Keyboard::Key::LShift)) { 
      // player shoot 
      shared_ptr<Player> p_ptr = dynamic_pointer_cast<Player> (Entity::withId(0));
      if (p_ptr->mCanShoot) {
        G::entity.push_back(make_shared<B2>(Entity::withId(0)->getPos()));
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
    for(auto & e  : G::entity) { e->update(ftStep); }
  }

  //-----------------------------------------
  // Draw phase 
  // ----------------------------------------
  void drawPhase() {
    for(auto & e  : G::entity) {
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
        removeDestroyedEntities(G::entity);
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
