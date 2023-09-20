#include <memory>
#include "InputManager.h"
#include "MainResources.h"

std::vector<sf::Keyboard::Key> InputManager::m_keys = std::vector<sf::Keyboard::Key>();
sf::RenderWindow *InputManager::m_window = new sf::RenderWindow();
sf::Event InputManager::m_event = sf::Event();

void InputManager::checkEvents() {
    while (MainResources::getWindow()->pollEvent(m_event)) {
        if (m_event.type == sf::Event::Closed ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && sf::Keyboard::isKeyPressed(sf::Keyboard::F4)) {
            MainResources::getWindow()->close();
        }
        if (m_event.type == sf::Event::KeyReleased) {
            m_keys.push_back(m_event.key.code);
        }
    }
}

InputManager::InputManager(sf::RenderWindow *window) {
    //m_mainResources = window;
}

void InputManager::clearKeys() {
    m_keys.clear();
}

std::vector<sf::Keyboard::Key> InputManager::getKeys() {
    return m_keys;
}
