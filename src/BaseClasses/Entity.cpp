#include "Entity.h"
#include "../Managers/MainResources.h"

Entity::Entity() = default;

Entity::Entity(const sf::String &path, sf::IntRect textureSizeAndOffset, sf::Vector2f origin) {
    m_defaultTexture.loadFromFile(path);
    m_defaultTexture.setSmooth(true);

    this->setTexture(m_defaultTexture);
    this->setTextureRect(textureSizeAndOffset);
    this->setOrigin(origin);
    this->setPosition(0, 0);
    this->setScale(1, 1);
}

void Entity::display() {
    MainResources::getWindow()->draw(*this);
}

void Entity::work() {

}
