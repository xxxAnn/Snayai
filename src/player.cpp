#include "snayai.hpp"

std::pair<int, int> snayai::controller::Controller::poll(snayai::grid::Grid grid, sf::RenderWindow &win) {
    return std::make_pair(0, 1);
}

std::pair<int, int> snayai::controller::Player::poll(snayai::grid::Grid _, sf::RenderWindow &win) {
    sf::Event event;
    sf::Clock clock;
    while (win.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            win.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left) {
                return std::make_pair(-1, 0);
            }
            if (event.key.code == sf::Keyboard::Right) {
                return std::make_pair(1, 0);
            }
            if (event.key.code == sf::Keyboard::Up) {
                return std::make_pair(0, -1);
            }
            if (event.key.code == sf::Keyboard::Down) {
                return std::make_pair(0, 1);
            }
        }
    }
    return std::make_pair(0, 0);
}