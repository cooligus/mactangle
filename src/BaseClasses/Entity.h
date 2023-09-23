#ifndef MACTANGLE_ENTITY_H
#define MACTANGLE_ENTITY_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>

class Entity : public sf::Sprite {
    sf::Texture m_defaultTexture;
public:
    explicit Entity(const sf::String &path, sf::IntRect textureSizeAndOffset = sf::IntRect(0, 0, 300, 300),
                    sf::Vector2f origin = sf::Vector2f(150, 150));

    Entity();

    virtual void display();

    virtual void work();
};


#endif //MACTANGLE_ENTITY_H
