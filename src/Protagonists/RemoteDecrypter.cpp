#include "RemoteDecrypter.h"
#include <iostream>

RemoteDecrypter::RemoteDecrypter() : Entity(BEDLER_PNG, sf::IntRect(0, 0, 300, 300)) {
    std::cout << this->getTexture()->getSize().y;
}

void RemoteDecrypter::makeReadyToGo() {
    PositionableEntity::makeReadyToGo();
}
