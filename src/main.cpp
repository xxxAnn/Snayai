#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

int main() {
    sf::RenderWindow window(
        sf::VideoMode(640, 480), 
        "Hello World"
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

