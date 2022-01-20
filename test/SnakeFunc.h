#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<vector>

class snakeSection{
    sf::Vector2f position1;
    sf::Vector2f position2;
    sf::RectangleShape section1;
    sf::RectangleShape section2;
public:
    snakeSection(sf::Vector2f startPosition1)
    {
        section1.setSize(sf::Vector2f(20,20));
        section2.setSize(sf::Vector2f(20,20));
        section1.setFillColor(sf::Color::Green);
        section2.setFillColor(sf::Color::Yellow);
        section1.setPosition(startPosition1);
        section2.setPosition(startPosition1.x+50,startPosition1.y+50);
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
    void upgrate()
    {
        section1.setPosition(position1);
        //section2.setPosition(position2);
    }
};

class Engine
{
    //sf::Vector2f resolution; be dard nemikhore
    sf::RenderWindow snakeWindow;
    vector<snakeSection>snake;
    vector<snakeSection>snake2;
public:
    Engine()
    {
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
        snakeWindow.create(sf::VideoMode(800,600),"main game");
        snakeWindow.setFramerateLimit(60);
        //Game loop. Runs and gets inputs until the window is closed.
        while (snakeWindow.isOpen())
        {
            input();
            draw();
        }
    }
    void newSnake(/*sf:: Vector2f start*/)
    {
        snake.clear();
        snake2.clear();
        //snake.push_back(sf::Vector2f(start.x,start.y)); //TODO: khodesh az emplace_pack estefade karde.
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



