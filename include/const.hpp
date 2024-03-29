#pragma once
#include "snayai.hpp"

namespace snayai {
    namespace constants {
        // i have no idea what the units are
        static const int WINDOW_WIDTH = 640;
        static const int WINDOW_HEIGHT = 480;
        static const int TILE_SIZE = 56;
        static const int TILE_PADDING_SIZE = 4;
        static const float SNAKE_SPEED = 11; // tiles per second
        const std::string WINDOW_NAME = "Snayai";
    }
}