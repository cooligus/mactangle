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
#include "../BaseClasses/Entity.h"

constexpr int ZIndexSize = 6;

enum ZIndex {
    Background = 0,
    UnderParticles = 1, // for posterity
    Entities = 2,
    Particles = 3, // for posterity
    FloatingEntities = 4,
    Layout = 5,
};

class Renderer {
    static std::vector<std::vector<Entity *>> m_entities;
    static std::shared_ptr<sf::RenderWindow> m_window;
public:
    Renderer();

    static void registerEntity(Entity *toDraw, ZIndex height);

    static void render();
};


#endif //MACTANGLE_RENDERER_H
