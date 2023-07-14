#pragma once

#include "common.hpp"
class Entity {
   public:
    Point pos = { 0 };
    int color = 0;
    char symbol;

    Entity(Point pos, char symbol, int color=0);

    const char* symbolAsCStr();
    void draw(Point& camera);
};

