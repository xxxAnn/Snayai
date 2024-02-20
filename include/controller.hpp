#include "snayai.hpp"

namespace snayai {
    namespace controller {
        class Controller {
            public:
                virtual std::pair<int, int> poll(snayai::grid::Grid grid, sf::RenderWindow &win);
        };

        class Player : public Controller {
            public:
                std::pair<int, int> poll(snayai::grid::Grid _, sf::RenderWindow &win) override;
        };
    }
}