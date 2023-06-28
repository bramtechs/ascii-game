#ifndef collision_h_INCLUDED
#define collision_h_INCLUDED

#include <ncursesw/ncurses.h>
#include <stdbool.h>
#include <math.h>
#include "arraycheck.hpp"

void clearCol();
void printCol(char character, bool printAll);
void addCol(int y, int x);
void tmvaddch(char character, int y, int x);
void drawColLine(int x1, int y1, int x2, int y2, char c);
bool colCheck(int y, int x);

#endif  // collision_h_INCLUDED
