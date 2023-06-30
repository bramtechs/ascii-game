#include <memory>

#include "player.hpp"

using namespace std;

static Player* instance;

Player::Player()
{
    instance = this;
}

Player* Player::get()
{
    return instance;
}

const char* Entity::symbolAsCStr()
{
    static char str[2];
    str[0] = this->symbol;
    str[1] = '\0';
    return str;
}
