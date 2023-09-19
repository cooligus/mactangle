#include "Entity.h"
#include "../MainResources.h"

Entity::Entity(sf::String path) {
    m_texture.loadFromFile(path);
    m_texture.setSmooth(true);

    this->setTexture(m_texture);
    this->setTextureRect(sf::IntRect(0, 0, 300, 300));
    this->setOrigin(150, 150);
    this->setPosition(100, 100);
    this->setScale(1, 1);
}

void Entity::display() {
    MainResources::getWindow()->draw(*this);
}
