#include "snayai.hpp"

namespace snayai {
    namespace utils {
        void PopulateColorMap(std::map<int, sf::Color> &colorMap);

        std::pair<int, int> randomPair(int max_x, int max_y);
        std::pair<int, int> getRelativeDirection(std::pair<int, int> a, std::pair<int, int> b);
        int getRelativeDirectionHorizontal(std::pair<int, int> a, std::pair<int, int> b);
        int getRelativeDirectionVertical(std::pair<int, int> a, std::pair<int, int> b);
    }
}