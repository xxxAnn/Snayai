#include "snayai.hpp"

void snayai::utils::PopulateColorMap(std::map<int, sf::Color> &colorMap) {
    colorMap[0] = sf::Color::White;
    colorMap[1] = sf::Color(17, 75, 8, 255);
    colorMap[2] = sf::Color(90, 90, 140, 200);
}

std::pair<int, int> snayai::utils::randomPair(int max_x, int max_y) {
    return std::pair<int, int>(rand() % static_cast<int>(max_x), rand() % static_cast<int>(max_y));
}

std::pair<int, int> snayai::utils::getRelativeDirection(std::pair<int, int> a, std::pair<int, int> b) {
    return std::pair<int, int>(getRelativeDirectionHorizontal(a, b), getRelativeDirectionVertical(a, b));
}

int snayai::utils::getRelativeDirectionHorizontal(std::pair<int, int> a, std::pair<int, int> b) {
    if (a.first < b.first) {
        return 1;
    } else if (a.first > b.first) {
        return -1;
    } else {
        return 0;
    }
}

int snayai::utils::getRelativeDirectionVertical(std::pair<int, int> a, std::pair<int, int> b) {
    if (a.second > b.second) {
        // a is below b
        return 1;
    } else if (a.second < b.second) {
        return -1;
    } else {
        return 0;
    }
}