#include <cstdio>
#include <curses.h>
#include "gui.hpp"
#include <string>
#include <cstring>
#include <sstream>

#include "common.hpp"
#include "player.hpp"

using namespace std;

const std::unordered_map<Keys, std::string> KeyDescriptions = {
    { Keys::SEARCH, "Magnifying glass" },
    { Keys::STATS, "Open stats" },
};

static int cachedWidth;
static int cachedHeight;

Point drawWin(int y, int x, int width, int height, Anchor anchor)
{
    // apply anchor first
    if (anchor == BOTTOM_RIGHT) {
        x = WIDTH - x - width;
        y = HEIGHT - y - height;
    }

    cachedWidth = width;
    cachedHeight = height;

    char* fillerTopBottom = new char[width + 1];
    fillerTopBottom[0] = '+';
    fillerTopBottom[width - 1] = '+';
    fillerTopBottom[width] = '\0';
    memset(fillerTopBottom + 1, '-', width - 2);

#if 1
    // debug draw size
    // FIXME: probably leaks
    char size[20];
    sprintf(size, "%ix%i", width, height);
    memcpy(fillerTopBottom, size, std::min(strlen(size), strlen(fillerTopBottom)));
#endif

    char* filler = new char[width + 1];
    filler[0] = '|';
    filler[width - 1] = '|';
    filler[width] = '\0';
    memset(filler + 1, ' ', width - 2);

    // draw window box
    int yy = y;
    mvaddstr(yy, x, fillerTopBottom);
    while (yy < y + height - 1) {
        mvaddstr(++yy, x, filler);
    }
    mvaddstr(yy, x, fillerTopBottom);

    delete[] filler;
    delete[] fillerTopBottom;

    constexpr int MARGIN = 2;
    return { x + MARGIN, y + MARGIN };
}

void drawProgressBar(WINDOW* window, wchar_t full, wchar_t empty, int percentFull, int y, int start, int end)
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

void drawDebugText(Point& camera)
{
    static char buffer[1024] = { 0 };
    sprintf(buffer,
            "Debug info:\nPlayer pos: %dx%d\nScreen size: %d by %d\nCamera padding: %d\nCamera pos: %dx%d",
            Player::get().pos.x, Player::get().pos.y,
            WIDTH,
            HEIGHT,
            CAMERA_PADDING,
            camera.x,
            camera.y);
    mvadd_cppstr(10, 1, buffer);
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

WINDOW* drawFullscreenWindow()
{
    WINDOW* window = subwin(stdscr, getmaxy(stdscr) - 4, getmaxx(stdscr) - 4, 2, 2);
    int maxx = getmaxx(window);

    werase(window);

    // fix the spacing

    box(window, ACS_VLINE, ACS_HLINE);
    // I HATE THIS LIBRARY
    mvwprintw(window, 0, 0, "%lc", L'╭');
    mvwprintw(window, 0, maxx - 1, "%lc", L'╮');
    mvwprintw(window, getmaxy(window) - 1, 0, "%lc", L'╰');
    mvwprintw(window, getmaxy(window) - 1, maxx - 1, "%lc", L'╯');

    return window;
}
