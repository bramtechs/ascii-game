#include "mapparser.hpp"

#include <cstdio>
#include <curses.h>
#include "gui.hpp"
#include <filesystem>
#include <string>

using namespace std;

wchar_t loadedMap[mapSizeY][mapSizeX];

string mapName;

FILE* cacheMap(const char* mapName)
{
    mapName = mapName;
    FILE* map = fopen(mapName, "r, ccs=UTF-8");
    fseek(map, 0, SEEK_SET);

    wchar_t drawTracker;
    int fileX = 0;
    int fileY = 0;

    while (feof(map) != 1) {
        drawTracker = fgetwc(map);
        fileX++;
        loadedMap[fileY][fileX] = drawTracker;
        if (drawTracker == L'\n') {
            fileX = 0;
            fileY++;
        }
    }

    return map;
}

void loadMapObj(FILE* map, int* worldOffsetY, int* worldOffsetX, int y, int x)
{
    fseek(map, 0, SEEK_SET);

    char drawTracker;
    int fileX = 0;
    int fileY = 0;

    while (feof(map) != 1) {
        drawTracker = fgetwc(map);
        fileX++;
        if (drawTracker == '\n') {
            fileX = 0;
            fileY++;
        } else if (drawTracker == '@') {
            *worldOffsetY = fileY - y;
            *worldOffsetX = fileX - x;
        }
    }
}

void loadMapCol(FILE* map)
{
    fseek(map, 0, SEEK_SET);

    char drawTracker;
    int fileX = 0;
    int fileY = 0;

    while (feof(map) != 1) {
        drawTracker = fgetwc(map);
        fileX++;
        if (drawTracker == '\n') {
            fileX = 0;
            fileY++;
        } else if (drawTracker == '#') {
            addCol(fileY, fileX);
        }
    }
}

void drawMap(Point offset, Point max)
{
    int i;
    int prtY = 0;
    int prtX = 0;

    for (i = 0; i < (max.y * max.x); i++) {
        if (offset.y < 0 || offset.x < 0) {
            mvprintw(prtY, prtX, "%lc", loadedMap[0 + prtY][0 + prtX]);
        } else if (loadedMap[offset.y + prtY][offset.x + prtX] == L'^') {
            prtX++;
        } else {
            mvprintw(prtY, prtX, "%lc", loadedMap[offset.y + prtY][offset.x + prtX]);
        }
        prtX++;
        if (prtX == max.x) {
            if (prtY != max.y) {
                prtY++;
            }
            prtX = 0;
        }
    }
}

string getMapName()
{
    return mapName;
}
