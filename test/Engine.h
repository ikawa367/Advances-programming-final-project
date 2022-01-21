#include <iostream>
#include <stdlib.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<vector>
#include <deque>
#include "Snake.h"
#include "Wall.h"
#include "Apple.h"

//this engine has the controll over everything and every classes
class Engine {
    sf::RenderWindow snakeWindow;

    //vectors represent
    vector<SnakeSection> snake;
    vector<SnakeSection> snake2;
    int snake1Direction;
    int snake2Direction;

    //double ended queues for snake 1 and snake 2
    deque<int> directionQueue1;
    deque<int> directionQueue2;

    //fruits locations in float number and an object of fruit class
    Apple apple;
    sf::Vector2f appleLocation1;
    sf::Vector2f appleLocation2;

    //walls locations in float number and an object of walls class
    Wall wall;
    sf::Vector2f wallLocation1;
    sf::Vector2f wallLocation2;

    //snakes general infos
    int speed;
    int sectionsToAdd1;
    int sectionsToAdd2;

    //SFXs for eating fruit and bumping to wall
    sf::Music notif;
    sf::Music bite;

    //manages the delays from start point / head & tail moves
    sf::Time timeSinceLastMove;

public:

    //user defined data type that has limited values of positions
    enum direction {
        UP, RIGHT, DOWN, LEFT
    };

    //the constructor
    Engine() {
        snake1Direction = direction::RIGHT;
        snake2Direction = direction::LEFT;
        timeSinceLastMove = sf::Time::Zero;

        newSnake();
        moveApple1();
        moveApple2();
        moveWall();

        notif.openFromFile("notif.wav");
        bite.openFromFile("bite.wav");

        //refers to the when apple is eaten by two snakes line 195 & 199
        sectionsToAdd1 = 0;
        sectionsToAdd2 = 0;
    }

    //function which represent the speed in settings
    void setSpeed(bool hard) {
        if (hard == true) {
            speed = 4;
        } else {
            speed = 2;
        }
    }

    // function represents inputs of keyboard to move 2 snakes
    void input() {
        sf::Event event;
        while (snakeWindow.pollEvent(event)) {
            if (event.type == (sf::Event::Closed)) {
                snakeWindow.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    addDirection1(direction::UP);
                } else if (event.key.code == sf::Keyboard::Down) {
                    addDirection1(direction::DOWN);
                } else if (event.key.code == sf::Keyboard::Right) {
                    addDirection1(direction::RIGHT);
                } else if (event.key.code == sf::Keyboard::Left) {
                    addDirection1(direction::LEFT);
                } else if (event.key.code == sf::Keyboard::W) {
                    addDirection2(direction::UP);
                } else if (event.key.code == sf::Keyboard::S) {
                    addDirection2(direction::DOWN);
                } else if (event.key.code == sf::Keyboard::D) {
                    addDirection2(direction::RIGHT);
                } else if (event.key.code == sf::Keyboard::A) {
                    addDirection2(direction::LEFT);
                }
            }
        }
    }

    //this two functions below get the directions of keyboard and update the snake movements
    void addDirection1(int newDirection) {
        if (directionQueue1.empty()) {
            directionQueue1.push_back(newDirection);
        } else if (!directionQueue1.empty()) {
            if (directionQueue1.back() != newDirection) {
                directionQueue1.push_back(newDirection);
            }
        }
    }

    void addDirection2(int newDirection2) {
        if (directionQueue2.empty()) {
            directionQueue2.push_back(newDirection2);
        } else if (!directionQueue2.empty()) {
            if (directionQueue2.back() != newDirection2) {
                directionQueue2.push_back(newDirection2);
            }
        }
    }

    //the update of whole game is in here from head/tail/directions ...
    void update() {
        if (timeSinceLastMove.asSeconds() >= sf::seconds(1.f / float(speed)).asSeconds()) {
            sf::Vector2f thisSectionPosition = snake[0].getPosition1();
            sf::Vector2f thisSectionPosition2 = snake2[0].getPosition2();
            sf::Vector2f lastSectionPosition = thisSectionPosition;
            sf::Vector2f lastSectionPosition2 = thisSectionPosition2;

            //updates the movement of snake using deque(something.front) and enum that we gave, for snake 1
            if (!directionQueue1.empty()) {
                switch (snake1Direction) {
                    case direction::UP:
                        if (directionQueue1.front() != direction::DOWN) {
                            snake1Direction = directionQueue1.front();
                        }
                        break;
                    case direction::DOWN:
                        if (directionQueue1.front() != direction::UP) {
                            snake1Direction = directionQueue1.front();
                        }
                        break;
                    case direction::LEFT:
                        if (directionQueue1.front() != direction::RIGHT) {
                            snake1Direction = directionQueue1.front();
                        }
                        break;
                    case direction::RIGHT:
                        if (directionQueue1.front() != direction::LEFT) {
                            snake1Direction = directionQueue1.front();
                        }
                        break;
                }
                directionQueue1.pop_front();
            }

            //updates the movement of snake using deque(something.front) and enum that we gave, for snake 2
            if (!directionQueue2.empty()) {
                switch (snake2Direction) {
                    case direction::UP:
                        if (directionQueue2.front() != direction::DOWN) {
                            snake2Direction = directionQueue2.front();
                        }
                        break;
                    case direction::DOWN:
                        if (directionQueue2.front() != direction::UP) {
                            snake2Direction = directionQueue2.front();
                        }
                        break;
                    case direction::LEFT:
                        if (directionQueue2.front() != direction::RIGHT) {
                            snake2Direction = directionQueue2.front();
                        }
                        break;
                    case direction::RIGHT:
                        if (directionQueue2.front() != direction::LEFT) {
                            snake2Direction = directionQueue2.front();
                        }
                        break;
                }
                directionQueue2.pop_front();
            }

            //refers to the when the apple is eaten by snakes lines 68 & 69
            if (sectionsToAdd1) {
                addSnakeSection1();
                sectionsToAdd1--;
            }
            if (sectionsToAdd2) {
                addSnakeSection2();
                sectionsToAdd2--;
            }

            //update snake1 head position
            switch (snake1Direction) {
                case direction::RIGHT:
                    if (thisSectionPosition.x > 800) {
                        thisSectionPosition.x = -20;
                        snake[0].setPosition1(sf::Vector2f(thisSectionPosition.x, thisSectionPosition.y));
                    }
                    snake[0].setPosition1(sf::Vector2f(thisSectionPosition.x + 20, thisSectionPosition.y));
                    break;

                case direction::DOWN:
                    if (thisSectionPosition.y > 600) {
                        thisSectionPosition.y = -20;
                        snake[0].setPosition1(sf::Vector2f(thisSectionPosition.x, thisSectionPosition.y + 20));
                    }
                    snake[0].setPosition1(sf::Vector2f(thisSectionPosition.x, thisSectionPosition.y + 20));
                    break;

                case direction::LEFT:
                    if (thisSectionPosition.x - 20 < 0) {
                        thisSectionPosition.x = 800;
                        snake[0].setPosition1(sf::Vector2f(thisSectionPosition.x - 20, thisSectionPosition.y));
                    }
                    snake[0].setPosition1(sf::Vector2f(thisSectionPosition.x - 20, thisSectionPosition.y));
                    break;

                case direction::UP:
                    if (thisSectionPosition.y - 20 < 0) {
                        thisSectionPosition.y = 600;
                        snake[0].setPosition1(sf::Vector2f(thisSectionPosition.x, thisSectionPosition.y - 20));
                    }
                    snake[0].setPosition1(sf::Vector2f(thisSectionPosition.x, thisSectionPosition.y - 20));
                    break;
            }

            //update snake2 head position
            switch (snake2Direction) {
                case direction::RIGHT:
                    if (thisSectionPosition2.x > 800) {
                        thisSectionPosition2.x = -20;
                        snake2[0].setPosition2(sf::Vector2f(thisSectionPosition2.x + 20, thisSectionPosition2.y));
                    }
                    snake2[0].setPosition2(sf::Vector2f(thisSectionPosition2.x + 20, thisSectionPosition2.y));
                    break;

                case direction::DOWN:
                    if (thisSectionPosition2.y > 600) {
                        thisSectionPosition2.y = -20;
                        snake2[0].setPosition2(sf::Vector2f(thisSectionPosition2.x, thisSectionPosition2.y + 20));
                    }
                    snake2[0].setPosition2(sf::Vector2f(thisSectionPosition2.x, thisSectionPosition2.y + 20));
                    break;

                case direction::LEFT:
                    if (thisSectionPosition2.x - 20 < 0) {
                        thisSectionPosition2.x = 800;
                        snake2[0].setPosition2(sf::Vector2f(thisSectionPosition2.x - 20, thisSectionPosition2.y));
                    }
                    snake2[0].setPosition2(sf::Vector2f(thisSectionPosition2.x - 20, thisSectionPosition2.y));
                    break;

                case direction::UP:
                    if (thisSectionPosition2.y - 20 < 0) {
                        thisSectionPosition2.y = 600;
                        snake2[0].setPosition2(sf::Vector2f(thisSectionPosition2.x, thisSectionPosition2.y - 20));
                    }
                    snake2[0].setPosition2(sf::Vector2f(thisSectionPosition2.x, thisSectionPosition2.y - 20));
                    break;
            }

            //update snake1 tail position
            for (int i = 1; i < snake.size(); i++) {
                thisSectionPosition = snake[i].getPosition1();
                snake[i].setPosition1(lastSectionPosition);
                lastSectionPosition = thisSectionPosition;
            }

            //update snake2 tail position
            for (int i = 1; i < snake2.size(); i++) {
                thisSectionPosition2 = snake2[i].getPosition2();
                snake2[i].setPosition2(lastSectionPosition2);
                lastSectionPosition2 = thisSectionPosition2;
            }

            //without thease for eaches the snakes wont move eventhough you have updated their head and tail position
            for (auto &i: snake) {
                i.update();
            }
            for (auto &i: snake2) {
                i.update();
            }

            timeSinceLastMove = sf::Time::Zero;

            //when the apple 1 is eaten by snake 1
            if (snake[0].getShape1().getGlobalBounds().intersects(apple.getSprite1().getGlobalBounds())) {
                bite.stop();
                bite.play();
                sectionsToAdd1 += 2;
                speed += 1;
                moveApple1();
            }
            //when the apple 1 is eaten by snake 2
            if (snake2[0].getShape2().getGlobalBounds().intersects(apple.getSprite1().getGlobalBounds())) {
                bite.stop();
                bite.play();
                sectionsToAdd2 += 2;
                speed += 1;
                moveApple1();
            }
            //when the apple 2 is eaten by snake 1
            if (snake[0].getShape1().getGlobalBounds().intersects(apple.getSprite2().getGlobalBounds())) {
                bite.stop();
                bite.play();
                sectionsToAdd1 += 2;
                speed += 1;
                moveApple2();
            }
            //when the apple 2 is eaten by snake 2
            if (snake2[0].getShape2().getGlobalBounds().intersects(apple.getSprite2().getGlobalBounds())) {
                bite.stop();
                bite.play();
                sectionsToAdd2 += 2;
                speed += 1;
                moveApple2();
            }

            //when two snakes bump to each other the game is over with an SFX
            for (int i = 1; i < snake.size(); i++) {
                if (snake[0].getShape1().getGlobalBounds().intersects(snake[i].getShape1().getGlobalBounds()) ||
                    snake2[0].getShape2().getGlobalBounds().intersects(snake[i].getShape1().getGlobalBounds()) ||
                    snake2[0].getShape2().getGlobalBounds().intersects(snake[0].getShape1().getGlobalBounds())) {
                    notif.stop();
                    notif.play();
                    restart();
                    snakeWindow.close();
                }
            }
            for (int i = 1; i < snake2.size(); i++) {
                if (snake2[0].getShape2().getGlobalBounds().intersects(snake2[i].getShape2().getGlobalBounds()) ||
                    snake[0].getShape1().getGlobalBounds().intersects(snake2[i].getShape2().getGlobalBounds()) ||
                    snake[0].getShape1().getGlobalBounds().intersects(snake2[0].getShape2().getGlobalBounds())) {
                    notif.stop();
                    notif.play();
                    restart();
                    snakeWindow.close();
                }
            }

            //if snakes bang their heads to walls the game is over
            if (snake[0].getShape1().getGlobalBounds().intersects(
                    sf::Rect<float>(wallLocation1.x, wallLocation1.y, 20, 60)) ||
                snake2[0].getShape2().getGlobalBounds().intersects(
                        sf::Rect<float>(wallLocation1.x, wallLocation1.y, 20, 60)) ||
                snake[0].getShape1().getGlobalBounds().intersects(
                        sf::Rect<float>(wallLocation2.x, wallLocation2.y, 60, 20)) ||
                snake2[0].getShape2().getGlobalBounds().intersects(
                        sf::Rect<float>(wallLocation2.x, wallLocation2.y, 60, 20))) {
                notif.stop();
                notif.play();
                restart();
                snakeWindow.close();
            }
            timeSinceLastMove = sf::Time::Zero;
        }
    }

    //draws snakes, walls, apples on window
    void draw() {
        snakeWindow.clear(sf::Color::Black);
        wall.setWallPosition(wallLocation1, 0);
        wall.setWallPosition(wallLocation2, 1);
        snakeWindow.draw(wall.getWall(0));
        snakeWindow.draw(wall.getWall(1));
        snakeWindow.draw(apple.getSprite1());
        snakeWindow.draw(apple.getSprite2());
        for (auto &s: snake) {
            for (auto &s: snake) {
                snakeWindow.draw(s.getShape1());
            }
            for (auto &s: snake2) {
                snakeWindow.draw(s.getShape2());
            }
            snakeWindow.display();
        }
    }

    //runs or restart the panels
    void run() {
        sf::Clock clock;
        snakeWindow.create(sf::VideoMode(800, 600), "main game");
        snakeWindow.setFramerateLimit(60);
        //Game loop. Runs and gets inputs until the window is closed.
        while (snakeWindow.isOpen()) {
            sf::Time dt = clock.restart();
            timeSinceLastMove += dt;
            input();
            update();
            draw();
        }
        restart();
    }

    //makes new snakes again when game is restarted
    void newSnake() {
        snake.clear();
        snake2.clear();
        snake.push_back(sf::Vector2f(100, 500));
        snake.push_back(sf::Vector2f(80, 500));
        snake.push_back(sf::Vector2f(60, 500));
        snake2.push_back(sf::Vector2f(700, 500));
        snake2.push_back(sf::Vector2f(720, 500));
        snake2.push_back(sf::Vector2f(740, 500));
    }

    //pushes back the body tile by tile refers to the when apple is eaten snake 1
    void addSnakeSection1() {
        sf::Vector2f newSectionPosition = snake[snake.size() - 1].getPosition1(); //-1 because index starts with 0
        snake.push_back(newSectionPosition);
    }

    //pushes back the body tile by tile refers to the when apple is eaten snake 2
    void addSnakeSection2() {
        sf::Vector2f newSectionPosition = snake2[snake2.size() - 1].getPosition2(); //-1 because index starts with 0
        snake2.push_back(newSectionPosition);
    }

    //sets and updates random position of apple 1
    void moveApple1() {
        bool badLocation = false;
        srand(time(0));
        do {
            if ((appleLocation1.x = (rand() % 40) * 20 + 100) > 400 ||
                (appleLocation1.x = (rand() % 40) * 20 + 100) < 0) {
                (appleLocation1.x = 100);
                (appleLocation1.y = 300);
            }
            appleLocation1.x = (rand() % 40) * 20;

            if ((appleLocation1.y = (rand() % 30) * 20 + 100) > 400 ||
                (appleLocation1.y = (rand() % 30) * 20 + 100) < 0) {
                (appleLocation1.y = 300);
                (appleLocation1.x = 100);
            }
            appleLocation1.y = (rand() % 30) * 20;

            for (auto &i: snake) {
                if (i.getShape1().getGlobalBounds().intersects(
                        sf::Rect<float>(appleLocation1.x, appleLocation1.y, 20, 20)) &&
                    i.getShape1().getGlobalBounds().intersects(
                            sf::Rect<float>(appleLocation2.x, appleLocation2.y, 20, 20))) {
                    badLocation = true;
                    break;
                }
            }
        } while (badLocation);
        apple.setPosition(appleLocation1, 0);
    }

    //sets and updates random position of apple 2
    void moveApple2() {
        bool badLocation = false;
        srand(time(0));
        do {
            appleLocation2.x = (rand() % 40) * 20;
            appleLocation2.y = (rand() % 30) * 20;
            for (auto &i: snake) {
                if (i.getShape2().getGlobalBounds().intersects(
                        sf::Rect<float>(appleLocation1.x, appleLocation1.y, 20, 20)) &&
                    i.getShape2().getGlobalBounds().intersects(
                            sf::Rect<float>(appleLocation2.x, appleLocation2.y, 20, 20))) {
                    badLocation = true;
                    break;
                }
            }
        } while (badLocation);
        apple.setPosition(appleLocation2, 1);
    }

    //sets and updates random position of walls
    void moveWall() {
        while (1) {
            wallLocation1.x = (rand() % 40) * 20;
            wallLocation1.y = (rand() % 10) * 20;
            wallLocation2.x = (rand() % 10) * 20;
            wallLocation2.y = (rand() % 40) * 20;
            if (std::abs(wallLocation1.x - wallLocation2.x) > 60 && std::abs(wallLocation1.y - wallLocation2.y) > 60 &&
                abs(appleLocation1.x - wallLocation1.x) > 0 && abs(appleLocation2.x - wallLocation2.x) > 0 &&
                abs(appleLocation1.x - wallLocation2.x) > 0 && abs(appleLocation1.x - wallLocation2.x) &&
                wallLocation1.x < 600 && wallLocation1.y < 600 && wallLocation2.x < 600 && wallLocation2.y < 600) {
                break;
            }
        }
        wall.setWallPosition(wallLocation1, 0);
        wall.setWallPosition(wallLocation2, 1);
    }

    //restarts the panel when game is over or X is pressed
    void restart() {
        snake1Direction = RIGHT;
        snake2Direction = LEFT;
        timeSinceLastMove = sf::Time::Zero;
        directionQueue1.clear();
        directionQueue2.clear();
        newSnake();
        moveWall();
        moveApple1();
        moveApple2();
    }
};