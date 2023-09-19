//
// Created by pewie on 19.09.2023.
//

#ifndef MACTANGLE_RENDERER_H
#define MACTANGLE_RENDERER_H


#include <SFML/Graphics/Drawable.hpp>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "BaseClasses/Entity.h"

constexpr int ZIndexSize = 5;

enum ZIndex {
    Background = 0,
    Entities = 1,
    Particle = 2, // for posterity
    FloatingEntities = 3,
    Layout = 4,
};

class Renderer {
    static std::vector<std::vector<std::shared_ptr<Entity>>> m_entities;
    static std::shared_ptr<sf::RenderWindow> m_window;
public:
    Renderer();

    static void addEntityToQueue(Entity &toDraw, ZIndex height);

    void render();
};


#endif //MACTANGLE_RENDERER_H
