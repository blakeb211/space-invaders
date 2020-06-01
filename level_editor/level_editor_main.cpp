#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "stdlibs.h"
using namespace std;

constexpr float kScreenWidth = 800.f;
constexpr float kScreenHeight = 6.f * kScreenWidth / 9.f;

class Example : public olc::PixelGameEngine
{
  public:
    Example()
    {
      out_file = fstream("level_data.txt", ios::app);
      sAppName = "Level Editor";
      input_timer = 0.f;
    }
    // level editor vars
    vector<pair<float,float>> path; 
    fstream out_file;
    float input_timer;
    const float timer_max{0.2f};

  public:
    bool OnUserCreate() override
    {
      // Called once at the start, so create things here
      return true;
    }

    // Called once per frame
    bool OnUserUpdate(float fElapsedTime) override
    {
      input_timer += fElapsedTime;
      if (input_timer > timer_max) {
        input_timer -= timer_max;
        if (GetMouse(0).bPressed) { // get left button state
        }
        // mouse down: start building up path 
        // mouse up: save, clear_path, reset
      }

      // draw current path
      for(auto &i : path) {
        FillCircle((int)round(i.first),(int)round(i.second), 3, olc::WHITE); 
      }
      return true;
    }

    float CalcDistance(pair<float, float> p1, pair<float, float> p2) {
      return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    }
    
    // clean the current path up from having too many points close together
    void CleanPath() {

    }
};


int main()
{
  Example demo;
  if (demo.Construct(kScreenWidth / 3.f, kScreenHeight / 3.f, 3, 3))
    demo.Start();

  demo.out_file.close();
  return 0;
}
