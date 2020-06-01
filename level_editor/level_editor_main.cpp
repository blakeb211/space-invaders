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
      out_file = fstream("level_data.txt", ios::app);
      return true;
    }

    // Called once per frame
    bool OnUserUpdate(float fElapsedTime) override
    { 
      Fill(0,0,kScreenWidth,kScreenHeight,0x0000);
      if (IsFocused()) {
          //------------------------------------------------- 
          // mouse down: start building up path 
          //------------------------------------------------- 
          if (m_keys[VK_SPACE].bReleased) {
            int x = GetMouseX();
            int y = GetMouseY();
            path.push_back(make_pair(x, y));
          }
          //------------------------------------------------- 
          // Write path to file 
          //------------------------------------------------- 
          if (m_keys[VK_DOWN].bReleased) {
            out_file << "E1\n";
            for (auto i : path) {
              out_file << i.first << " " << i.second << "|";
            }
            out_file << "\n";
            out_file.flush();
            path.erase(begin(path), end(path));
          }
          //------------------------------------------------- 
          // Undo
          //------------------------------------------------- 
          if (m_keys[VK_UP].bReleased) {
            if (path.size() > 0)
            path.erase(--end(path));
          }

          //------------------------------------------------- 
          // ESCAPE - close output file
          //------------------------------------------------- 
          if (m_keys[VK_ESCAPE].bPressed) {
            out_file.close();
            return false;
          }
          

          cout << "path size: " << path.size() << endl;
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
