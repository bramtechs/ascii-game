#include "common.hpp"
#include "gui.hpp"
#include <string>
#include <vector>

using namespace std;

vector<string> info = { "K - Magnifying Glass", "E - Stats", "",  "WASD - Movement",
                        "Arrow Keys - Attack",  "Q - Quit" };

void drawTutorialWin()
{
    auto pos = drawWin(2, 2, 30, 10, BOTTOM_RIGHT);
    mvadd_cppstrvec(pos.y, pos.x, info);
}
