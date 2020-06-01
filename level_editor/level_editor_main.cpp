#define OLC_PGE_APPLICATION
#include "olcConsoleGameEngine.h"
#include "stdlibs.h"
using namespace std;

constexpr float kScreenWidth = 800.f;
constexpr float kScreenHeight = 6.f * kScreenWidth / 9.f;

class Example : public olcConsoleGameEngine
{
  public:
    Example()
    {
      input_timer = 0.f;
      path = vector<pair<int,int>>{};
    }
    // level editor vars
    vector<pair<int,int>> path; 
    fstream out_file;
    float input_timer;
    const float timer_max{0.3f};

  public:
    bool OnUserCreate() override
    {
      // Called once at the start, so create things here
      return true;
    }

    // Called once per frame
    bool OnUserUpdate(float fElapsedTime) override
    {
      if (IsFocused()) {
        input_timer += fElapsedTime;
        if (input_timer > timer_max) {
          input_timer -= timer_max;
          //------------------------------------------------- 
          // mouse down: start building up path 
          //------------------------------------------------- 
          if (m_keys[VK_SPACE].bPressed) {
            out_file = fstream("level_data.txt", ios::app);
            int x = GetMouseX();
            int y = GetMouseY();
            path.emplace_back(make_pair(x, y));
            out_file << "pushing " << x << " , " << y << endl;
          }
          //------------------------------------------------- 
          // mouse up: save, clear_path, reset
          //------------------------------------------------- 
          if (m_keys[VK_SPACE].bReleased) {
            out_file.close();
          }

        }

        // draw current path
        for(auto &i : path) {
          FillCircle((int)round(i.first),(int)round(i.second), 3); 
        }
      }
      return true;
    }

    float CalcDistance(pair<float, float> p1, pair<float, float> p2) {
      return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
    }

    // clean the current path up from having too many points close together
    void CleanPath() {

    }
};


int main()
{
  Example demo;
  if (demo.ConstructConsole(kScreenWidth / 3.f, kScreenHeight / 3.f, 3, 3))
    demo.Start();

  return 0;
}
