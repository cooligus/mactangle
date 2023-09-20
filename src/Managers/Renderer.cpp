#include "Renderer.h"
#include "MainResources.h"
#include <iostream>

std::vector<std::vector<Entity *>> Renderer::m_entities = std::vector<std::vector<Entity *>>();

void Renderer::registerEntity(Entity *toDraw, ZIndex height) {
    switch (height) {
        case Background:
            m_entities[Background].push_back(toDraw);
            break;
        case UnderParticles:
            m_entities[UnderParticles].push_back(toDraw);
            break;
        case Entities:
            m_entities[Entities].push_back(toDraw);
            break;
        case Particles:
            m_entities[Particles].push_back(toDraw);
            break;
        case FloatingEntities:
            m_entities[FloatingEntities].push_back(toDraw);
            break;
        case Layout:
            m_entities[Layout].push_back(toDraw);
            break;
    }
}


Renderer::Renderer() {
    for (int i = 0; i < ZIndexSize; i++) {
        m_entities.emplace_back();
    }
}

void Renderer::render() {
    MainResources::getWindow()->clear();
    for (const auto &entireScope: m_entities) {
        for (const auto &entity: entireScope) {
            entity->display();
        }
    }
    MainResources::getWindow()->display();
}
