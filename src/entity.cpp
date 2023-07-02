#include <ncursesw/ncurses.h>

#include "entity.hpp"

Entity::Entity(Point pos)
{
    this->pos = pos;
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
