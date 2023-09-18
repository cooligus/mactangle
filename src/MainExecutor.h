//
// Created by pewie on 16.09.2023.
//

#ifndef MACTANGLE_MAINEXECUTOR_H
#define MACTANGLE_MAINEXECUTOR_H


#include "offert.h"
#include "additionals.h"
#include "InputManager.h"

class MainExecutor {
    MainClass object_main;
    sf::Event event;
    Map the_map;
    Addidtionals addition;
    Mactangle mactangle;
    Dacler dacler;
    Bedler bedler;
    Shop shop;
    Offert dacler_offert;
    Offert bedler_offert;
    InputManager inputs;
public:
    MainExecutor();

    void start();
};


#endif //MACTANGLE_MAINEXECUTOR_H
