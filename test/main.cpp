#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include"MainMenu.h"

using namespace std;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(600, 600), "My window", sf::Style::Default, settings);

    //we make it more dynamic in here instead of giving it the amount of 800 and 600 our selves
    MainMenu menuDisplay(window.getSize().x, window.getSize().y);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::KeyReleased:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Up:
                            menuDisplay.moveUp();
                            break;

                        case sf::Keyboard::Down:
                            menuDisplay.moveDown();
                            break;

                        case sf::Keyboard::Return:
                            switch (menuDisplay.getPressedItem())
                            {
                                case 0:
                                    cout << "PLAY is pressed" << endl;
                                    break;

                                case 1:
                                    cout << "Game setting is pressed" << endl;
                                    break;

                                case 2:
                                    cout << "exit  is pressed" << endl;
                                    break;
                            }
                    }
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        window.clear(sf::Color::Black);
        menuDisplay.draw(window);
        window.display();
    }

    return 0;
}