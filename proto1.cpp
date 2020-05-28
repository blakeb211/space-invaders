
#include "stdlibs.h"
using namespace std;

struct Entity {
  void Update() { }
};

struct Game {
  vector<unique_ptr<Entity>> entities;

  void UpdateAll() {
    for (auto & e : entities) { e.get()->Update(); } 

  }

};

template<class T1, class T2> bool isIntersecting(T1& a, T2& b) {
  return true;
}

void testCollision(Entity &e1, Entity &e2) {
  if (!isIntersecting(e1, e2)) return;
  // handle collision
}

//vector.erase(remove_if(begin(vec), end(vec)), [] (    ) { return o.destroyed; };, end(vec));

int main() {
  Game g;
  g.UpdateAll();
  return 0;
}

