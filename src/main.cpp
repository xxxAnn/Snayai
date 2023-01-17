#include "../headers/snayai.hpp"

int main() {
    sf::RenderWindow window(
        sf::VideoMode(snayai::constants::WINDOW_WIDTH, snayai::constants::WINDOW_HEIGHT), 
        snayai::constants::WINDOW_NAME
    );

    snayai::grid::Grid myGrid;
    snayai::snake::Snake mySnake(1, 1);

    myGrid.update(mySnake);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    mySnake.setDirection(-1, 0);
                }
                if (event.key.code == sf::Keyboard::Right) {
                    mySnake.setDirection(1, 0);
                }
                if (event.key.code == sf::Keyboard::Up) {
                    mySnake.setDirection(0, -1);
                }
                if (event.key.code == sf::Keyboard::Down) {
                    mySnake.setDirection(0, 1);
                }
            }
        }

        window.clear(sf::Color::Black);
        
        if (myGrid.tick(mySnake)) {
            std::ofstream myFile;

            myFile.open("training_data.txt", std::ios_base::app);

            std::vector<int> v = snayai::ai::generateTrainingData(myGrid, mySnake);

            for(int i = 0; i < v.size(); i++) {
                myFile << v[i] << ' ';
            }

            myFile << '\n';

            myFile.close();

            // generate a random input
            /*
            int myRandomInput = rand() % static_cast<int>(4);

            if (myRandomInput == 0) {
                mySnake.setDirection(-1, 0);
            }
            if (myRandomInput == 1) {
                mySnake.setDirection(1, 0);
            }
            if (myRandomInput == 2) {
                mySnake.setDirection(0, -1);
            }
            if (myRandomInput == 3) {
                mySnake.setDirection(0, 1);
            }
            */

            if (myGrid.ended) {
                myGrid = snayai::grid::Grid();
                mySnake = snayai::snake::Snake(1, 1);
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
