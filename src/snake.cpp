#include "../headers/snayai.hpp"

snayai::snake::Snake::Snake(int x, int y) {
    std::pair<int, int> pairToAdd(x, y);
    std::pair<int, int> otherPairToAdd(x-1, y);
    blocks.push_back(pairToAdd);
    blocks.push_back(otherPairToAdd);
    direction[0] = 1;
    direction[1] = 0;
}

bool snayai::snake::Snake::move(int width, int height) {
    std::pair<int, int> back;
    back = blocks.back();
    int newHeadPositionX = back.first + direction[0];
    int newHeadPositionY = back.second + direction[1];
    if (isDeath(newHeadPositionX, newHeadPositionY, width, height)) {
        std::cout << "You died." << '\n';
        return true;
    } else {
        blocks.push_back({newHeadPositionX, newHeadPositionY});
        blocks.erase(blocks.begin());
        return false;
    }
}

std::pair<int, int> snayai::snake::Snake::getHeadPosition() {
    return blocks.back();
}

bool snayai::snake::Snake::collidesSelf(int newX, int newY) {
    for (int i = 1; i < blocks.size(); i++) {
        std::pair<int, int> block;
        block = blocks[i];
        if (block.first == newX && block.second == newY) {
            return true;
        }
    }
    return false;
}

bool snayai::snake::Snake::isDeath(int newX, int newY, int width, int height) {
    if (newX >= width-1 || newX < 0 || newY >= height-1 || newY < 0 || collidesSelf(newX, newY)) {
        return true;
    }
    return false;
}

void snayai::snake::Snake::addNewBlock() {
    std::pair<int, int> back;
    back = blocks.back();
    int newHeadPositionX = back.first + direction[0];
    int newHeadPositionY = back.second + direction[1];

    blocks.push_back({newHeadPositionX, newHeadPositionY});
}
 
void snayai::snake::Snake::setDirection(int x, int y) {
    if ((direction[0] != -x && direction[1] == 0) || (direction[1] != -y && direction[0] == 0)) {
        direction[0] = x;
        direction[1] = y;
    }
}