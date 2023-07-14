#include <curses.h>

#include "entity.hpp"

Entity::Entity(Point pos, char symbol, int color)
{
    this->pos = pos;
    this->symbol = symbol;
    this->color = color;
}

void Entity::draw(Point& camera)
{
    attron(COLOR_PAIR(color));
    mvaddstr(pos.y, pos.x, symbolAsCStr());
    attroff(COLOR_PAIR(color));
}

const char* Entity::symbolAsCStr()
{
    static char str[2];
    str[0] = this->symbol;
    str[1] = '\0';
    return str;
}
