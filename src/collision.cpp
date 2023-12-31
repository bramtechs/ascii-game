#include "collision.hpp"

#define ARRAY_SIZE 4096

int null = 2147483647;

int colX[ARRAY_SIZE];
int colY[ARRAY_SIZE];
int tracker = 0;

void clearCol()
{
    tracker = 0;
    int i;
    for (i = 0; i < ARRAY_SIZE; i++) {
        colY[tracker] = 0;
        colX[tracker] = 0;
        tracker++;
    }
    tracker = 0;
}

void printCol(char character, bool printAll)
{
    int i;
    for (i = 0; i < ARRAY_SIZE; i++) {
        if (colX[i] == 0 && colY[i] == 0 && !printAll) {
            return;
        } else {
            mvaddch(colY[i], colX[i], character);
        }
    }
}

void addCol(int y, int x)
{
    int i;
    for (i = 0; i < ARRAY_SIZE; i++) {
        if (colX[i] == x && colY[i] == y) {
            return;
        }
    }
    colY[tracker] = y;
    colX[tracker] = x;
    tracker++;
}

void tmvaddch(char character, int y, int x)
{
    int i;
    for (i = 0; i < ARRAY_SIZE; i++) {
        if (colX[i] == x && colY[i] == y) {
            mvaddch(y, x, character);
            return;
        }
    }
    colY[tracker] = y;
    colX[tracker] = x;
    tracker++;
}

bool colCheck(int y, int x)
{
    int i;
    for (i = 0; i < ARRAY_SIZE; i++) {
        if (colX[i] == x && colY[i] == y) {
            return true;
        }
    }
    return false;
}

void drawColLine(int x1, int y1, int x2, int y2, char c)
{
    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
    dx = x2 - x1;
    dy = y2 - y1;
    dx1 = fabs(dx);
    dy1 = fabs(dy);
    px = 2 * dy1 - dx1;
    py = 2 * dx1 - dy1;

    if (dy1 <= dx1) {
        if (dx >= 0) {
            x = x1;
            y = y1;
            xe = x2;
        } else {
            x = x2;
            y = y2;
            xe = x1;
        }

        tmvaddch(c, y, x);

        for (i = 0; x < xe; i++) {
            x++;
            if (px < 0) {
                px += 2 * dy1;
            } else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                    y++;
                } else {
                    y--;
                }

                px += 2 * (dy1 - dx1);
            }

            tmvaddch(c, y, x);
        }
    } else {
        if (dy >= 0) {
            x = x1;
            y = y1;
            ye = y2;
        } else {
            x = x2;
            y = y2;
            ye = y1;
        }

        tmvaddch(c, y, x);

        for (i = 0; y < ye; i++) {
            y++;
            if (py <= 0) {
                py += 2 * dx1;
            } else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                    x++;
                } else {
                    x--;
                }
                py += 2 * (dx1 - dy1);
            }

            tmvaddch(c, y, x);
        }
    }
}
