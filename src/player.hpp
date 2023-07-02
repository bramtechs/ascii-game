#pragma once
#include <memory>

#include "entity.hpp"
#include "common.hpp"

class Player : public Entity {
   public:
    static Player& get();

    Player(Point pos);

    void draw(Point& camera);
};
