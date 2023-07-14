#include <vector>
#include <cmath>

#include "mapgenerator.hpp"
#include "common.hpp"

using namespace std;

// return '|', '/', '\' or '-' depending on the direction of the pipe
char pipeTowards(Point src, Point target)
{
    if (src.x == target.x) {
        return '|';
    } else if (src.y == target.y) {
        return '-';
    } else if (src.x < target.x && src.y < target.y) {
        return '\\';
    } else if (src.x < target.x && src.y > target.y) {
        return '/';
    } else if (src.x > target.x && src.y < target.y) {
        return '/';
    } else if (src.x > target.x && src.y > target.y) {
        return '\\';
    }
    return 'x';
}

char pipeTowards90Deg(Point src, Point target)
{
    if (src.x == target.x) {
        return '-';
    } else if (src.y == target.y) {
        return '|';
    } else if (src.x < target.x && src.y < target.y) {
        return '/';
    } else if (src.x < target.x && src.y > target.y) {
        return '\\';
    } else if (src.x > target.x && src.y < target.y) {
        return '\\';
    } else if (src.x > target.x && src.y > target.y) {
        return '/';
    }
    return 'x';
}

void fillCircle(AsciiMap& map, int x, int y, float radius, bool border = false)
{
    for (int xx = x - radius; xx < x + radius; xx++) {
        for (int yy = y - radius; yy < y + radius; yy++) {
            double distance = sqrt(pow((xx - x), 2) + pow((yy - y), 2));
            if (distance < radius / 2) {
                map[yy][xx] = 'O';
            } else if (border && abs(distance - radius / 2) < 1.f) {
                map[yy][xx] = pipeTowards90Deg({ xx, yy }, { x, y });
            }
        }
    }
}

void generateTreeStumps(AsciiMap& map)
{
    vector<Point> trees;

    // find tree stumps
    wchar_t prev = 'x';
    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            wchar_t cur = map[y][x];
            if (prev == 'O' && cur == 'O') {
                trees.push_back({ x - 1, y });
            }
            prev = cur;
        }
    }

    // generate tree stumps
    for (const auto [x, y] : trees) {
        float radius = 2.2f;
        fillCircle(map, x, y, radius, true);
        map[y][x] = 'O';
        map[y][x + 1] = 'O';
    }
}

void generateMapDetails(AsciiMap& map, MapGeneratorSettings settings)
{
    if (settings.trees) {
        generateTreeStumps(map);
    }
}
