class Wall {
    sf::RectangleShape wall1;
    sf::RectangleShape wall2;
public:
    //constructor
    Wall() {
        //one of them is 20 * 60 and other is 60 * 20
        wall1.setSize(sf::Vector2f(20, 60));
        wall1.setFillColor(sf::Color::Magenta);
        wall2.setFillColor(sf::Color::Cyan);
        wall2.setSize(sf::Vector2f(60, 20));
    }

    //referes to move of walls in engine
    void setWallPosition(sf::Vector2f newPosition, bool firstOrSecond) {
        if (firstOrSecond == 0) {
            wall1.setPosition(newPosition);
        } else if (firstOrSecond == 1) {
            wall2.setPosition(newPosition);
        }
    }

    sf::RectangleShape getWall(bool firstOrSecond) {
        if (firstOrSecond == 0) {
            return wall1;
        } else {
            return wall2;
        }
    }

};
