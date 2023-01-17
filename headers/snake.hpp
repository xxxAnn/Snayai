#pragma once
#include "snayai.hpp"

namespace snayai {
    namespace snake {
        class Snake {
            private:
                int direction[2];
                
            public:
                std::vector<std::pair<int, int>> blocks;
                std::pair<int, int> getHeadPosition();
                int snake_color = 1;
                Snake(int x, int y);
                bool move(int width, int height);
                bool collidesSelf(int newX, int newY);
                void setDirection(int x, int y);
                void addNewBlock();
        };
    }
}

