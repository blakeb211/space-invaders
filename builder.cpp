#include "builder.h"
#include "entity.h"
#include "globals.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
using namespace std;
using namespace sf;
using Vec2 = Vector2<float>;

void Builder::build_level(unsigned int & levelId) {
    // open the file levelN_data.txt
    cout << "opening level loading input file" << endl;
    ifstream in_file("level" + to_string(levelId) + "_data.txt", ios::in); 
    unsigned int enemyCount = 0;
    unsigned int pathCount = 0;
    queue<unsigned int> enemyIds = {};
    cout << "entering while loop" << endl;
    while(in_file.good()) {
        string line;
        getline(in_file, line); 
        // check if its a level layout line
        if (line.find('-') != string::npos) {
            for(int i = 0; i < line.size(); i++)
                if (isdigit(line[i])) {
                    enemyCount++;
                    // convert char number to int number 
                    int digit = line[i] - '0';
                    switch(digit) {
                        case 1:
                            G::entity.push_back(make_shared<E1>(Vec2(4.f*G::screenWidth / 6.f, 3.f * G::screenHeight / 8.f)));
                            break;
                        case 2:
                            G::entity.push_back(make_shared<E2>(Vec2(4.f*G::screenWidth / 6.f, 3.f * G::screenHeight / 8.f)));
                            break;
                        case 3:
                            G::entity.push_back(make_shared<E3>(Vec2(4.f*G::screenWidth / 6.f, 3.f * G::screenHeight / 8.f)));
                            break;
                        case 4:
                            G::entity.push_back(make_shared<E4>(Vec2(4.f*G::screenWidth / 6.f, 3.f * G::screenHeight / 8.f)));
                            break;
                        default: 
                            throw exception("switch in Builder::build_level failed");
                            break;
                    };
                    cout << "enemy  was added to G::entity" << endl;
                    // add the newly created enemy's entity id to the enemyIds vector
                    enemyIds.push((*(--end(G::entity)))->getId());
                }
        }
        // load the paths
        // check if its a path line
        //shared_ptr<Player> p_ptr = dynamic_pointer_cast<Player> (Entity::withId(0));
        if (line.find('|') != string::npos) {
            pathCount++;
            unsigned int currEntityId = enemyIds.front(); // pop from the front
            enemyIds.pop();
            // get a pointer to the enemy
            shared_ptr<Enemy> e_ptr = dynamic_pointer_cast<Enemy> (Entity::withId(currEntityId));
            // read in the path
            istringstream ss(line);
            // read in the whole line of float float|
            while(ss.good()) { 
                float x;
                float y;
                char c;
                ss >> x;
                if (ss.bad()) throw exception("sstring stream accessed when bad in Builder::build_level");
                ss >> y;
                ss >> c;
                assert(x*G::screenWidth <= G::screenWidth);
                assert(y*G::screenHeight <= G::screenHeight);
                e_ptr->path.push_back(Vec2(x*G::screenWidth, y*G::screenHeight));
            }
            cout << "path was added to an entity" << endl;
        }
    }
    cout << "closing level loading input file" << endl;
    in_file.close();
    assert(enemyCount == pathCount);
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
