#pragma once
#include "snayai.hpp"

namespace snayai {
    namespace snake {
        class Snake {
            private:
                std::vector<std::pair<int, int>> blocks;
                int direction[2];
                int snake_color = 1;

            public:
                Snake(int x, int y);
                void move();
                void updateGrid(snayai::grid::Grid &grid);
                void setDirection(int x, int y);
        };
    }
}

