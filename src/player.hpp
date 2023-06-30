#pragma once
#include <memory>

#include "common.hpp"

// TODO: move to own file
class Entity {
   public:
    Point pos = { 0 };
    char symbol = '@';

    const char* symbolAsCStr();
};

class Player : public Entity {
   public:
    Player();
    Player* get();
};
