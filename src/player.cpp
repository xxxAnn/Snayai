#include "snayai.hpp"

std::pair<int, int> snayai::controller::Controller::poll(snayai::grid::Grid grid, sf::RenderWindow &win, std::shared_ptr<snayai::net::Net> net, snayai::snake::Snake &snake) {
    return std::make_pair(0, 1);
}

std::pair<int, int> snayai::controller::Player::poll(snayai::grid::Grid _, sf::RenderWindow &win, std::shared_ptr<snayai::net::Net> net, snayai::snake::Snake &snake) {
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

std::pair<int, int> snayai::controller::AI::poll(snayai::grid::Grid grid, sf::RenderWindow &win, std::shared_ptr<snayai::net::Net> net, snayai::snake::Snake &snake) {
    sf::Event event;
    if (win.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            win.close();
        }
    }
    // setup array

    float arr[6];

    std::fill_n(arr, 6, 0.0F);

    auto food_pos = grid.getFood();
    auto snake_pos = snake.getHeadPosition();
    auto snake_dir = snake.getDirection();

    auto food_direction = snayai::utils::getRelativeDirection(snake_pos, food_pos);

    std::pair<int, int> right_turn;
    std::pair<int, int> left_turn;
    if (snake_dir.first == 0) {
        right_turn = std::make_pair(snake_dir.second, 0);
        left_turn = std::make_pair(-snake_dir.second, 0);
    } else if (snake_dir.second == 0) {
        right_turn = std::make_pair(0, -snake_dir.first);
        left_turn = std::make_pair(0, snake_dir.first);
    }

    if (food_direction.first == snake_dir.first || food_direction.second == snake_dir.second) {
        arr[0] = 1.0F;
    } else if (food_direction.first == right_turn.first || food_direction.second == right_turn.second ) {
        arr[1] = 1.0F;
    }
    if (food_direction.first == left_turn.first || food_direction.second == left_turn.second) {
        arr[2] = 1.0F;
    }
    if (snake.isDeath(snake_pos.first+snake_dir.first, snake_pos.second+snake_dir.second, grid.getSize().first, grid.getSize().second)) {
        arr[3] = 1.0F;
    }
    if (snake.isDeath(snake_pos.first+right_turn.first, snake_pos.second+right_turn.second, grid.getSize().first, grid.getSize().second)) {
        arr[4] = 1.0F;
    }
    if (snake.isDeath(snake_pos.first+left_turn.first, snake_pos.second+left_turn.second, grid.getSize().first, grid.getSize().second)) {
        arr[5] = 1.0F;
    }
    

    torch::Tensor input = torch::from_blob(arr, {6});

    torch::Tensor output = net->forward(input);

    float result[3];

    result[0] = output[0].item<float>();
    result[1] = output[1].item<float>();
    result[2] = output[2].item<float>();

    std::pair<int, int> going;

    going = snake.getDirection();

    int movement = 0;


    float sum = result[0]+result[1]+result[2];
    int total_int = std::max(static_cast<int>(100*sum), 1);

    int ranum = rand();

    int num = (ranum % total_int);


    if (result[0] < num  && num < result[0]+result[1]) {
        movement = 1;
        if (snake_dir.first == 0) {
            going = std::make_pair(-snake_dir.second, 0);
        } else if (snake_dir.second == 0) {
            going = std::make_pair(0, snake_dir.first);
        }
    }
    
    if (num > result[0]+result[1]) {
        movement = 2;
        // (0, 1) -> (1, 0) 
        // (0, -1) -> (-1, 0) 
        // (1, 0) -> (0, -1)
        // (-1, 0) -> (0, 1)
        if (snake_dir.first == 0) {
            going = std::make_pair(snake_dir.second, 0);
        } else if (snake_dir.second == 0) {
            going = std::make_pair(0, -snake_dir.first);
        }
    }



    float actual[3];

    std::fill_n(actual, 3, 0.0F);

    if (grid.foodHook) {
        actual[previous_movement] = 5.0F;
    }
    if (grid.endingHook) {


        actual[previous_movement] = -25.0F;
    }
    torch::Tensor target = torch::from_blob(actual, {3});

    if (grid.endingHook || grid.foodHook || true) {
        if (started) {
            //std::printf("Training: \n");
            //std::cout << target << std::endl;
            //std::cout << prev_input << std::endl;
            //std::cout << net->forward(prev_input) << std::endl;
            //std::printf("\n");
            if (++counter % 10 == 0) {
                std::printf("Saving model\n");
                torch::save(net, "snake_ai.pt");
            }
            net->train(target, prev_input);
        } else {
            //std::printf("started");
            started = true;
        }
    }

    prev_input = input;
    previous_movement = movement;

    return going;
}