#pragma once
#include <string>
#include <curses.h>

WINDOW* drawWinBegin(int x, int y, int width, int height);
void drawWinEnd(WINDOW* window);

void drawProgressBar(WINDOW *window, wchar_t full, wchar_t empty, int percentFull, int y, int start, int end);
void drawSeparator(WINDOW *window, wchar_t start, wchar_t mid, wchar_t end, int y, int lenght);

inline void mvadd_cppstr(int y, int x, const std::string& str)
{
    mvaddnstr(y, x, str.c_str(), str.size());
}
