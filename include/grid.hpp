#pragma once
#include "snayai.hpp"

namespace snayai {
    namespace grid {
        class Grid {
            public: 
                static const int width = snayai::constants::WINDOW_WIDTH/(snayai::constants::TILE_SIZE + snayai::constants::TILE_PADDING_SIZE) + 1;
                static const int height = snayai::constants::WINDOW_HEIGHT/(snayai::constants::TILE_SIZE + snayai::constants::TILE_PADDING_SIZE) + 1;
                bool ended = false;
                
            private:
                std::vector<std::pair<int, int>> foods;   
                int matrix[width][height];
                clock_t now;
                float delay;
                int food_color = 2;

            public:
                Grid();
                int getTile(int i, int j);
                void setTile(int i, int j, int value);
                bool checkCollision(std::pair<int, int> &head);
                void reset();
                void addNewFood();
                bool tick(snayai::snake::Snake &snake);
                void update(snayai::snake::Snake &snake);
                bool isFood(int x, int y);
                std::pair<int, int> getSize();
                int score;
                sf::Color getTileColor(int i, int j);
        };
    }
}