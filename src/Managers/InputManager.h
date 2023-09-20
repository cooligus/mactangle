//
// Created by pewie on 16.09.2023.
//

#ifndef MACTANGLE_INPUTMANAGER_H
#define MACTANGLE_INPUTMANAGER_H


#include <SFML/Window/Event.hpp>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

class InputManager {
    static std::vector<sf::Keyboard::Key> m_keys;
    static sf::RenderWindow *m_window;
    static sf::Event m_event;
public:
    void checkEvents();

    void clearKeys();

    static std::vector<sf::Keyboard::Key> getKeys();

    explicit InputManager(sf::RenderWindow *window);
};


#endif //MACTANGLE_INPUTMANAGER_H
