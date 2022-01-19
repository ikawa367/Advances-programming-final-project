#include"MainMenu.hpp"

MainMenu::MainMenu(float width, float height)
{
	if (!fontOfObtions.loadFromFile("arial.ttf"))
	{
		//exit(0);
	}

	//if you want to center each item in the middle of the pannel you'll use the formula below:
	// 4 is our Max_NUMBER_OF_ITEMS + 1
	menuText[0].setFont(fontOfObtions);
	menuText[0].setFillColor(sf::Color::Green);
	menuText[0].setString("START");
	// multiply by 1 means the position is in the top
	menuText[0].setPosition(sf::Vector2f(width / 2, height / 4 * 1));

	menuText[1].setFont(fontOfObtions);
	menuText[1].setFillColor(sf::Color::Green);
	menuText[1].setString("Game Settings");
	// multiply by 2 means the position is in the middle
	menuText[1].setPosition(sf::Vector2f(width / 2, height / 4 * 2));

	menuText[2].setFont(fontOfObtions);
	menuText[2].setFillColor(sf::Color::Green);
	menuText[2].setString("Exit Game");
	// multiply by 3 means the position is in the bottom
	menuText[2].setPosition(sf::Vector2f(width / 2, height / 4 * 3));
}

void MainMenu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < Max_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menuText[i]);
	}
}

void MainMenu::moveUp()
{
	if (selectedItemIndex - 1 >= 0) {
		menuText[selectedItemIndex].setFillColor(sf::Color::Green);
		selectedItemIndex--;
		menuText[selectedItemIndex].setFillColor(sf::Color::Blue);
	}
}

void MainMenu::moveDown()
{
	if (selectedItemIndex + 1 < 3) {
		menuText[selectedItemIndex].setFillColor(sf::Color::Green);
		selectedItemIndex++;
		menuText[selectedItemIndex].setFillColor(sf::Color::Blue);
	}
}
