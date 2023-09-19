#include <SFML/System/String.hpp>
#include "StringKey.h"

sf::String getCharFromNumber(sf::Keyboard::Key key) {
    sf::String charKey = "";
    switch (key) {
        case sf::Keyboard::Key::Num0:
            charKey = "0";
            break;
        case sf::Keyboard::Key::Numpad0:
            charKey = "0";
            break;
        case sf::Keyboard::Key::Num1:
            charKey = "1";
            break;
        case sf::Keyboard::Key::Numpad1:
            charKey = "1";
            break;
        case sf::Keyboard::Key::Num2:
            charKey = "2";
            break;
        case sf::Keyboard::Key::Numpad2:
            charKey = "2";
            break;
        case sf::Keyboard::Key::Num3:
            charKey = "3";
            break;
        case sf::Keyboard::Key::Numpad3:
            charKey = "3";
            break;
        case sf::Keyboard::Key::Num4:
            charKey = "4";
            break;
        case sf::Keyboard::Key::Numpad4:
            charKey = "4";
            break;
        case sf::Keyboard::Key::Num5:
            charKey = "5";
            break;
        case sf::Keyboard::Key::Numpad5:
            charKey = "5";
            break;
        case sf::Keyboard::Key::Num6:
            charKey = "6";
            break;
        case sf::Keyboard::Key::Numpad6:
            charKey = "6";
            break;
        case sf::Keyboard::Key::Num7:
            charKey = "7";
            break;
        case sf::Keyboard::Key::Numpad7:
            charKey = "7";
            break;
        case sf::Keyboard::Key::Num8:
            charKey = "8";
            break;
        case sf::Keyboard::Key::Numpad8:
            charKey = "8";
            break;
        case sf::Keyboard::Key::Num9:
            charKey = "9";
            break;
        case sf::Keyboard::Key::Numpad9:
            charKey = "0";
            break;
        case sf::Keyboard::Key::Dash:
            charKey = "-";
            break;
        case sf::Keyboard::Key::BackSpace:
            charKey = "\b";
            break;
        case sf::Keyboard::Key::Enter:
            charKey = "\n";
            break;
        default:
            charKey = "";
    }
    return charKey;
}
