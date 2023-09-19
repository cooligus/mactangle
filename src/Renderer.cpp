#include "Renderer.h"
#include "MainResources.h"
#include <iostream>

std::vector<std::vector<std::shared_ptr<Entity>>> Renderer::m_entities = std::vector<std::vector<std::shared_ptr<Entity>>>();

void Renderer::addEntityToQueue(Entity &toDraw, ZIndex height) {
    std::shared_ptr<Entity> toPush= std::make_shared<Entity>(toDraw);
    switch (height) {
        case Background:
            m_entities[Background].push_back(toPush);
            break;
        case Entities:
            m_entities[Entities].push_back(toPush);
            break;
        case Particle:
            m_entities[Particle].push_back(toPush);
            break;
        case FloatingEntities:
            m_entities[FloatingEntities].push_back(toPush);
            break;
        case Layout:
            m_entities[Layout].push_back(toPush);
            break;
    }
}


Renderer::Renderer() {
    for(int i = 0; i < ZIndexSize; i++) {
        m_entities.emplace_back();
    }
}

void Renderer::render() {
    MainResources::getWindow()->clear();
    for(const auto& entireScope: m_entities) {
        for(const auto& entity: entireScope) {
            entity->display();
        }
    }
    MainResources::getWindow()->display();
}
