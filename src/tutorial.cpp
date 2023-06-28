#include "common.hpp"
#include "gui.hpp"

const char* info[] = { "? - Magnifying Glass", "E - Stats", "",  "WASD - Movement",
                       "Arrow Keys - Attack",  "Q - Quit",  NULL };

void drawTutorialWin()
{
    const int MARGIN_RIGHT = 25;

    static int y;
    int row = HEIGHT - y * 2;
    y = 0;
    for (int i = 0; info[i] != NULL; i++) {
        mvadd_cppstr(row + i + 2, WIDTH - MARGIN_RIGHT, info[i]);
        y++;
    }
}