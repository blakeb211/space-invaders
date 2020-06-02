#define OLC_PGE_APPLICATION
#include "olcConsoleGameEngine.h"
#include "stdlibs.h"
using namespace std;

constexpr float kScreenWidth = 1024.f;
constexpr float kScreenHeight = 3.f * kScreenWidth / 4.f;
constexpr float kPixelSize = 3.f;
// TODO: add object placement before path drawing
// TODO: need a convenient file format 
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
    // level layout drawing - must be 9 lines long
    const vector<string> layout = 
    {"-------------------",
     "------3---4---1--",
     "-------------------",
     "----2---1---2----",
     "-------------------", 
     "-----------4--------", 
     "-------------------", 
     "-------------------",
     "-------------------", 
    };

  public:
    bool OnUserCreate() override
    {
      // Called once at the start, so create things here
      out_file = fstream("level1_data.txt", ios::out);
      // print the layout first
      assert(layout.size() == 9);
      for (auto s : layout) {
        out_file << s << endl;
      }
      out_file << endl;
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
        // Write the path to file 
        //------------------------------------------------- 
        if (m_keys[VK_DOWN].bReleased) {
          if (path.size() > 0) {
            for (auto i : path) {
              out_file << setprecision(2) << i.first/kScreenWidth << " " << i.second/kScreenHeight << "|";
            }
            out_file << "\n\n";
            out_file.flush();
            path.erase(begin(path), end(path));
          }
        }
        //------------------------------------------------- 
        // Undo
        //------------------------------------------------- 
        if (m_keys[VK_UP].bReleased) {
          if (path.size() > 0)
            path.pop_back(); 
        }

        //------------------------------------------------- 
        // ESCAPE - close output file
        //------------------------------------------------- 
        if (m_keys[VK_ESCAPE].bPressed) {
          out_file.close();
          return false;
        }

        // draw enemy positions
        // i = line count
        // j = char count on line i
        for (int i = 0; i < layout.size(); i++) {
          for (int j = 0; j < layout[i].size(); j++) {
            if (isdigit((layout[i])[j])) {
              int xpos = (((float)(j+1)) / layout[i].size()) * kScreenWidth;
              int ypos = (((float)(i+1)) /layout.size()) * kScreenHeight;
              FillCircle(xpos / kPixelSize,ypos / kPixelSize,2, 'L', 145);
            }
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

};


int main()
{
  Example demo;
  if (demo.ConstructConsole(kScreenWidth / kPixelSize, kScreenHeight / kPixelSize, kPixelSize, kPixelSize))
    demo.Start();

  return 0;
}
