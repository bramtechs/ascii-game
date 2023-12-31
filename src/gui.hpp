#pragma once
#include <vector>
#include <string>
#include <curses.h>
#include "common.hpp"

enum Anchor {
    TOP_LEFT,
    BOTTOM_RIGHT,
};

extern const std::unordered_map<Keys, std::string> KeyDescriptions;

Point drawWin(int y, int x, int width, int height, Anchor anchor = TOP_LEFT);

void drawDebugText(Point& camera);

void drawProgressBar(WINDOW* window, wchar_t full, wchar_t empty, int percentFull, int y, int start, int end);
void drawSeparator(WINDOW* window, wchar_t start, wchar_t mid, wchar_t end, int y, int lenght);

WINDOW* drawFullscreenWindow();

void mvadd_cppstr(int y, int x, const std::string& str);
void mvadd_cppstrvec(int y, int x, const std::vector<std::string>& vec);
