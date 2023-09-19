//
// Created by pewie on 19.09.2023.
//

#ifndef MACTANGLE_MASTER_H
#define MACTANGLE_MASTER_H


#include "InputManager.h"
#include "Renderer.h"
#include "MainResources.h"

class Master {
    InputManager m_inputMgr;
    MainResources m_window;
    Renderer m_renderer;

public:
    Master();
    void start();
};


#endif //MACTANGLE_MASTER_H
