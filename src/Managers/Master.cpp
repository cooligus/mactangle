#include "Master.h"
#include "../BaseClasses/PositionableEntity.h"
#include "../Protagonists/RemoteDecrypter.h"

Master::Master() :
        m_mainResources(sf::Vector2f(3840.f, 2160.f)), m_inputMgr(), m_renderer(), m_map() {}

void Master::start() {
    MainResources::startGame();


    RemoteDecrypter remoteDecrypter;

    Renderer::registerEntity(dynamic_cast<Entity *>(&m_map), ZIndex::Background);
    Renderer::registerEntity(dynamic_cast<Entity *>(&remoteDecrypter), ZIndex::Background);

    m_holding.addToQueue(dynamic_cast<PositionableEntity *>(&remoteDecrypter));

    while (MainResources::getWindow()->isOpen()) {
        // required inputs
        InputManager::checkEvents();

        m_holding.manageCurrentEntity();

        // final steps
        Renderer::render();
        InputManager::clearKeys();
    }
}
