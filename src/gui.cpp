#include <curses.h>
#include "gui.hpp"

static int cachedWidth;
static int cachedHeight;
WINDOW* drawWinBegin(int x, int y, int width, int height)
{
    cachedWidth = width;
    cachedHeight = height;

    WINDOW* window = subwin(stdscr, x, y, width, height);

    werase(window);

    // fix the spacing

    box(window, ACS_VLINE, ACS_HLINE);
    // I HATE THIS LIBRARY
    mvwprintw(window, 0, 0, "%lc", L'╭');
    mvwprintw(window, 0, width - 1, "%lc", L'╮');
    mvwprintw(window, getmaxy(window) - 1, 0, "%lc", L'╰');
    mvwprintw(window, getmaxy(window) - 1, width - 1, "%lc", L'╯');

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