#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<vector>
#include <deque>

class snakeSection{
    sf::Vector2f position1;
    sf::Vector2f position2;
    sf::RectangleShape section1;
    sf::RectangleShape section2;
public:
    snakeSection(sf::Vector2f startPosition1)
    {
        sf::Vector2f startPosition2;
        startPosition2.x=startPosition1.x;
        startPosition2.y=startPosition1.y;
        section1.setSize(sf::Vector2f(20,20));
        section2.setSize(sf::Vector2f(20,20));
        section1.setFillColor(sf::Color::Green);
        section2.setFillColor(sf::Color::Yellow);
        section1.setPosition(startPosition1);
        section2.setPosition(startPosition1.x+50,startPosition1.y+50);
        position1=startPosition1;
        position2=startPosition2;
    }

    sf::Vector2f getPosition1()
    {
        return position1;
    }
    sf::Vector2f getPosition2()
    {
        return position2;
    }
    void setPosition1(sf::Vector2f newPosition)
    {
        position1=newPosition;
    }
    void setPosition2(sf::Vector2f newPosition)
    {
        position2=newPosition;
    }
    sf::RectangleShape getShape1()
    {
        return section1;
    }
    sf::RectangleShape getShape2()
    {
        return section2;
    }
    void update()
    {
        section1.setPosition(position1);
        section2.setPosition(position2); //TODO: dangerous
    }
};

class Engine
{
    //sf::Vector2f resolution; be dard nemikhore
    sf::RenderWindow snakeWindow;
    vector<snakeSection>snake;
    vector<snakeSection>snake2;
    int snake1Direction;
    int snake2Direction;
    deque<int> directionQueue1;
    deque<int> directionQueue2;
    int speed;
    sf::Time timeSinceLastMove;
public:
    enum direction{UP,RIGHT,DOWN,LEFT};
    Engine()
    {
        speed=2;
        snake1Direction=direction::RIGHT;
        snake2Direction=direction::RIGHT;
        timeSinceLastMove=sf::Time::Zero;
        newSnake();
    }
    void input(){
        sf::Event event;
        while (snakeWindow.pollEvent(event))
        {
            if(event.type==(sf::Event::Closed))
            {
                snakeWindow.close();
            }
            if(event.type==sf::Event::KeyPressed)
            {
                if(event.key.code ==sf::Keyboard::Up)
                {
                    addDirection1(direction::UP);
                }
                else if(event.key.code ==sf::Keyboard::Down)
                {
                    addDirection1(direction::DOWN);
                }
                else if(event.key.code ==sf::Keyboard::Right)
                {
                    addDirection1(direction::RIGHT);
                }
                else if(event.key.code ==sf::Keyboard::Left)
                {
                    addDirection1(direction::LEFT);
                }
                else if(event.key.code == sf:: Keyboard::W)
                {
                    addDirection2(direction::UP);
                }
                else if(event.key.code == sf:: Keyboard::S)
                {
                    addDirection2(direction::DOWN);
                }
                else if(event.key.code == sf:: Keyboard::D)
                {
                    addDirection2(direction::RIGHT);
                }
                else if(event.key.code == sf:: Keyboard::A)
                {
                    addDirection2(direction::LEFT);
                }
            }
        }
    }
    void addDirection1(int newDirection)
    {
        if(directionQueue1.empty())
        {
            directionQueue1.push_back(newDirection);
        }
        else if(!directionQueue1.empty())
        {
            if(directionQueue1.back() != newDirection)
            {
                directionQueue1.push_back(newDirection);
            }
        }
    }
    void addDirection2(int newDirection)
    {
        if(directionQueue2.empty())
        {
            directionQueue2.push_back(newDirection);
        }
        else if(!directionQueue2.empty())
        {
            if(directionQueue2.back() != newDirection)
            {
                directionQueue2.push_back(newDirection);
            }
        }
    }
    void update()
    {
        if(timeSinceLastMove.asSeconds() >= sf::seconds(1.f/float (speed)).asSeconds())
        {
            sf::Vector2f thisSectionPosition = snake[0].getPosition1();
            sf::Vector2f thisSectionPosition2 = snake2[0].getPosition2(); //TODO: or getposition1?
            sf::Vector2f lastSectionPosition = thisSectionPosition;
            sf::Vector2f lastSectionPosition2 = thisSectionPosition2;

            if(!directionQueue1.empty())
            {
                switch (snake1Direction)
                {
                    case direction::UP:
                        if(directionQueue1.front() != direction::DOWN)
                        {
                            snake1Direction = directionQueue1.front();
                        }
                        break;
                    case direction::DOWN:
                        if(directionQueue1.front() != direction::UP)
                        {
                            snake1Direction = directionQueue1.front();
                        }
                        break;
                    case direction::LEFT:
                        if(directionQueue1.front() != direction::RIGHT)
                        {
                            snake1Direction = directionQueue1.front();
                        }
                        break;
                    case direction::RIGHT:
                        if(directionQueue1.front() != direction::LEFT)
                        {
                            snake1Direction = directionQueue1.front();
                        }
                        break;
                }
                directionQueue1.pop_front();
            }
            //update snakes head position
            switch (snake1Direction)
            {
                case direction::RIGHT:
                    snake[0].setPosition1(sf::Vector2f(thisSectionPosition.x + 20, thisSectionPosition.y));
                    break;
                case direction::DOWN:
                    snake[0].setPosition1(sf::Vector2f(thisSectionPosition.x, thisSectionPosition.y+20));
                    break;
                case direction::LEFT:
                    snake[0].setPosition1(sf::Vector2f(thisSectionPosition.x -20, thisSectionPosition.y));
                    break;
                case direction::UP:
                    snake[0].setPosition1(sf::Vector2f(thisSectionPosition.x , thisSectionPosition.y-20));
                    break;
            }
            //update snake tail position
            for(int i=1;i<snake.size();i++)
            {
                thisSectionPosition = snake[i].getPosition1();
                snake[i].setPosition1(lastSectionPosition);
                lastSectionPosition = thisSectionPosition;
            }

            for(auto &i : snake)
            {
                i.update();
            }
            timeSinceLastMove = sf::Time::Zero;
        }
    }
    void draw()
    {
        snakeWindow.clear(sf::Color::Black);
        for(auto & s: snake)
        {
            snakeWindow.draw(s.getShape1());
            //snakeWindow.draw(s.getShape2()); is true or not???
        }
        for(auto & s: snake2)
        {
            snakeWindow.draw(s.getShape2());
        }
        snakeWindow.display();
    }
    void run()
    {
        sf::Clock clock;
        snakeWindow.create(sf::VideoMode(800,600),"main game");
        snakeWindow.setFramerateLimit(60);
        //Game loop. Runs and gets inputs until the window is closed.
        while (snakeWindow.isOpen())
        {
            sf::Time dt = clock.restart();
            timeSinceLastMove += dt;
            input();
            update();
            draw();
        }
    }
    void newSnake(/*sf:: Vector2f start*/)
    {
        snake.clear();
        snake2.clear();
        //snake.push_back(sf::Vector2f(start.x,start.y));
        snake.push_back(sf::Vector2f(100,100)); //TODO: khodesh az emplace_pack estefade karde.
        snake.push_back(sf::Vector2f(80,100));
        snake.push_back(sf::Vector2f(60,100));
        snake2.push_back(sf::Vector2f(160,100));
        snake2.push_back(sf::Vector2f(140,100));
        snake2.push_back(sf::Vector2f(120,100));
        //....

    }
    void addSnakeSection()
    {
        sf::Vector2f newSectionPosition = snake[snake.size() -1].getPosition1(); //-1 because index starts with 0
        snake.push_back(newSectionPosition);
    }
};



