#include "snayai.hpp"

namespace snayai {
    namespace controller {
        class Controller {
            public:
                virtual std::pair<int, int> poll(snayai::grid::Grid grid, sf::RenderWindow &win, std::shared_ptr<snayai::net::Net> net, snayai::snake::Snake &snake);
        };

        class Player : public Controller {
            public:
                std::pair<int, int> poll(snayai::grid::Grid _, sf::RenderWindow &win, std::shared_ptr<snayai::net::Net> net, snayai::snake::Snake &snake) override;
        };
        
        class AI : public Controller {
            public:
                std::pair<int, int> poll(snayai::grid::Grid grid, sf::RenderWindow &win, std::shared_ptr<snayai::net::Net> net, snayai::snake::Snake &snake) override;

            private:
                torch::Tensor prev_input;
                bool started = false;
                int previous_movement = 0;
                int no_food_for = 0;
                int counter = 0;
                double previous_distance;

        };
    }
}