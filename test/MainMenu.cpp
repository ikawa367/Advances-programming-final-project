#include "MainMenu.h"
#include <SFML/Audio.hpp>

MainMenu::MainMenu(float width, float height) {
    if (!fontOfOptions.loadFromFile("Amatic-Bold.ttf")) {
        //you can handle bug but no need in here
    }

    //if you want to center each item in the middle of the pannel you'll use the formula below:
    // 4 is our Max_NUMBER_OF_ITEMS + 1
    menuText[0].setFont(fontOfOptions);
    menuText[0].setFillColor(sf::Color::Green);
    menuText[0].setString("START");
    // multiply by 0.5 means the position is in the top
    menuText[0].setPosition(sf::Vector2f(width / 2.5, height / 4 * 0.5));

    menuText[1].setFont(fontOfOptions);
    menuText[1].setFillColor(sf::Color::Green);
    menuText[1].setString("Game Music(ON/OFF)");
    // multiply by 1.5 means the position is in the middle
    menuText[1].setPosition(sf::Vector2f(width / 2.5, height / 4 * 1.5));

    menuText[2].setFont(fontOfOptions);
    menuText[2].setFillColor(sf::Color::Green);
    menuText[2].setString("Difficality : Easy");
    // multiply by 2.5 means the position is in the bottom
    menuText[2].setPosition(sf::Vector2f(width / 2.5, height / 4 * 2));

    menuText[3].setFont(fontOfOptions);
    menuText[3].setFillColor(sf::Color::Green);
    menuText[3].setString("Difficality : Hard");
    // multiply by 3.5 means the position is in the bottom
    menuText[3].setPosition(sf::Vector2f(width / 2.5, height / 4 * 2.5));

    menuText[4].setFont(fontOfOptions);
    menuText[4].setFillColor(sf::Color::Green);
    menuText[4].setString("Exit Game");
    // multiply by 4.5 means the position is in the bottom
    menuText[4].setPosition(sf::Vector2f(width / 2.5, height / 4 * 3));
}

void MainMenu::draw(sf::RenderWindow &window) {
    for (int i = 0; i < Max_NUMBER_OF_ITEMS; i++) {
        window.draw(menuText[i]);
    }
}

//updates colors when you move up and down between options
void MainMenu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menuText[selectedItemIndex].setFillColor(sf::Color::Green);
        selectedItemIndex--;
        menuText[selectedItemIndex].setFillColor(sf::Color::Cyan);
    }
}

void MainMenu::moveDown() {
    if (selectedItemIndex + 1 < 5) {
        menuText[selectedItemIndex].setFillColor(sf::Color::Green);
        selectedItemIndex++;
        menuText[selectedItemIndex].setFillColor(sf::Color::Cyan);
    }
}
