#include "snayai.hpp"

snayai::grid::Grid::Grid() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            setTile(i, j, 0);
        }
    }
    now = clock();

    delay = 1/(snayai::constants::SNAKE_SPEED);
    delay *= CLOCKS_PER_SEC;

    addNewFood();
    score = 0;};

void snayai::grid::Grid::reset() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            setTile(i, j, 0);
        }
    }
}

void snayai::grid::Grid::addNewFood() {
    auto newFood = snayai::utils::randomPair(width-1, height-1);
    //std::cout << "Spawning food at (" << newFood.first << ", " << newFood.second << ")" << '\n';
    foods.push_back(newFood);
}

int snayai::grid::Grid::getTile(int i, int j) {
    return matrix[i][j];
}

std::pair<int, int> snayai::grid::Grid::getSize() {
    return std::make_pair(width, height);
}

void snayai::grid::Grid::setTile(int i, int j, int value) {
    matrix[i][j] = value;
}

//! Gets the sf::Color for a tile.
sf::Color snayai::grid::Grid::getTileColor(int i, int j) {
    std::map<int, sf::Color> colorMap;
    snayai::utils::PopulateColorMap(colorMap);

    return colorMap[getTile(i, j)];
}

bool snayai::grid::Grid::tick(snayai::snake::Snake &snake) {
    if (clock() - now >= delay && !ended) {
        now = clock();
        reset();
        ended = snake.move(width, height);
        auto snake_head = snake.getHeadPosition();
        if (checkCollision(snake_head)) {
            snake.addNewBlock();
            addNewFood();
            score++;
        }
        update(snake);
        return true;
    }
    return false;
}

bool snayai::grid::Grid::isFood(int x, int y) {
    for (auto food : foods) {
        if (food.first == x && food.second == y) {
            return true;
        }
    }
    return false;
}

bool snayai::grid::Grid::checkCollision(std::pair<int, int> &head) {
    for (int i = 0; i < foods.size(); i++) {
        std::pair<int, int> food;
        food = foods[i];

        if (food.first == head.first && food.second == head.second) {
            foods.erase(foods.begin()+i);
            return true;
        }

    }
    return false;
}  

void snayai::grid::Grid::update(snayai::snake::Snake &snake) {
    for (auto block : snake.blocks) {
        setTile(block.first, block.second, snake.snake_color);
    }
    for (auto food : foods) {
        setTile(food.first, food.second, food_color);
    }
}