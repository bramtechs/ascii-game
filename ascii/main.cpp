#include <cstdio>
#include <iostream>
#include <locale.h>
#include <math.h>
#include <curses.h>
#include <string>

#include "collision.hpp"
#include "common.hpp"
#include "mapparser.hpp"
#include "player.hpp"
#include "stats.hpp"
#include "tutorial.hpp"
#include "dialog.hpp"
#include "input.hpp"
#include "gui.hpp"

using namespace std;

int WIDTH = 1;
int HEIGHT = 1;

int CAMERA_PADDING = 100;

static char lastPress;

bool isKeyPressed(char key)
{
    return lastPress == key;
}

bool isKeyReleased(char key)
{
    return lastPress != key;
}

int main()
{
    initscr();

    curs_set(0);
    timeout(30);
    start_color();
    noecho();

    init_pair(1, COLOR_YELLOW, COLOR_BLACK);

    Point camera = { 0, 0 };

    bool stop = false;

    auto& player = *(new Player({ 20, 20 }));

    FILE* map = cacheMap("maps/outside.map");
    loadMapCol(map);
    loadMapObj(map, &camera.y, &camera.x, player.pos.y, player.pos.x);
    fclose(map);

    Dialog dialog("Tavernkeeper",
                  DialogNode("Hello and welcome to my humble shop! How can I help you?")
                      .append("Where can I find food?", DialogNode())
                      .append("Where can I find adventure?", DialogNode()));

    while (stop == false) {
        if (is_termresized()) {
            WIDTH = getmaxx(stdscr);
            HEIGHT = getmaxy(stdscr);
            CAMERA_PADDING = std::max(WIDTH / 3, HEIGHT / 3);
        }

        drawMap(camera, { WIDTH, HEIGHT });

        player.draw(camera);

        drawDebugText(camera);
        drawTutorialWin();
        // dialog.draw();

        // handle key input
        lastPress = getch();

        // built in keys
        if (isKeyPressed(Keys::QUIT)) {
            stop = true;
        }

        refresh();
        erase();
    }
    endwin();
}
