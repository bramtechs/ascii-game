#include "common.hpp"
#include "gui.hpp"
#include <string>
#include <vector>

using namespace std;

void drawTutorialWin()
{
    static string info = "";

    if (info.empty()) {
        for (const auto& pair : KeyDescriptions) {
            static char line[100];
            sprintf(line, "%c - %s\n", pair.first, pair.second.c_str());
            info += line;
        }
    }

    auto pos = drawWin(2, 2, 30, 10, BOTTOM_RIGHT);
    mvadd_cppstr(pos.y, pos.x, info);
}
