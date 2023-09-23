//
// Created by pewie on 19.09.2023.
//

#ifndef MACTANGLE_POSITIONABLEENTITY_H
#define MACTANGLE_POSITIONABLEENTITY_H


#include <SFML/Graphics/Sprite.hpp>
#include "Entity.h"

class PositionableEntity : public virtual Entity {
public:
    virtual bool canBePlaced();

    virtual void makeReadyToGo();
};


#endif //MACTANGLE_POSITIONABLEENTITY_H
