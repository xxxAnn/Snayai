#pragma once
#include "snayai.hpp"

namespace snayai {
    namespace ai {
        std::vector<int> generateTrainingData(snayai::grid::Grid &grid, snayai::snake::Snake &snake);
    }
}