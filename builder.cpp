#include "builder.h"
#include "entity.h"
#include "globals.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
using namespace std;
using namespace sf;
using Vec2 = Vector2<float>;

void Builder::build_level(unsigned int & levelId) {
  switch(levelId) {
    case 1: 
  G::entity.push_back(make_shared<E1>(Vec2(1.f*G::screenWidth / 6.f, 1.f * G::screenHeight / 8.f)));
  G::entity.push_back(make_shared<E2>(Vec2(2.f*G::screenWidth / 6.f, 1.f * G::screenHeight / 8.f)));
  G::entity.push_back(make_shared<E3>(Vec2(3.f*G::screenWidth / 6.f, 1.f * G::screenHeight / 8.f)));
  G::entity.push_back(make_shared<E4>(Vec2(4.f*G::screenWidth / 6.f, 1.f * G::screenHeight / 8.f)));
  G::entity.push_back(make_shared<E2>(Vec2(1.f*G::screenWidth / 6.f, 2.f * G::screenHeight / 8.f)));
  G::entity.push_back(make_shared<E1>(Vec2(2.f*G::screenWidth / 6.f, 2.f * G::screenHeight / 8.f)));
  G::entity.push_back(make_shared<E4>(Vec2(3.f*G::screenWidth / 6.f, 3.f * G::screenHeight / 8.f)));
  G::entity.push_back(make_shared<E3>(Vec2(4.f*G::screenWidth / 6.f, 3.f * G::screenHeight / 8.f)));

  break;
    case 2:
  break;
    case 3:
  break;
  }
}
void Builder::build_player(vector<Voxel> &vox) {
  vox.emplace_back(0.f,0.f);
  vox.emplace_back(0.f+1.f * G::bW, 0.f);
  vox.emplace_back(0.f+2.f * G::bW, 0.f);
  vox.emplace_back(0.f+1.f * G::bW, 0.f - 1.f* G::bW, Color::Cyan);
}

void Builder::build_B1(vector<Voxel> &vox) { 
  vox.emplace_back(1.f * G::bW, 0.f * G::bW, Color(209,181,190,255));
  vox.emplace_back(0.f * G::bW, 1.f * G::bW, Color(209,181,190,255));
  vox.emplace_back(1.f * G::bW, 1.f * G::bW, Color(209,181,190,255));
  vox.emplace_back(2.f * G::bW, 1.f * G::bW, Color(209,181,190,255));
  vox.emplace_back(1.f * G::bW, 2.f * G::bW, Color(209,181,190,255));
}

void Builder::build_B2(vector<Voxel> &vox) {
  vox.emplace_back(2.f * G::bW, 0.f * G::bW, Color(112,1,209,255));
  vox.emplace_back(3.f * G::bW, 0.f * G::bW, Color(112,1,209,255));
  vox.emplace_back(1.f * G::bW, 1.f * G::bW, Color(112,1,209,255));
  vox.emplace_back(2.f * G::bW, 1.f * G::bW, Color(112,1,209,255));
  vox.emplace_back(3.f * G::bW, 1.f * G::bW, Color(112,1,209,255));
  vox.emplace_back(4.f * G::bW, 1.f * G::bW, Color(112,1,209,255));
  vox.emplace_back(1.f * G::bW, 2.f * G::bW, Color(112,1,209,255));
  vox.emplace_back(4.f * G::bW, 2.f * G::bW, Color(112,1,209,255));
  vox.emplace_back(0.f * G::bW, 3.f * G::bW, Color(112,1,209,255));
  vox.emplace_back(5.f * G::bW, 3.f * G::bW, Color(112,1,209,255));
}

void Builder::build_B3(vector<Voxel> &vox) {
}


void Builder::build_E1(vector<Voxel> &vox) {
  vox.emplace_back(9.f * G::bW, 0.f * G::bW, Color::Cyan);
  vox.emplace_back(10.f * G::bW, 0.f * G::bW, Color::Cyan);
  vox.emplace_back(11.f * G::bW, 0.f * G::bW, Color::Cyan);
  vox.emplace_back(12.f * G::bW, 0.f * G::bW, Color::Cyan);
  vox.emplace_back(7.f * G::bW, 1.f * G::bW, Color::Cyan);
  vox.emplace_back(8.f * G::bW, 1.f * G::bW, Color::Cyan);
  vox.emplace_back(9.f * G::bW, 1.f * G::bW, Color::Cyan);
  vox.emplace_back(10.f * G::bW, 1.f * G::bW, Color::Cyan);
  vox.emplace_back(11.f * G::bW, 1.f * G::bW, Color::Cyan);
  vox.emplace_back(12.f * G::bW, 1.f * G::bW, Color::Cyan);
  vox.emplace_back(13.f * G::bW, 1.f * G::bW, Color::Cyan);
  vox.emplace_back(14.f * G::bW, 1.f * G::bW, Color::Cyan);
  vox.emplace_back(6.f * G::bW, 2.f * G::bW, Color::Cyan);
  vox.emplace_back(7.f * G::bW, 2.f * G::bW, Color::Cyan);
  vox.emplace_back(8.f * G::bW, 2.f * G::bW, Color::Cyan);
  vox.emplace_back(9.f * G::bW, 2.f * G::bW, Color::Cyan);
  vox.emplace_back(10.f * G::bW, 2.f * G::bW, Color::Cyan);
  vox.emplace_back(11.f * G::bW, 2.f * G::bW, Color::Cyan);
  vox.emplace_back(12.f * G::bW, 2.f * G::bW, Color::Cyan);
  vox.emplace_back(13.f * G::bW, 2.f * G::bW, Color::Cyan);
  vox.emplace_back(14.f * G::bW, 2.f * G::bW, Color::Cyan);
  vox.emplace_back(15.f * G::bW, 2.f * G::bW, Color::Cyan);
  vox.emplace_back(5.f * G::bW, 3.f * G::bW, Color::Cyan);
  vox.emplace_back(6.f * G::bW, 3.f * G::bW, Color::Cyan);
  vox.emplace_back(9.f * G::bW, 3.f * G::bW, Color::Cyan);
  vox.emplace_back(10.f * G::bW, 3.f * G::bW, Color::Cyan);
  vox.emplace_back(11.f * G::bW, 3.f * G::bW, Color::Cyan);
  vox.emplace_back(12.f * G::bW, 3.f * G::bW, Color::Cyan);
  vox.emplace_back(15.f * G::bW, 3.f * G::bW, Color::Cyan);
  vox.emplace_back(16.f * G::bW, 3.f * G::bW, Color::Cyan);
  vox.emplace_back(5.f * G::bW, 4.f * G::bW, Color::Cyan);
  vox.emplace_back(6.f * G::bW, 4.f * G::bW, Color::Cyan);
  vox.emplace_back(7.f * G::bW, 4.f * G::bW, Color::Cyan);
  vox.emplace_back(8.f * G::bW, 4.f * G::bW, Color::Cyan);
  vox.emplace_back(9.f * G::bW, 4.f * G::bW, Color::Cyan);
  vox.emplace_back(10.f * G::bW, 4.f * G::bW, Color::Cyan);
  vox.emplace_back(11.f * G::bW, 4.f * G::bW, Color::Cyan);
  vox.emplace_back(12.f * G::bW, 4.f * G::bW, Color::Cyan);
  vox.emplace_back(13.f * G::bW, 4.f * G::bW, Color::Cyan);
  vox.emplace_back(14.f * G::bW, 4.f * G::bW, Color::Cyan);
  vox.emplace_back(15.f * G::bW, 4.f * G::bW, Color::Cyan);
  vox.emplace_back(16.f * G::bW, 4.f * G::bW, Color::Cyan);
  vox.emplace_back(8.f * G::bW, 5.f * G::bW, Color::Cyan);
  vox.emplace_back(13.f * G::bW, 5.f * G::bW, Color::Cyan);
  vox.emplace_back(7.f * G::bW, 6.f * G::bW, Color::Cyan);
  vox.emplace_back(9.f * G::bW, 6.f * G::bW, Color::Cyan);
  vox.emplace_back(10.f * G::bW, 6.f * G::bW, Color::Cyan);
  vox.emplace_back(11.f * G::bW, 6.f * G::bW, Color::Cyan);
  vox.emplace_back(12.f * G::bW, 6.f * G::bW, Color::Cyan);
  vox.emplace_back(14.f * G::bW, 6.f * G::bW, Color::Cyan);
  vox.emplace_back(6.f * G::bW, 7.f * G::bW, Color::Cyan);
  vox.emplace_back(9.f * G::bW, 7.f * G::bW, Color::Cyan);
  vox.emplace_back(12.f * G::bW, 7.f * G::bW, Color::Cyan);
  vox.emplace_back(15.f * G::bW, 7.f * G::bW, Color::Cyan);
}

void Builder::build_E2(vector<Voxel> &vox) {
  vox.emplace_back(3.f * G::bW, 0.f * G::bW, Color::Magenta);
  vox.emplace_back(4.f * G::bW, 0.f * G::bW, Color::Magenta);
  vox.emplace_back(17.f * G::bW, 0.f * G::bW, Color::Magenta);
  vox.emplace_back(18.f * G::bW, 0.f * G::bW, Color::Magenta);
  vox.emplace_back(6.f * G::bW, 1.f * G::bW, Color::Magenta);
  vox.emplace_back(16.f * G::bW, 1.f * G::bW, Color::Magenta);
  vox.emplace_back(5.f * G::bW, 2.f * G::bW, Color::Magenta);
  vox.emplace_back(6.f * G::bW, 2.f * G::bW, Color::Magenta);
  vox.emplace_back(7.f * G::bW, 2.f * G::bW, Color::Magenta);
  vox.emplace_back(8.f * G::bW, 2.f * G::bW, Color::Magenta);
  vox.emplace_back(9.f * G::bW, 2.f * G::bW, Color::Magenta);
  vox.emplace_back(10.f * G::bW, 2.f * G::bW, Color::Magenta);
  vox.emplace_back(11.f * G::bW, 2.f * G::bW, Color::Magenta);
  vox.emplace_back(12.f * G::bW, 2.f * G::bW, Color::Magenta);
  vox.emplace_back(13.f * G::bW, 2.f * G::bW, Color::Magenta);
  vox.emplace_back(14.f * G::bW, 2.f * G::bW, Color::Magenta);
  vox.emplace_back(15.f * G::bW, 2.f * G::bW, Color::Magenta);
  vox.emplace_back(16.f * G::bW, 2.f * G::bW, Color::Magenta);
  vox.emplace_back(17.f * G::bW, 2.f * G::bW, Color::Magenta);
  vox.emplace_back(4.f * G::bW, 3.f * G::bW, Color::Magenta);
  vox.emplace_back(5.f * G::bW, 3.f * G::bW, Color::Magenta);
  vox.emplace_back(6.f * G::bW, 3.f * G::bW, Color::Magenta);
  vox.emplace_back(8.f * G::bW, 3.f * G::bW, Color::Magenta);
  vox.emplace_back(9.f * G::bW, 3.f * G::bW, Color::Magenta);
  vox.emplace_back(10.f * G::bW, 3.f * G::bW, Color::Magenta);
  vox.emplace_back(11.f * G::bW, 3.f * G::bW, Color::Magenta);
  vox.emplace_back(12.f * G::bW, 3.f * G::bW, Color::Magenta);
  vox.emplace_back(13.f * G::bW, 3.f * G::bW, Color::Magenta);
  vox.emplace_back(14.f * G::bW, 3.f * G::bW, Color::Magenta);
  vox.emplace_back(16.f * G::bW, 3.f * G::bW, Color::Magenta);
  vox.emplace_back(17.f * G::bW, 3.f * G::bW, Color::Magenta);
  vox.emplace_back(18.f * G::bW, 3.f * G::bW, Color::Magenta);
  vox.emplace_back(2.f * G::bW, 4.f * G::bW, Color::Magenta);
  vox.emplace_back(3.f * G::bW, 4.f * G::bW, Color::Magenta);
  vox.emplace_back(4.f * G::bW, 4.f * G::bW, Color::Magenta);
  vox.emplace_back(5.f * G::bW, 4.f * G::bW, Color::Magenta);
  vox.emplace_back(6.f * G::bW, 4.f * G::bW, Color::Magenta);
  vox.emplace_back(7.f * G::bW, 4.f * G::bW, Color::Magenta);
  vox.emplace_back(8.f * G::bW, 4.f * G::bW, Color::Magenta);
  vox.emplace_back(9.f * G::bW, 4.f * G::bW, Color::Magenta);
  vox.emplace_back(10.f * G::bW, 4.f * G::bW, Color::Magenta);
  vox.emplace_back(11.f * G::bW, 4.f * G::bW, Color::Magenta);
  vox.emplace_back(12.f * G::bW, 4.f * G::bW, Color::Magenta);
  vox.emplace_back(13.f * G::bW, 4.f * G::bW, Color::Magenta);
  vox.emplace_back(14.f * G::bW, 4.f * G::bW, Color::Magenta);
  vox.emplace_back(15.f * G::bW, 4.f * G::bW, Color::Magenta);
  vox.emplace_back(16.f * G::bW, 4.f * G::bW, Color::Magenta);
  vox.emplace_back(17.f * G::bW, 4.f * G::bW, Color::Magenta);
  vox.emplace_back(18.f * G::bW, 4.f * G::bW, Color::Magenta);
  vox.emplace_back(19.f * G::bW, 4.f * G::bW, Color::Magenta);
  vox.emplace_back(20.f * G::bW, 4.f * G::bW, Color::Magenta);
  vox.emplace_back(5.f * G::bW, 5.f * G::bW, Color::Magenta);
  vox.emplace_back(6.f * G::bW, 5.f * G::bW, Color::Magenta);
  vox.emplace_back(7.f * G::bW, 5.f * G::bW, Color::Magenta);
  vox.emplace_back(8.f * G::bW, 5.f * G::bW, Color::Magenta);
  vox.emplace_back(9.f * G::bW, 5.f * G::bW, Color::Magenta);
  vox.emplace_back(10.f * G::bW, 5.f * G::bW, Color::Magenta);
  vox.emplace_back(11.f * G::bW, 5.f * G::bW, Color::Magenta);
  vox.emplace_back(12.f * G::bW, 5.f * G::bW, Color::Magenta);
  vox.emplace_back(13.f * G::bW, 5.f * G::bW, Color::Magenta);
  vox.emplace_back(14.f * G::bW, 5.f * G::bW, Color::Magenta);
  vox.emplace_back(15.f * G::bW, 5.f * G::bW, Color::Magenta);
  vox.emplace_back(16.f * G::bW, 5.f * G::bW, Color::Magenta);
  vox.emplace_back(17.f * G::bW, 5.f * G::bW, Color::Magenta);
  vox.emplace_back(5.f * G::bW, 6.f * G::bW, Color::Magenta);
  vox.emplace_back(17.f * G::bW, 6.f * G::bW, Color::Magenta);
  vox.emplace_back(6.f * G::bW, 7.f * G::bW, Color::Magenta);
  vox.emplace_back(7.f * G::bW, 7.f * G::bW, Color::Magenta);
  vox.emplace_back(8.f * G::bW, 7.f * G::bW, Color::Magenta);
  vox.emplace_back(9.f * G::bW, 7.f * G::bW, Color::Magenta);
  vox.emplace_back(14.f * G::bW, 7.f * G::bW, Color::Magenta);
  vox.emplace_back(15.f * G::bW, 7.f * G::bW, Color::Magenta);
  vox.emplace_back(16.f * G::bW, 7.f * G::bW, Color::Magenta);
  vox.emplace_back(17.f * G::bW, 7.f * G::bW, Color::Magenta);
}

void Builder::build_E3(vector<Voxel> &vox) {
  vox.emplace_back(9.f * G::bW, 0.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(10.f * G::bW, 0.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(11.f * G::bW, 0.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(12.f * G::bW, 0.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(13.f * G::bW, 0.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(5.f * G::bW, 1.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(6.f * G::bW, 1.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(7.f * G::bW, 1.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(8.f * G::bW, 1.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(9.f * G::bW, 1.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(10.f * G::bW, 1.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(11.f * G::bW, 1.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(12.f * G::bW, 1.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(13.f * G::bW, 1.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(14.f * G::bW, 1.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(15.f * G::bW, 1.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(16.f * G::bW, 1.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(4.f * G::bW, 2.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(5.f * G::bW, 2.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(6.f * G::bW, 2.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(7.f * G::bW, 2.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(8.f * G::bW, 2.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(9.f * G::bW, 2.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(10.f * G::bW, 2.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(11.f * G::bW, 2.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(12.f * G::bW, 2.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(13.f * G::bW, 2.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(14.f * G::bW, 2.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(15.f * G::bW, 2.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(16.f * G::bW, 2.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(17.f * G::bW, 2.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(18.f * G::bW, 2.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(4.f * G::bW, 3.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(5.f * G::bW, 3.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(6.f * G::bW, 3.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(9.f * G::bW, 3.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(10.f * G::bW, 3.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(11.f * G::bW, 3.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(12.f * G::bW, 3.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(13.f * G::bW, 3.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(16.f * G::bW, 3.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(17.f * G::bW, 3.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(18.f * G::bW, 3.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(4.f * G::bW, 4.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(5.f * G::bW, 4.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(6.f * G::bW, 4.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(7.f * G::bW, 4.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(8.f * G::bW, 4.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(9.f * G::bW, 4.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(10.f * G::bW, 4.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(11.f * G::bW, 4.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(12.f * G::bW, 4.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(13.f * G::bW, 4.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(14.f * G::bW, 4.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(15.f * G::bW, 4.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(16.f * G::bW, 4.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(17.f * G::bW, 4.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(18.f * G::bW, 4.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(6.f * G::bW, 5.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(7.f * G::bW, 5.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(8.f * G::bW, 5.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(14.f * G::bW, 5.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(15.f * G::bW, 5.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(16.f * G::bW, 5.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(5.f * G::bW, 6.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(6.f * G::bW, 6.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(7.f * G::bW, 6.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(15.f * G::bW, 6.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(16.f * G::bW, 6.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(17.f * G::bW, 6.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(3.f * G::bW, 7.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(4.f * G::bW, 7.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(5.f * G::bW, 7.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(17.f * G::bW, 7.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(18.f * G::bW, 7.f * G::bW, Color::Red + Color::Yellow);
  vox.emplace_back(19.f * G::bW, 7.f * G::bW, Color::Red + Color::Yellow);
}

void Builder::build_E4(vector<Voxel> &vox) {
  vox.emplace_back(9.f * G::bW, 0.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(10.f * G::bW, 0.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(11.f * G::bW, 0.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(12.f * G::bW, 0.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(13.f * G::bW, 0.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(14.f * G::bW, 0.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(15.f * G::bW, 0.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(16.f * G::bW, 0.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(17.f * G::bW, 0.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(18.f * G::bW, 0.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(19.f * G::bW, 0.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(6.f * G::bW, 1.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(7.f * G::bW, 1.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(8.f * G::bW, 1.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(9.f * G::bW, 1.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(10.f * G::bW, 1.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(11.f * G::bW, 1.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(12.f * G::bW, 1.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(13.f * G::bW, 1.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(14.f * G::bW, 1.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(15.f * G::bW, 1.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(16.f * G::bW, 1.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(17.f * G::bW, 1.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(18.f * G::bW, 1.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(19.f * G::bW, 1.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(20.f * G::bW, 1.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(21.f * G::bW, 1.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(22.f * G::bW, 1.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(23.f * G::bW, 1.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(4.f * G::bW, 2.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(5.f * G::bW, 2.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(6.f * G::bW, 2.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(7.f * G::bW, 2.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(8.f * G::bW, 2.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(9.f * G::bW, 2.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(10.f * G::bW, 2.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(11.f * G::bW, 2.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(12.f * G::bW, 2.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(13.f * G::bW, 2.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(14.f * G::bW, 2.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(15.f * G::bW, 2.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(16.f * G::bW, 2.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(17.f * G::bW, 2.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(18.f * G::bW, 2.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(19.f * G::bW, 2.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(20.f * G::bW, 2.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(21.f * G::bW, 2.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(22.f * G::bW, 2.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(23.f * G::bW, 2.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(24.f * G::bW, 2.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(25.f * G::bW, 2.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(3.f * G::bW, 3.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(4.f * G::bW, 3.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(5.f * G::bW, 3.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(6.f * G::bW, 3.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(8.f * G::bW, 3.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(9.f * G::bW, 3.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(10.f * G::bW, 3.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(11.f * G::bW, 3.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(13.f * G::bW, 3.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(14.f * G::bW, 3.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(15.f * G::bW, 3.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(16.f * G::bW, 3.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(18.f * G::bW, 3.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(19.f * G::bW, 3.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(20.f * G::bW, 3.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(21.f * G::bW, 3.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(23.f * G::bW, 3.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(24.f * G::bW, 3.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(25.f * G::bW, 3.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(26.f * G::bW, 3.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(0.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(1.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(2.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(3.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(4.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(5.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(6.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(7.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(8.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(9.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(10.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(11.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(12.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(13.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(14.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(15.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(16.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(17.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(18.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(19.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(20.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(21.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(22.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(23.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(24.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(25.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(26.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(27.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(28.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(29.f * G::bW, 4.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(5.f * G::bW, 5.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(6.f * G::bW, 5.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(7.f * G::bW, 5.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(8.f * G::bW, 5.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(9.f * G::bW, 5.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(13.f * G::bW, 5.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(14.f * G::bW, 5.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(15.f * G::bW, 5.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(16.f * G::bW, 5.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(20.f * G::bW, 5.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(21.f * G::bW, 5.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(22.f * G::bW, 5.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(23.f * G::bW, 5.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(24.f * G::bW, 5.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(7.f * G::bW, 6.f * G::bW, Color(255,140,0,245));
  vox.emplace_back(22.f * G::bW, 6.f * G::bW, Color(255,140,0,245));
}

void build_wall1(Vec2 start, Vec2 end, vector<Voxel> & vox) {


}
