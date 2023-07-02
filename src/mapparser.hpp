#pragma once

#include <stdlib.h>
#include <wchar.h>

#include "common.hpp"
#include "collision.hpp"

#define mapSizeY 1004
#define mapSizeX 1004

FILE* cacheMap(const char* mapName);
void loadMapObj(FILE* map, int* worldOffsetY, int* worldOffsetX, int y, int x);
void loadMapCol(FILE* map);
void drawMap(Point offset, Point max);
