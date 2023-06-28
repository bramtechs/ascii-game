#include "common.hpp"
#include "gui.hpp"
#include <string>
#include <vector>

using namespace std;

vector<string> info = { "K - Magnifying Glass", "E - Stats", "",  "WASD - Movement",
                        "Arrow Keys - Attack",  "Q - Quit" };

void drawTutorialWin()
{
    const int MARGIN_RIGHT = 25;
    mvadd_cppstrvec(HEIGHT - 20, WIDTH - MARGIN_RIGHT, info);
}
