#include "Master.h"

Master::Master() :
        m_mainResources(sf::Vector2f(3840.f, 2160.f)), m_inputMgr(nullptr), m_renderer(), m_map() {}

void Master::start() {
    MainResources::startGame();
    Renderer::registerEntity(dynamic_cast<Entity *>(&m_map), ZIndex::Background);
    while (MainResources::getWindow()->isOpen()) {
        m_inputMgr.checkEvents();
        Renderer::render();
        m_inputMgr.clearKeys();
    }
}
