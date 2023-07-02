#pragma once

#include "mapparser.hpp"

struct MapGeneratorSettings {
    bool ancientRoads = true;
    bool trees = true;
};

void generateMapDetails(AsciiMap& map, MapGeneratorSettings settings);
