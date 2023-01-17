#include "../headers/snayai.hpp"

void snayai::utils::PopulateColorMap(std::map<int, sf::Color> &colorMap) {
    colorMap[0] = sf::Color::White;
    colorMap[1] = sf::Color(17, 75, 8, 255);
    colorMap[2] = sf::Color(90, 90, 140, 200);
}

std::pair<int, int> snayai::utils::randomPair(int max_x, int max_y) {
    return std::pair<int, int>(rand() % static_cast<int>(max_x), rand() % static_cast<int>(max_y));
}

