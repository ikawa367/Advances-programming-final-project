class SnakeSection {
    sf::Vector2f position1;
    sf::Vector2f position2;
    sf::RectangleShape section1;
    sf::RectangleShape section2;
public:
    //constructor
    SnakeSection(sf::Vector2f startPosition1) {
        sf::Vector2f startPosition2;
        startPosition2.x = startPosition1.x;
        startPosition2.y = startPosition1.y;

        //each snake is 20 * 20 at first but their size will change
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
