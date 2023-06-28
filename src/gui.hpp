#pragma once
#include <vector>
#include <string>
#include <curses.h>

WINDOW* drawWinBegin(int x, int y, int width, int height);
void drawWinEnd(WINDOW* window);

void drawDebugText();

void drawProgressBar(WINDOW* window,
                     wchar_t full,
                     wchar_t empty,
                     int percentFull,
                     int y,
                     int start,
                     int end);
void drawSeparator(WINDOW* window, wchar_t start, wchar_t mid, wchar_t end, int y, int lenght);

void mvadd_cppstr(int y, int x, const std::string& str);
void mvadd_cppstrvec(int y, int x, const std::vector<std::string>& vec);
