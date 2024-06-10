#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;
class knightType {
public:
    struct position {
        position(int r = 0, int c = 0, int o = 0) {
            row = r;
            col = c; 
            onwardMoves = o;
        }
        int row;
        int col;
        int onwardMoves;
    };

    knightType(int = 8);
    bool knightTour(int, int); 
    void outputTour() const;
private:
    bool knightTour(int, int, int); vector<position> getAvailableMoves(int, int); bool fullBoard ();
    vector< vector<int> > board;

    int functionsCalled; 
};

int main() {
    return 0;
}