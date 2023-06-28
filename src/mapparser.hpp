#pragma once

#define mapSizeY 1004
#define mapSizeX 1004

#include <stdlib.h>
#include <wchar.h>
#include "collision.hpp"

void cacheMap(FILE *map);
void loadMapObj(FILE *map, int *worldOffsetY, int *worldOffsetX, int y, int x);
void loadMapCol(FILE *map);
void drawMap(int worldOffsetY, int worldOffsetX, int termMaxY, int termMaxX);