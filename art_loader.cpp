#include "stdlibs.h"
using namespace std;

int main() {
    string name = "Enemy4";
    string in_file_name = name + ".txt";
    string out_file_name = "create_" + name + ".txt";
    ifstream in_file(in_file_name, ios::in);
    ofstream out_file(out_file_name, ios::out);

    int y = 0;
    while(in_file.good()) {
        string line;
        getline(in_file, line);
        for(int x = 0; x < line.size(); x++) {
            if(line[x] == 'X') {
            out_file << "vox.emplace_back(" << x << ".f * blockWidth, " << y << ".f * blockHeight, Color(255,140,0,245));" << endl;
            }
        }

        y++;
    }
    in_file.close();
    out_file.close();
    return 0;
}
