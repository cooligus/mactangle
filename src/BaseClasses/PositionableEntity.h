//
// Created by pewie on 19.09.2023.
//

#ifndef MACTANGLE_POSITIONABLEENTITY_H
#define MACTANGLE_POSITIONABLEENTITY_H


#include <SFML/Graphics/Sprite.hpp>
#include "../PPSaB.h"
#include "../mainclasses.h"
#include "../map.h"

class PositionableEntity : public sf::Sprite, Button {
    bool m_isSet{false};
    bool m_holding{true};
    sf::RenderWindow *m_window{};

public:
    PositionableEntity(sf::RenderWindow *window);

    void registerWindow(sf::RenderWindow *window);

    void pick();

    void set();

    virtual bool canBePlaced();

    virtual void work();

    virtual void display();

    void setMousePos();
};


#endif //MACTANGLE_POSITIONABLEENTITY_H
