#pragma once

#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;

//array of text items included in the main menu
#define Max_NUMBER_OF_ITEMS 5

class MainMenu {
private:
    //item that u select in main menu
    int selectedItemIndex = 0;
    sf::Font fontOfOptions;

    //array of text items included in the main menu refer to the define
    sf::Text menuText[Max_NUMBER_OF_ITEMS];

public:
    MainMenu(float width, float height);

    void draw(sf::RenderWindow &window);

    //you move the options Up and Down with keyboard keys so we make functions to controll them
    void moveUp();

    void moveDown();

    int getPressedItem() { return selectedItemIndex; }
};

