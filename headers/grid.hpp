#pragma once
#include "snayai.hpp"

namespace snayai {
    namespace grid {
        class Grid {
            private:
                static const int width = snayai::constants::WINDOW_WIDTH/(snayai::constants::TILE_SIZE + snayai::constants::TILE_PADDING_SIZE) + 1;
                static const int height = snayai::constants::WINDOW_HEIGHT/(snayai::constants::TILE_SIZE + snayai::constants::TILE_PADDING_SIZE) + 1;
                int matrix[width][height];

            public:
                Grid();
                int getTile(int i, int j);
                int setTile(int i, int j, int value);
                void reset();
                sf::Color getTileColor(int i, int j);
        };
    }
}