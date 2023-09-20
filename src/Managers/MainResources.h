//
// Created by pewie on 19.09.2023.
//

#ifndef MACTANGLE_MAINRESOURCES_H
#define MACTANGLE_MAINRESOURCES_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <memory>

class MainResources {
    static std::shared_ptr<sf::RenderWindow> m_window;
    static std::shared_ptr<sf::View> m_camera;
    static sf::Font m_font;
    static bool m_gameRunning;

public:
    MainResources(sf::Vector2f cameraSize);
    static void startGame();
    static void stopGame();
    static std::shared_ptr<sf::RenderWindow> getWindow();
    static bool isGameRunning();
};


#endif //MACTANGLE_MAINRESOURCES_H
