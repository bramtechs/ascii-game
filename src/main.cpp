// CURSES SUCKS // DO NOT REMOVE THIS COMMENT // VERY IMPORTANT//
#include <cstdio>
#define _XOPEN_SOURCE_EXTENDED
#include <iostream>
#include <locale.h>
#include <math.h>
#include <ncursesw/ncurses.h>
#include <string>

#include "collision.hpp"
#include "common.hpp"
#include "mapparser.hpp"
#include "stats.hpp"
#include "tutorial.hpp"
#include "gui.hpp"

using namespace std;

int WIDTH = 1;
int HEIGHT = 1;

constexpr int CAMERA_PADDING = 100;

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
    char lastPress;

    string playerChar = "@";

    FILE* map = cacheMap("maps/outside.map");
    loadMapCol(map);
    loadMapObj(map, &worldOffsetY, &worldOffsetX, y, x);
    fclose(map);

    while (stop == false) {
        if (is_term_resized(HEIGHT, WIDTH) == true) {
            WIDTH = getmaxx(stdscr);
            HEIGHT = getmaxy(stdscr);
        }

        drawMap(worldOffsetY, worldOffsetX, HEIGHT, WIDTH);
        drawTutorialWin();

        attron(COLOR_PAIR(1));
        mvadd_cppstr(y, x, playerChar);
        attroff(COLOR_PAIR(1));

        lastX = x;
        lastY = y;
        lastWorldOffsetX = worldOffsetX;
        lastWorldOffsetY = worldOffsetY;

        lastPress = getch();

        if (lastPress == 'q') {
            stop = true;
        }

        if (lastPress == 'e') {
            timeout(60);
            lastPress = ' ';
            while (lastPress != 'q' && lastPress != 'e') {
                lastPress = getch();
                erase();
                drawStatWin();
                if (lastPress == 'w') {
                    hp[0]++;
                }
                if (lastPress == 's') {
                    hp[0]--;
                }
            }
            timeout(30);
        }

        // PLAYER MOVEMENT
        if (lastPress == 'w') {
            if (y - CAMERA_PADDING <= 0 && worldOffsetY > 0) {
                worldOffsetY--;
            } else {
                y--;
            }
        }
        if (lastPress == 's') {
            if (y + CAMERA_PADDING >= HEIGHT) {
                worldOffsetY++;
            } else {
                y++;
            }
        }
        if (lastPress == 'd') {
            if (x + CAMERA_PADDING >= WIDTH) {
                worldOffsetX++;
            } else {
                x++;
            }
        }
        if (lastPress == 'a') {
            if (x - CAMERA_PADDING <= 0 && worldOffsetX > 0) {
                worldOffsetX--;
            } else {
                x--;
            }
        }

        if ((lastWorldOffsetX != worldOffsetY || lastWorldOffsetX != worldOffsetX)
            || (lastY != y || lastX != x)) {
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
