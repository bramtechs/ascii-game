#pragma once
#include <string>
#include <unordered_map>

#define PI 3.14159265

extern int WIDTH;
extern int HEIGHT;
extern int CAMERA_PADDING;

struct Point {
    int x;
    int y;
};

enum Keys {
    UP = 'w',
    DOWN = 's',
    LEFT = 'a',
    RIGHT = 'd',

    ATT_UP = '8',
    ATT_DOWN = '2',
    ATT_LEFT = '4',
    ATT_RIGHT = '6',

    STATS = 'e',
    SEARCH = 'k',
    CENTER = 'c',

    CONFIRM = 'w',
    QUIT = 'q',
};

