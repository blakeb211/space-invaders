#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "stdlibs.h"
#include "entity.h"
#include "globals.h"
#include "builder.h" 
#include "collision_manager.h"

using namespace std;
using namespace sf;
using Vec2 = Vector2<float>; 
using FrameTime = float;

//------------------------------------------------------------------------------------
// Global Functions
//------------------------------------------------------------------------------------

 


struct Game {
    // These members are related to the control of the game.
    RenderWindow window{{G::screenWidth, G::screenHeight}, G::screenTitle};
    FrameTime lastFt{0.f}, currentSlice{0.f};
    FrameTime ftStep{12.f}, ftSlice{12.f};
    bool gameOver{false};
    CollisionManager coll_mgr;
    int updateCounter = 0;
    
    Game() {
        window.setFramerateLimit(80);
        unsigned int levelId{1};
        // Create Player
        G::entity.push_back(make_shared<Player>(Vec2(3.f*G::screenWidth / 4.f, G::screenHeight - 20.f))); 
        // Load level
        Builder::build_level(levelId);
    }
    
    static void removeDestroyedEntities(vector<shared_ptr<Entity>> & vec) {
        vec.erase(remove_if(begin(vec), end(vec), [] (const shared_ptr<Entity> & e) { return e->destroyed; }), end(vec));
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
            if (Entity::withId(0)->getPos().x > 0.f) {
                Entity::withId(0)->move({ftStep * -1.f * G::kPlayerSpeed,0.f}); 
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::Key::Right)) { 
            if (Entity::withId(0)->getPos().x < G::screenWidth) {
                Entity::withId(0)->move({ftStep * G::kPlayerSpeed,0.f}); 
            }
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
        /* produce collision map*/
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
                updateCounter++;
                if (updateCounter % 5 == 0) {
                    coll_mgr.CheckCollisionsForThisFrame(); 
                }
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
