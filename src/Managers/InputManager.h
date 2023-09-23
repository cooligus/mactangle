//
// Created by pewie on 16.09.2023.
//

#ifndef MACTANGLE_INPUTMANAGER_H
#define MACTANGLE_INPUTMANAGER_H


#include <SFML/Window/Event.hpp>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <optional>

class InputManager {
    static std::vector<sf::Keyboard::Key> m_keys;
    static std::vector<sf::Event::MouseButtonEvent> m_buttonMouseEvents;
    static sf::RenderWindow *m_window;
    static sf::Event m_event;
public:
    static void checkEvents();

    static void clearKeys();

    static bool wasMouseClicked();

    static std::vector<sf::Keyboard::Key> getKeys();
};


#endif //MACTANGLE_INPUTMANAGER_H
