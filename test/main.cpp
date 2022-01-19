#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include"MainMenu.h"
#include "SnakeFunc.h"

using namespace std;

bool musicFlag = 1;

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(700, 800), "My window", sf::Style::Default, settings);
    sf::Music music;
    music.openFromFile("mymusic.wav");

    music.setVolume(50);
    music.play();

    //we make it more dynamic in here instead of giving it the amount of 800 and 600 our selves
    MainMenu menuDisplay(window.getSize().x, window.getSize().y);

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::KeyReleased:
                    switch (event.key.code) {
                        case sf::Keyboard::Up:
                            menuDisplay.moveUp();
                            break;

                        case sf::Keyboard::Down:
                            menuDisplay.moveDown();
                            break;

                        case sf::Keyboard::Return:
                            switch (menuDisplay.getPressedItem()) {
                                case 0:
                                    snake();
                                    break;

                                case 1:
                                    if (musicFlag) {
                                        music.stop();
                                        musicFlag = 0;
                                    } else {
                                        music.play();
                                        musicFlag = 1;
                                    }
                                    break;

                                case 2:
                                    //difficality easy
                                    break;

                                case 3:
                                    //difficality hard
                                    break;

                                case 4:
                                    window.close();
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