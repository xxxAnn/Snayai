#include "snayai.hpp"

int main() {
    sf::RenderWindow window(
        sf::VideoMode(snayai::constants::WINDOW_WIDTH, snayai::constants::WINDOW_HEIGHT), 
        snayai::constants::WINDOW_NAME
    );

    snayai::grid::Grid myGrid;
    snayai::snake::Snake mySnake(5, 5);
    std::shared_ptr<snayai::net::Net> net = std::make_shared<snayai::net::Net>(std::make_pair(16, 21));

    // this if is for loading the model
    // if the model is not found, it will be created
    // if the model is found, it will be loaded

    std::ifstream file;

    file.open("snake_ai.pt");

    if (file) {
        std::printf("Loading model from file\n");
        torch::load(net, "snake_ai.pt");
    }

    snayai::controller::AI controller;
    myGrid.update(mySnake);

    while (window.isOpen()) {

        if (myGrid.tick(mySnake)) {
            
            std::pair<int, int> direction = controller.poll(myGrid, window, net, mySnake);
            myGrid.endingHook = false;
            myGrid.foodHook = false;
            if (direction.first != 0 || direction.second != 0) {
                mySnake.setDirection(direction.first, direction.second);
            }

            window.clear(sf::Color::Black);

            if (myGrid.ended) {
                myGrid = snayai::grid::Grid();
                myGrid.endingHook = true;
                mySnake = snayai::snake::Snake(5, 5);
                myGrid.update(mySnake);
            }
        }

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
