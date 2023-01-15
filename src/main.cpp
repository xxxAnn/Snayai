#include "../headers/snayai.hpp"

int main() {
    sf::RenderWindow window(
        sf::VideoMode(snayai::constants::WINDOW_WIDTH, snayai::constants::WINDOW_HEIGHT), 
        snayai::constants::WINDOW_NAME
    );

    snayai::grid::Grid myGrid;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);

        /*
        The following section calculates the amount of square tiles there should be horizontally and vertically
        based on the size of each tile and the size of their padding. It then draws all of those tiles on the screen. 
        The tile padding is shifted to the right by half a tile so that the tiles on the side get extra padding towards the outside.
        */

        int h = 0;

        int horizontal_tiles = snayai::constants::WINDOW_WIDTH/(snayai::constants::TILE_SIZE + snayai::constants::TILE_PADDING_SIZE);
        int vertical_tiles = snayai::constants::WINDOW_HEIGHT/(snayai::constants::TILE_SIZE + snayai::constants::TILE_PADDING_SIZE);

        while (h <= horizontal_tiles) {
            int v = 0;
            while (v <= vertical_tiles) {
                sf::RectangleShape rec(sf::Vector2f(snayai::constants::TILE_SIZE, snayai::constants::TILE_SIZE));

                rec.setFillColor(myGrid.getTileColor(h, v));
                rec.setPosition(h * snayai::constants::TILE_SIZE + (h+0.5) * (snayai::constants::TILE_PADDING_SIZE), v * snayai::constants::TILE_SIZE + (v+0.5) * snayai::constants::TILE_PADDING_SIZE);

                window.draw(rec);
                v++;
            }
            h++;
        }

        window.display();
    }

    return 0;
}
