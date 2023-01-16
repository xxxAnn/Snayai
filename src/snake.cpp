#include "../headers/snayai.hpp"

snayai::snake::Snake::Snake(int x, int y) {
    std::pair<int, int> pairToAdd(x, y);
    std::pair<int, int> otherPairToAdd(x-1, y);
    blocks.push_back(pairToAdd);
    blocks.push_back(otherPairToAdd);
    direction[0] = 1;
    direction[1] = 0;
}

void snayai::snake::Snake::move() {
    int end[2];
    std::pair<int, int> back;
    back = blocks.back();
    blocks.push_back({back.first + direction[0], back.second + direction[1]});
    blocks.erase(blocks.begin());
}

void snayai::snake::Snake::updateGrid(snayai::grid::Grid &grid) {
    for (auto block : blocks) {
        grid.setTile(block.first, block.second, snake_color);
    }
}

void snayai::snake::Snake::setDirection(int x, int y) {
    direction[0] = x;
    direction[1] = y;
}