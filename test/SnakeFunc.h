#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<thread>

using namespace std;

int game = 1, direction = 0, sizeBodyOfSnake = 1;
int randomX = 0, randomY = 0;
bool good = true;

struct Point {
    int x = 0;
    int y = 0;
} p[100];


void snake() {
    sf::RenderWindow window(sf::VideoMode(1000, 700), "My window");
    sf::Time speed = sf::seconds(0.6f);
    sf::Event event;

    sf::Texture squareTex, backgroundTex, fruitTex;

    squareTex.loadFromFile("snake1.jpg");
    backgroundTex.loadFromFile("grass.jpg");
    fruitTex.loadFromFile("fruit.jpg");

    sf::Sprite snake(squareTex), fruit(fruitTex), background(backgroundTex);
    snake.setPosition(0, 0);
    fruit.setPosition(1000, 0);

    srand(time(NULL));
    randomX = 1 + rand() % (450);
    randomY = 1 + rand() % (450);
    for (int i = 0; i < 9; i++) {

        if (randomX <= (i + 1) * 50 && randomX > i * 50) {
            randomX = (i + 1) * 50;
        }
        if (randomY <= (i + 1) * 50 && randomY > i * 50) {
            randomY = (i + 1) * 50;
        }
    }


    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (game == 1) {
                    if (event.key.code == sf::Keyboard::Up && direction != 2) { direction = 3; }
                    if (event.key.code == sf::Keyboard::Down && direction != 3) { direction = 2; }
                    if (event.key.code == sf::Keyboard::Left && direction != 0) { direction = 1; }
                    if (event.key.code == sf::Keyboard::Right && direction != 1) { direction = 0; }
                }
            }
        }

        if (game == 1) {
            window.draw(background);

            for (int i = sizeBodyOfSnake; i > 0; i--) {
                p[i].x = p[i - 1].x;
                p[i].y = p[i - 1].y;
            }

            if (direction == 0) { p[0].x += 50; }
            if (direction == 1) { p[0].x -= 50; }
            if (direction == 2) { p[0].y += 50; }
            if (direction == 3) { p[0].y -= 50; }

            if (p[0].x > 1000) { p[0].x = 0; }
            if (p[0].x < 0) { p[0].x = 1000; }
            if (p[0].y > 700) { p[0].y = 0; }
            if (p[0].y < 0) { p[0].y = 700; }


            if (p[0].x == fruit.getPosition().x && p[0].y == fruit.getPosition().y) {
                sizeBodyOfSnake++;
                good = true;
                while (good) {
                    randomX = 1 + rand() % (450);
                    randomY = 1 + rand() % (450);
                    for (int i = 0; i < 9; i++) {

                        if (randomX <= (i + 1) * 50 && randomX > i * 50) {
                            randomX = (i + 1) * 50;
                        }
                        if (randomY <= (i + 1) * 50 && randomY > i * 50) {
                            randomY = (i + 1) * 50;
                        }
                        for (int i = 0; i < sizeBodyOfSnake; i++) {
                            if (randomX == p[i].x && randomY == p[i].y) { break; }
                            else if ((randomX != p[i].x || randomY != p[i].y) &&
                                     i == sizeBodyOfSnake - 1) { good = false; }
                        }
                    }
                }
            }
            fruit.setPosition(randomX, randomY);
            window.draw(fruit);

            for (int i = 0; i < sizeBodyOfSnake; i++) {
                snake.setPosition(p[i].x, p[i].y);
                window.draw(snake);
            }
            window.display();
            sf::sleep(speed);
        }
    }
}

