#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "../headers/const.hpp"

int main() {
    sf::RenderWindow window(
        sf::VideoMode(snayai::constants::WINDOW_WIDTH, snayai::constants::WINDOW_HEIGHT), 
        snayai::constants::WINDOW_NAME
    );

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);

        window.display();
    }

    return 0;
}

