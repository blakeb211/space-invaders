#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "stdlibs.h"

using namespace std;

struct Vector3 {
  float x, y, theta;
};

using Vec3 = Vector3; 

struct Voxel { 
    Vec3 pos;  //x, y , theta
    int color;
    int health; // voxel health
};

struct Entity {
    virtual void Update(float fElapsed) { /* check for collision */ /* update pos */  }
    virtual void Draw() { }
    virtual ~Entity() { }  
    private:
    // should this be shared_ptr?
    list<Voxel> vox;
};

struct Bullet : Entity {

};
struct B1 : Bullet {

};

struct B2 : Bullet {

};

struct Player : Entity {


};

struct Enemy: Entity {
};

struct E1: Enemy {

};
struct E2: Enemy {

};
struct E3: Enemy {

};
struct E4: Enemy {

};

template<class T1, class T2> bool isIntersecting(T1& a, T2& b) {
    return true;
}

void testCollision(Entity &e1, Entity &e2) {
    if (!isIntersecting(e1, e2)) return;
    // handle collision
}

//vector.erase(remove_if(begin(vec), end(vec)), [] (    ) { return o.destroyed; };, end(vec));

// GLOBALS
static const int screenWidth{1024};
static const int screenHeight = {768};
static const int pixelSize = {3};
static bool gameOver{false};
static bool pause{false};

class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		sAppName = "Prototype #2 - Blake's Space Invaders Clone";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand()% 255));	
		return true;
	}
};




//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
  Example demo;
  if (demo.Construct(screenWidth / pixelSize,screenHeight / pixelSize, pixelSize, pixelSize))
    demo.Start();

    return 0;
}
