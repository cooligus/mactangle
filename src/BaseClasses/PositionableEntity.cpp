//
// Created by pewie on 19.09.2023.
//

#include "PositionableEntity.h"

PositionableEntity::PositionableEntity(sf::RenderWindow *window) {
    registerWindow(window);
}

void PositionableEntity::registerWindow(sf::RenderWindow *main) {
    m_window = main;
}


void PositionableEntity::pick() {
    m_holding = true;
}


void PositionableEntity::display() {
    m_window->draw(*this);
}

void PositionableEntity::work() {
    if(m_holding && !m_isSet) {
        setMousePos();
    }
}

void PositionableEntity::set() {
    m_isSet = true;
    m_holding = false;
}

void PositionableEntity::setMousePos() {
    this->setPosition(Vector2<float>(Mouse::getPosition()));
}

bool PositionableEntity::canBePlaced() {
    return true;
}
