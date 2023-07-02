#pragma once

#include "common.hpp"
class Entity {
   public:
    Point pos = { 0 };
    char symbol = '@';
    int color = 1;

    Entity(Point pos);

    const char* symbolAsCStr();
    void draw(Point& camera);
};

