#include <curses.h>
#include "gui.hpp"
#include <string>
#include <sstream>
#include "common.hpp"

using namespace std;

static int cachedWidth;
static int cachedHeight;
WINDOW* drawWinBegin(int x, int y, int width, int height)
{
    cachedWidth = width;
    cachedHeight = height;

    // mvaddstr(y++, x, line.c_str());

    WINDOW* window = subwin(stdscr, x, y, width, height);

    box(window, ACS_VLINE, ACS_HLINE);
    return window;
}

void drawWinEnd(WINDOW* window)
{
    drawSeparator(window, L'├', L'─', L'┤', 8, cachedWidth / 1.2);
    wrefresh(window);
}

void drawProgressBar(WINDOW* window,
                     wchar_t full,
                     wchar_t empty,
                     int percentFull,
                     int y,
                     int start,
                     int end)
{
    int i;
    for (i = 0; i < (int)end - start; i++) {
        mvwprintw(window, y, start + i, "%lc", empty);
    }
    for (i = 0; i < (int)(end - start) * percentFull / 100; i++) {
        mvwprintw(window, y, start + i, "%lc", full);
    }
}

void drawSeparator(WINDOW* window, wchar_t start, wchar_t mid, wchar_t end, int y, int length)
{
    mvwprintw(window, y, (int)((getmaxx(window) / 2) - (length / 2)), "%lc", start);
    int drawTracker = 1;
    int i;
    for (i = 0; i < length - 1; i++) {
        mvwprintw(window, y, drawTracker + (int)((getmaxx(window) / 2) - (length / 2)), "%lc", mid);
        drawTracker++;
    }
    mvwprintw(window, y, (int)((getmaxx(window) / 2) + (length / 2)), "%lc", end);
}

void drawDebugText()
{
    string info = "Debug info:\nScreen size: " + to_string(getmaxx(stdscr)) + "x"
                  + to_string(getmaxy(stdscr)) + "\n";
    info += "Camera padding: " + to_string(CAMERA_PADDING) + "\n";
    mvadd_cppstr(10, 1, info);
}

void mvadd_cppstr(int y, int x, const std::string& str)
{
    stringstream ss(str);
    string line;

    while (std::getline(ss, line)) {
        mvaddstr(y++, x, line.c_str());
    }
}

void mvadd_cppstrvec(int y, int x, const std::vector<std::string>& vec)
{
    for (auto& line : vec) {
        mvaddstr(y++, x, line.c_str());
    }
}
