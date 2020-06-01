#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "stdlibs.h"
using namespace std;


class Example : public olc::PixelGameEngine
{
  public:
  Example()
  {
    out_file = fstream("level_data.txt", ios::app);
    sAppName = "Level Editor";
  }
  // level editor vars
  vector<pair<float,float>> path; 
  fstream out_file;

  public:
  bool OnUserCreate() override
  {
    // Called once at the start, so create things here
    return true;
  }

  bool OnUserUpdate(float fElapsedTime) override
  {
    // called once per frame
    // mouse down: start building up path 
    // mouse up: clean path, save, reset
    // draw current path
    //Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand()% 255));	
    return true;
  }
};


int main()
{
  Example demo;
  if (demo.Construct(256, 240, 4, 4))
    demo.Start();
  
  demo.out_file.close();
  return 0;
}
