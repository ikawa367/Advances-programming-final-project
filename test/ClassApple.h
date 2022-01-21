//class Apple {
//    sf::RectangleShape sprite;
//    sf::RectangleShape sprite2;
//public:
//    Apple() {
//        sf::Vector2f startPosition1(400, 400);
//        sf::Vector2f startPosition2(300, 500);
//        sprite.setSize(sf::Vector2f(20, 20));
//        sprite2.setSize(sf::Vector2f(20, 20));
//        sprite.setFillColor(sf::Color::Red);
//        sprite2.setFillColor(sf::Color::Blue);
//        sprite.setPosition(startPosition1);
//        sprite2.setPosition(startPosition2);
//    }
//
//    void setPosition(sf::Vector2f newPosition, bool firstOrsecond) {
//        if (firstOrsecond == 0) {
//            sprite.setPosition(newPosition);
//        } else {
//            sprite2.setPosition(newPosition);
//        }
//    }
//
//    //draw function needs getSprite.
//    sf::RectangleShape getSprite1() {
//        return sprite;
//    }
//
//    sf::RectangleShape getSprite2() {
//        return sprite2;
//    }
//};