#ifndef MACTANGLE_ENTITY_H
#define MACTANGLE_ENTITY_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>

class Entity : public sf::Sprite {
    sf::Texture m_texture;
public:
    explicit Entity(const sf::String &path);

    Entity();

    virtual void display();
};


#endif //MACTANGLE_ENTITY_H
