#include "stdlibs.h"
// link to raylib

using namespace std;
using Vec3 = Vector3<float>;
using Color = int;

struct Voxel { 
    Vec3 pos;  //ex, y , theta
    Color color;
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

struct Player : Entity {


};

struct Enemy : Entity {

};

struct Game {
    vector<unique_ptr<Entity>> entities;
    float fElapsed;

    void UpdateAll() {
        for (auto & e : entities) { e.get()->Update(fElapsed); } 

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

