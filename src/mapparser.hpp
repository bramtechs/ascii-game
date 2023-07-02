#pragma once

#include <stdlib.h>
#include <wchar.h>
#include <string>

#include "common.hpp"
#include "collision.hpp"

#define MAP_SIZE 1024

typedef wchar_t AsciiMap[MAP_SIZE][MAP_SIZE];

FILE* cacheMap(const char* mapName);
void loadMapObj(FILE* map, int* worldOffsetY, int* worldOffsetX, int y, int x);
void loadMapCol(FILE* map);
void drawMap(Point offset, Point max);

std::string getMapName();
