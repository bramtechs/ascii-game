#pragma once
#include <memory>

#include "entity.hpp"
#include "common.hpp"

class Player : public Entity {
   public:
    Player(Point pos);
    Player* get();

    void draw(Point& camera);
};
