#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<vector>
#include <deque>
#include <thread>
#include "ClassApple.h"

class Apple {
    sf::RectangleShape sprite;
    sf::RectangleShape sprite2;
public:
    Apple() {
        sf::Vector2f startPosition1(400, 400);
        sf::Vector2f startPosition2(300, 500);
        sprite.setSize(sf::Vector2f(20, 20));
        sprite2.setSize(sf::Vector2f(20, 20));
        sprite.setFillColor(sf::Color::Red);
        sprite2.setFillColor(sf::Color::Blue);
        sprite.setPosition(startPosition1);
        sprite2.setPosition(startPosition2);
    }

    void setPosition(sf::Vector2f newPosition, bool firstOrsecond) {
        if (firstOrsecond == 0) {
            sprite.setPosition(newPosition);
        } else {
            sprite2.setPosition(newPosition);
        }
    }

    //draw function needs getSprite.
    sf::RectangleShape getSprite1() {
        return sprite;
    }

    sf::RectangleShape getSprite2() {
        return sprite2;
    }
};

class snakeSection {
    sf::Vector2f position1;
    sf::Vector2f position2;
    sf::RectangleShape section1;
    sf::RectangleShape section2;
public:
    snakeSection(sf::Vector2f startPosition1) {
        sf::Vector2f startPosition2;
        startPosition2.x = startPosition1.x;
        startPosition2.y = startPosition1.y;
        section1.setSize(sf::Vector2f(20, 20));
        section2.setSize(sf::Vector2f(20, 20));
        section1.setFillColor(sf::Color::Green);
        section2.setFillColor(sf::Color::Yellow);
        section1.setPosition(startPosition1);
        section2.setPosition(startPosition1.x, startPosition1.y);
        position1 = startPosition1;
        position2 = startPosition2;
    }

    sf::Vector2f getPosition1() {
        return position1;
    }

    sf::Vector2f getPosition2() {
        return position2;
    }

    void setPosition1(sf::Vector2f newPosition) {
        position1 = newPosition;
    }

    void setPosition2(sf::Vector2f newPosition) {
        position2 = newPosition;
    }

    sf::RectangleShape getShape1() {
        return section1;
    }

    sf::RectangleShape getShape2() {
        return section2;
    }

    void update() {
        section1.setPosition(position1);
        section2.setPosition(position2); //TODO: dangerous
    }
};

class Engine {
    //sf::Vector2f resolution; be dard nemikhore
    sf::RenderWindow snakeWindow;
    vector<snakeSection> snake;
    vector<snakeSection> snake2;
    int snake1Direction;
    int snake2Direction;
    deque<int> directionQueue1;
    deque<int> directionQueue2;
    sf::Vector2f appleLocation1;
    sf::Vector2f appleLocation2;
    int speed;
    int sectionsToAdd1;
    int sectionsToAdd2;
    Apple apple;
    sf::Time timeSinceLastMove;
public:
    enum direction {
        UP, RIGHT, DOWN, LEFT
    };

    Engine() {
        snake1Direction = direction::RIGHT;
        snake2Direction = direction::LEFT;
        timeSinceLastMove = sf::Time::Zero;
        newSnake();
        moveApple1();
        moveApple2();
        sectionsToAdd1 = 0;
        sectionsToAdd2 = 0;
    }

    void setSpeed(bool hard) {
        if (hard == true) {
            speed = 8;
        } else {
            speed = 2;
        }
    }

    void input() {
        sf::Event event;
        while (snakeWindow.pollEvent(event)) {
            if (event.type == (sf::Event::Closed)) {
                restart();
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

    void update()
    {
        if (timeSinceLastMove.asSeconds() >= sf::seconds(1.f / float(speed)).asSeconds())
        {
            sf::Vector2f thisSectionPosition = snake[0].getPosition1();
            sf::Vector2f thisSectionPosition2 = snake2[0].getPosition2(); //TODO: or getposition1?
            sf::Vector2f lastSectionPosition = thisSectionPosition;
            sf::Vector2f lastSectionPosition2 = thisSectionPosition2;

            if (!directionQueue1.empty())
            {
                switch (snake1Direction)
                {
                    case direction::UP:
                        if (directionQueue1.front() != direction::DOWN)
                        {
                            snake1Direction = directionQueue1.front();
                        }
                        break;
                    case direction::DOWN:
                        if (directionQueue1.front() != direction::UP)
                        {
                            snake1Direction = directionQueue1.front();
                        }
                        break;
                    case direction::LEFT:
                        if (directionQueue1.front() != direction::RIGHT)
                        {
                            snake1Direction = directionQueue1.front();
                        }
                        break;
                    case direction::RIGHT:
                        if (directionQueue1.front() != direction::LEFT)
                        {
                            snake1Direction = directionQueue1.front();
                        }
                        break;
                }
                directionQueue1.pop_front();
            }

            if (!directionQueue2.empty())
            {
                switch (snake2Direction)
                {
                    case direction::UP:
                        if (directionQueue2.front() != direction::DOWN)
                        {
                            snake2Direction = directionQueue2.front();
                        }
                        break;
                    case direction::DOWN:
                        if (directionQueue2.front() != direction::UP)
                        {
                            snake2Direction = directionQueue2.front();
                        }
                        break;
                    case direction::LEFT:
                        if (directionQueue2.front() != direction::RIGHT)
                        {
                            snake2Direction = directionQueue2.front();
                        }
                        break;
                    case direction::RIGHT:
                        if (directionQueue2.front() != direction::LEFT)
                        {
                            snake2Direction = directionQueue2.front();
                        }
                        break;
                }
                directionQueue2.pop_front();
            }

            if (sectionsToAdd1)
            {
                addSnakeSection1();
                sectionsToAdd1--;
            }
            if (sectionsToAdd2)
            {
                addSnakeSection2();
                sectionsToAdd2--;
            }

            //update snakes head position
            switch (snake1Direction)
            {
                case direction::RIGHT:
                    if (thisSectionPosition.x > 800)
                    {
                        thisSectionPosition.x = -20;
                        snake[0].setPosition1(sf::Vector2f(thisSectionPosition.x, thisSectionPosition.y));
                    }
                    snake[0].setPosition1(sf::Vector2f(thisSectionPosition.x + 20, thisSectionPosition.y));
                    break;

                case direction::DOWN:
                    if (thisSectionPosition.y > 600)
                    {
                        thisSectionPosition.y = -20;
                        snake[0].setPosition1(sf::Vector2f(thisSectionPosition.x, thisSectionPosition.y + 20));
                    }
                    snake[0].setPosition1(sf::Vector2f(thisSectionPosition.x, thisSectionPosition.y + 20));
                    break;

                case direction::LEFT:
                    if (thisSectionPosition.x - 20 < 0)
                    {
                        thisSectionPosition.x = 800;
                        snake[0].setPosition1(sf::Vector2f(thisSectionPosition.x - 20, thisSectionPosition.y));
                    }
                    snake[0].setPosition1(sf::Vector2f(thisSectionPosition.x - 20, thisSectionPosition.y));
                    break;

                case direction::UP:
                    if (thisSectionPosition.y - 20 < 0)
                    {
                        thisSectionPosition.y = 600;
                        snake[0].setPosition1(sf::Vector2f(thisSectionPosition.x, thisSectionPosition.y - 20));
                    }
                    snake[0].setPosition1(sf::Vector2f(thisSectionPosition.x, thisSectionPosition.y - 20));
                    break;
            }

            //update snakes head position
            switch (snake2Direction)
            {
                case direction::RIGHT:
                    if (thisSectionPosition2.x > 800)
                    {
                        thisSectionPosition2.x = -20;
                        snake2[0].setPosition2(sf::Vector2f(thisSectionPosition2.x + 20, thisSectionPosition2.y));
                    }
                    snake2[0].setPosition2(sf::Vector2f(thisSectionPosition2.x + 20, thisSectionPosition2.y));
                    break;

                case direction::DOWN:
                    if (thisSectionPosition2.y > 600)
                    {
                        thisSectionPosition2.y = -20;
                        snake2[0].setPosition2(sf::Vector2f(thisSectionPosition2.x, thisSectionPosition2.y + 20));
                    }
                    snake2[0].setPosition2(sf::Vector2f(thisSectionPosition2.x, thisSectionPosition2.y + 20));
                    break;

                case direction::LEFT:
                    if (thisSectionPosition2.x - 20 < 0)
                    {
                        thisSectionPosition2.x = 800;
                        snake2[0].setPosition2(sf::Vector2f(thisSectionPosition2.x - 20, thisSectionPosition2.y));
                    }
                    snake2[0].setPosition2(sf::Vector2f(thisSectionPosition2.x - 20, thisSectionPosition2.y));
                    break;

                case direction::UP:
                    if (thisSectionPosition2.y - 20 < 0)
                    {
                        thisSectionPosition2.y = 600;
                        snake2[0].setPosition2(sf::Vector2f(thisSectionPosition2.x, thisSectionPosition2.y - 20));
                    }
                    snake2[0].setPosition2(sf::Vector2f(thisSectionPosition2.x, thisSectionPosition2.y - 20));
                    break;
            }

            //update snake tail position
            for (int i = 1; i < snake.size(); i++)
            {
                thisSectionPosition = snake[i].getPosition1();
                snake[i].setPosition1(lastSectionPosition);
                lastSectionPosition = thisSectionPosition;
            }


            //update snake tail position
            for (int i = 1; i < snake2.size(); i++)
            {
                thisSectionPosition2 = snake2[i].getPosition2();
                snake2[i].setPosition2(lastSectionPosition2);
                lastSectionPosition2 = thisSectionPosition2;
            }

            for (auto &i: snake)
            {
                i.update();
            }
            for (auto &i: snake2)
            {
                i.update();
            }

            timeSinceLastMove = sf::Time::Zero;

            if (snake[0].getShape1().getGlobalBounds().intersects(apple.getSprite1().getGlobalBounds()))
            {
                sectionsToAdd1 += 2;
                speed += 0.75;
                moveApple1();
            }
            if (snake2[0].getShape2().getGlobalBounds().intersects(apple.getSprite1().getGlobalBounds()))
            {
                sectionsToAdd2 += 2;
                speed += 0.75;
                moveApple1();
            }
            if (snake[0].getShape1().getGlobalBounds().intersects(apple.getSprite2().getGlobalBounds()))
            {
                sectionsToAdd1 += 2;
                speed += 0.75;
                moveApple2();
            }
            if (snake2[0].getShape2().getGlobalBounds().intersects(apple.getSprite2().getGlobalBounds()))
            {
                sectionsToAdd2 += 2;
                speed += 0.75;
                moveApple2();
            }
            for (int i = 1; i < snake.size(); i++)
            {
                if (snake[0].getShape1().getGlobalBounds().intersects(snake[i].getShape1().getGlobalBounds()) ||
                    snake2[0].getShape2().getGlobalBounds().intersects(snake[i].getShape1().getGlobalBounds()) ||
                    snake2[0].getShape2().getGlobalBounds().intersects(snake[0].getShape1().getGlobalBounds()))
                {
                    for (int i = 1; i < snake.size(); i++)
                    {
                        if (snake[0].getShape1().getGlobalBounds().intersects(snake[i].getShape1().getGlobalBounds()) ||
                            snake2[0].getShape2().getGlobalBounds().intersects(
                                    snake[i].getShape1().getGlobalBounds()) ||
                            snake2[0].getShape2().getGlobalBounds().intersects(snake[0].getShape1().getGlobalBounds()))
                        {
                            restart();
                            snakeWindow.close();
                        }
                    }
                    for (int i = 1; i < snake2.size(); i++)
                    {
                        if (snake2[0].getShape2().getGlobalBounds().intersects(
                                snake2[i].getShape2().getGlobalBounds()) ||
                            snake[0].getShape1().getGlobalBounds().intersects(
                                    snake2[i].getShape2().getGlobalBounds()) ||
                            snake[0].getShape1().getGlobalBounds().intersects(snake2[0].getShape2().getGlobalBounds()))
                        {
                            for (int i = 1; i < snake2.size(); i++)
                            {
                                if (snake2[0].getShape2().getGlobalBounds().intersects(
                                        snake2[i].getShape2().getGlobalBounds()) ||
                                    snake[0].getShape1().getGlobalBounds().intersects(
                                            snake2[i].getShape2().getGlobalBounds()) ||
                                    snake[0].getShape1().getGlobalBounds().intersects(
                                            snake2[0].getShape2().getGlobalBounds()))
                                {
                                    restart();
                                    snakeWindow.close();
                                }
                            }
                            timeSinceLastMove = sf::Time::Zero;
                        }
                    }
                }
            }
        }
    }

    void draw() {
        snakeWindow.clear(sf::Color::Black);
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

    }

    void newSnake() {
        snake.clear();
        snake2.clear();
        snake.push_back(sf::Vector2f(100, 100)); //TODO: khodesh az emplace_pack estefade karde.
        snake.push_back(sf::Vector2f(80, 100));
        snake.push_back(sf::Vector2f(60, 100));
        snake2.push_back(sf::Vector2f(700, 100));
        snake2.push_back(sf::Vector2f(720, 100));
        snake2.push_back(sf::Vector2f(740, 100));

    }

    void addSnakeSection1() {
        sf::Vector2f newSectionPosition = snake[snake.size() - 1].getPosition1(); //-1 because index starts with 0
        snake.push_back(newSectionPosition);
    }

    void addSnakeSection2() {
        sf::Vector2f newSectionPosition = snake2[snake2.size() - 1].getPosition2(); //-1 because index starts with 0
        snake2.push_back(newSectionPosition);
    }

    void moveApple1() {
        bool badLocation = false;
        srand(time(0));
        do {
            appleLocation1.x = (rand() % 40) * 20 - 20;
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

    void restart()
    {
        snake1Direction=RIGHT;
        snake2Direction=LEFT;
        timeSinceLastMove= sf::Time::Zero;
        directionQueue1.clear();
        directionQueue2.clear();
        newSnake();
        moveApple1();
        moveApple2();
    }
};