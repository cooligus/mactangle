//
// Created by pewie on 19.09.2023.
//

#ifndef MACTANGLE_MASTER_H
#define MACTANGLE_MASTER_H


#include "InputManager.h"
#include "Renderer.h"
#include "MainResources.h"
#include "../Layout/Map.h"

class Master {
    InputManager m_inputMgr;
    MainResources m_mainResources;
    Renderer m_renderer;
    Map m_map;

public:
    Master();
    void start();
};


#endif //MACTANGLE_MASTER_H
