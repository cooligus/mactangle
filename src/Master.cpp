#include "Master.h"

Master::Master() :
        m_window(), m_inputMgr(nullptr), m_renderer() {}

void Master::start() {
    Entity entity(BACKGROUND_PNG);
    m_renderer.addEntityToQueue(entity, ZIndex::Entities);
    while (MainResources::getWindow()->isOpen()) {
        m_inputMgr.checkEvents();
        m_renderer.render();
        m_inputMgr.clearKeys();
    }
}
