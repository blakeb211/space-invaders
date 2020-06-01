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
// Global Functions
//------------------------------------------------------------------------------------
template<class T1, class T2> bool isIntersecting(T1& a, T2& b) {
  return true;
}

void testCollision(Entity &e1, Entity &e2) {
  if (!isIntersecting(e1, e2)) return;
  // handle collision
}
<<<<<<< HEAD

<<<<<<< HEAD
void removeDestroyedEntities(vector<shared_ptr<Entity>> & vec) {
  vec.erase(remove_if(begin(vec), end(vec), [] (const shared_ptr<Entity> & e) { return e->destroyed; }), end(vec));
=======
void removeDestroyedEntities(vector<Entity> & vec) {
    // TODO: consider a threshold for different entity types
    vec.erase(remove_if(begin(vec), end(vec), [] (const Entity & e) { return e.getHealth() <= 0u; }), end(vec));
=======
 
void removeDeadEntities(vector<Entity> & vec) {
  // TODO: consider a threshold for different entity types
  vec.erase(remove_if(begin(vec), end(vec), [] (const Entity & e) { return e.getHealth() <= 0u; }), end(vec));
>>>>>>> n/a
>>>>>>> n/a
}

struct Game {
<<<<<<< HEAD
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
=======
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
<<<<<<< HEAD
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
=======
    entity.emplace_back(Player{Vec2(screenWidth / 2.f, screenHeight - 20.f)}); 
    removeDeadEntities(entity); 
    while(true)
    {
>>>>>>> n/a
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
>>>>>>> n/a

};

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
  Game{}.Run();
  return 0;
}
