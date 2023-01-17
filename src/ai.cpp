#include "../headers/snayai.hpp"

int getTileType(snayai::grid::Grid &grid, snayai::snake::Snake &snake, int x, int y) {
    if (x < 0 || y < 0 || x >= grid.width || y >= grid.height) {
        return 1;
    } else if (snake.isDeath(x, y, grid.width, grid.height)) {
        return 1;
    } else if (grid.isFood(x, y)) {
        return 2;
    }
    return 0;
}

std::vector<int> snayai::ai::generateTrainingData(snayai::grid::Grid &grid, snayai::snake::Snake &snake) {
    int scoreDelta;
    int x;
    int y;
    int left;
    int right;
    int top;
    int bottom;
    std::pair<int, int> head;

    scoreDelta = grid._ai_training_current_score - grid._ai_training_previous_score;
    head = snake.getHeadPosition();
    x = head.first;
    y = head.second;
    // Find the block state to the left.
    left = getTileType(grid, snake, x-1, y);
    right = getTileType(grid, snake, x+1, y);
    top = getTileType(grid, snake, x, y-1);
    bottom = getTileType(grid, snake, x, y+1);

    return {scoreDelta, left, right, top, bottom};
}

