#include <SFML/Window/Mouse.hpp>
#include "HoldingManager.h"
#include "MainResources.h"
#include "InputManager.h"

bool HoldingManager::addToQueue(PositionableEntity *entity, bool addIfBusy) {
    if (!addIfBusy && !m_isBusy) {
        m_toPut.push_back(entity);
        m_isBusy = true;
        return true;
    } else if (addIfBusy) {
        m_toPut.push_back(entity);
        return true;
    }

    return false;
}

bool HoldingManager::getIsBusy() {
    return m_isBusy;
}

void HoldingManager::manageCurrentEntity() {
    if (m_isBusy) {
        m_toPut[0]->setPosition(MainResources::getMouseRelPosition());
        if (m_toPut[0]->canBePlaced() && InputManager::wasMouseClicked()) {
            place();
        }
    }
}

bool HoldingManager::place() {
    if (m_toPut[0]->canBePlaced()) {
        m_toPut.erase(m_toPut.begin());
        if (m_toPut.empty()) {
            m_isBusy = false;
        }
    }
    return false;
}
