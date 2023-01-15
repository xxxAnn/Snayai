#include "../headers/snayai.hpp"


snayai::grid::Grid::Grid() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            matrix[i][j] = 0;
        }
    }
};

int snayai::grid::Grid::getTile(int i, int j) {
    return matrix[i][j];
}

//! Gets the sf::Color for a tile.
sf::Color snayai::grid::Grid::getTileColor(int i, int j) {
    std::map<int, sf::Color> colorMap;
    snayai::utils::PopulateColorMap(colorMap);

    return colorMap[getTile(i, j)];
}