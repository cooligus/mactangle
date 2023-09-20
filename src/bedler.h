#pragma once

#include "mainclasses.h"
#include "map.h"
#include "mactangle.h"

using namespace sf;
using namespace std;

class Bedler : public Sprite {
    //-----VARIABLES-----//

    Texture bedler_texture;
    Sprite sight;
    Texture sight_texture;
    Button button;
    Button sight_button;

    Text result;
    Event eventus = eventus;
    sf::String result_text;

    bool seted = false;
    bool holding = false;
    bool can_do_animation = false;
    bool pressed = false;
    bool sight_holding = false;
    bool add_money = false;
    int touch_counter = 0;

    //-----FUNCTIONS-----//
    void testForClick(Bedler object);

    bool testMactangles(vector<Mactangle> &mactangles);

public:
    Bedler(MainClass &main);

    void nowCanBeSetted();

    void setSomething(MainClass &object);

    void set(OldMap &map, MainClass &object);

    void writeResult(MainClass &main, vector<Mactangle> &mactangles);

    void textureReset();

    void setSetted();

    bool addMoney();

    Texture getHimTexture();

    bool getMainBool();

    void work(Bedler object, OldMap &map, MainClass &main, vector<Mactangle> &mactangles);

    void display(MainClass &main);
};
