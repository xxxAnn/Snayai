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
    if (newHeadPositionX >= width-1 || newHeadPositionX < 0 || newHeadPositionY >= height-1 || newHeadPositionY < 0 || collidesSelf(newHeadPositionX, newHeadPositionY)) {
        std::cout << "You died." << std::endl;
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