// CURSES SUCKS // DO NOT REMOVE THIS COMMENT // VERY IMPORTANT//
#include <cstdio>
#include <iostream>
#include <locale.h>
#include <math.h>
#include <ncursesw/ncurses.h>
#include <string>

#include "collision.hpp"
#include "common.hpp"
#include "mapparser.hpp"
#include "player.hpp"
#include "stats.hpp"
#include "tutorial.hpp"
#include "dialog.hpp"
#include "gui.hpp"

using namespace std;

int WIDTH = 1;
int HEIGHT = 1;

int CAMERA_PADDING = 100;

static char lastPress;

bool isKeyPressed(char key){
    return lastPress == key;
}

int main()
{
    initscr();

    curs_set(0);
    timeout(30);
    start_color();
    noecho();

    init_pair(1, COLOR_YELLOW, COLOR_BLACK);

    int x = 20;
    int y = 20;
    int lastX = 0;
    int lastY = 0;
    WIDTH = getmaxx(stdscr);
    HEIGHT = getmaxy(stdscr);
    int worldOffsetY = 0;
    int worldOffsetX = 0;
    int lastWorldOffsetY = 0;
    int lastWorldOffsetX = 0;
    bool stop = false;

    FILE* map = cacheMap("maps/outside.map");
    loadMapCol(map);
    loadMapObj(map, &worldOffsetY, &worldOffsetX, y, x);
    fclose(map);

    Dialog dialog("Tavernkeeper",
                  DialogNode("Hello and welcome to my humble shop! How can I help you?")
                      .append("Where can I find food?", DialogNode())
                      .append("Where can I find adventure?", DialogNode()));

    auto player = new Player();

    while (stop == false) {
        if (is_term_resized(HEIGHT, WIDTH) == true) {
            WIDTH = getmaxx(stdscr);
            HEIGHT = getmaxy(stdscr);
            CAMERA_PADDING = std::max(WIDTH / 3, HEIGHT / 3);
        }

        drawMap(worldOffsetY, worldOffsetX, HEIGHT, WIDTH);

        // TODO: Refactor player
        attron(COLOR_PAIR(1));
        mvaddstr(y, x, player->symbolAsCStr());
        attroff(COLOR_PAIR(1));

        drawDebugText();
        drawTutorialWin();
        dialog.draw();

        // TODO: Refactor player
        lastX = x;
        lastY = y;
        lastWorldOffsetX = worldOffsetX;
        lastWorldOffsetY = worldOffsetY;

        lastPress = getch();

        if (lastPress == Keys::QUIT) {
            stop = true;
        }

        if (lastPress == Keys::STATS) {
            timeout(60);
            lastPress = ' ';
            while (lastPress != Keys::QUIT && lastPress != Keys::STATS) {
                lastPress = getch();
                erase();
                drawStatWin();
                if (lastPress == Keys::UP) {
                    hp[0]++;
                }
                if (lastPress == Keys::DOWN) {
                    hp[0]--;
                }
            }
            timeout(30);
        }

        // PLAYER MOVEMENT
        if (lastPress == Keys::UP) {
            if (y - CAMERA_PADDING <= 0 && worldOffsetY > 0) {
                worldOffsetY--;
            } else {
                y--;
            }
        }
        if (lastPress == Keys::DOWN) {
            if (y + CAMERA_PADDING >= HEIGHT) {
                worldOffsetY++;
            } else {
                y++;
            }
        }
        if (lastPress == Keys::RIGHT) {
            if (x + CAMERA_PADDING >= WIDTH) {
                worldOffsetX++;
            } else {
                x++;
            }
        }
        if (lastPress == Keys::LEFT) {
            if (x - CAMERA_PADDING <= 0 && worldOffsetX > 0) {
                worldOffsetX--;
            } else {
                x--;
            }
        }

        if ((lastWorldOffsetX != worldOffsetY || lastWorldOffsetX != worldOffsetX) || (lastY != y || lastX != x)) {
            if (colCheck(worldOffsetY + y, worldOffsetX + x) || (y < 0 || x < 0)) {
                x = lastX;
                y = lastY;
                worldOffsetX = lastWorldOffsetX;
                worldOffsetY = lastWorldOffsetY;
            }
        }

        refresh();
        erase();
    }
    endwin();
}
