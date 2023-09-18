#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include "PPSaB.h"
#include "bedler.h"
#include "shop.h"
#include "map.h"
#include "mactangle.h"
#include "mainclasses.h"

using namespace sf;
using namespace std;

#include "InputManager.h"
#include "helpers/StringKey.h"

Bedler::Bedler(MainClass &main)
        : result_text(" ") {
    bedler_texture.loadFromFile(BEDLER_PNG);
    bedler_texture.setSmooth(true);

    this->setTexture(bedler_texture);
    this->setTextureRect(IntRect(0, 0, 300, 300));
    this->setOrigin(150, 150);
    this->setPosition(0, 0);
    this->setScale(0, 0);

    result.setFont(main.m_font);
    result.setCharacterSize(100);
    result.setFillColor(Color(255, 255, 255));
    result.setOrigin(100, 30);
    result.setScale(1.2, 1.2);
    result.setPosition(getPosition());;
    result.setString(" ");
}

void Bedler::nowCanBeSetted() {
    holding = true;
}

void Bedler::setSomething(MainClass &object) {
    button.setSomething(300, 300, object.m_window, object.m_camera);
    sight_button.setSomething(300, 300, object.m_window, object.m_camera);
}

void Bedler::set(Map &map, MainClass &object) {
    if (seted == false) {
        float mouse_position_x =
                (float) Mouse::getPosition().x / object.m_window.getSize().x * object.m_camera.getSize().x;
        float mouse_position_y =
                (float) Mouse::getPosition().y / object.m_window.getSize().y * object.m_camera.getSize().y;

        Vector2f path_positions;

        bool path_on_x = false;
        bool can_be_setted = false;

        if (seted == false && holding == true) {
            this->setTextureRect(IntRect(0, 0, 300, 300));
            this->setScale(1.0, 1.0);

            float upp_wall = 0;
            float downn_wall = 0;
            float leftt_wall = 0;
            float rightt_wall = 0;

            int smallest_stopper = 220;
            int smaller_stopper = 220;
            int bigger_stopper = 420;

            for (int i = 1; i < map.getCountOfPathBlocks(); i++) {
                path_positions = map.getPathBlocksPosition(i - 1);

                if (map.getWhereIsGoingPath(i) == 'x' && path_on_x == true) {
                    upp_wall = path_positions.y - smaller_stopper;
                    downn_wall = path_positions.y + smaller_stopper;
                    leftt_wall = path_positions.x - bigger_stopper;
                    rightt_wall = path_positions.x + bigger_stopper;
                }
                if (map.getWhereIsGoingPath(i) == 'y' && path_on_x == false) {
                    upp_wall = path_positions.y - bigger_stopper;
                    downn_wall = path_positions.y + bigger_stopper;
                    leftt_wall = path_positions.x - smaller_stopper;
                    rightt_wall = path_positions.x + smaller_stopper;
                }

                if (map.getWhereIsGoingPath(i) == 'x' && path_on_x == false) {
                    upp_wall = path_positions.y - smallest_stopper;
                    downn_wall = path_positions.y + smallest_stopper;
                    leftt_wall = path_positions.x - smallest_stopper;
                    rightt_wall = path_positions.x + smallest_stopper;

                    path_on_x = true;
                }
                if (map.getWhereIsGoingPath(i) == 'y' && path_on_x == true) {
                    upp_wall = path_positions.y - smallest_stopper;
                    downn_wall = path_positions.y + smallest_stopper;
                    leftt_wall = path_positions.x - smallest_stopper;
                    rightt_wall = path_positions.x + smallest_stopper;

                    path_on_x = false;
                }


                if (this->getPosition().y > upp_wall && this->getPosition().y < downn_wall &&
                    this->getPosition().x > leftt_wall && this->getPosition().x < rightt_wall) {
                    can_be_setted = false;
                    this->setTextureRect(IntRect(600, 0, 300, 300));
                    i = map.getCountOfPathBlocks() + 1;
                } else if (this->getPosition().y <= upp_wall || this->getPosition().y >= downn_wall ||
                           this->getPosition().x <= leftt_wall || this->getPosition().x >= rightt_wall) {
                    can_be_setted = true;
                    this->setTextureRect(IntRect(0, 0, 300, 300));
                }
            }
        }
        if (button.holding() == false) {
            this->setPosition(mouse_position_x, mouse_position_y);
        }
        if (can_be_setted == true) {
            button.use();
            if (button.holding() == true) {
                this->setScale(0.98, 0.98);
            }
        }
        if (button.released() == true && seted == false && holding == true && can_be_setted == true) {
            seted = true;
            holding = false;

            this->setRotation(0);
            this->setTextureRect(IntRect(0, 0, 300, 300));
            this->setScale(0.95, 0.95);

            result.setPosition(getPosition());;
        }
    }
}

void Bedler::work(Bedler object, Map &map, MainClass &main, vector<Mactangle> &mactangles) {
    this->setTexture(bedler_texture);
    this->setSomething(main);
    this->testForClick(object);
    this->writeResult(main, mactangles);
}

void Bedler::testForClick(Bedler object) {
    if (seted == true) {
        button.use(object);

        if (button.mouseOn() == true) {
            this->setTextureRect(IntRect(300, 0, 300, 300));
        } else if (button.mouseOn() == false) {
            this->setTextureRect(IntRect(0, 0, 300, 300));
        }
        if (button.holding() == true && button.mouseOn() == true) {
            this->setTextureRect(IntRect(300, 0, 300, 300));
            pressed = false;
        }
        if (button.released() == true && button.mouseOn() == true) {
            pressed = true;
        }
        if (button.mouseOn() == false) {
            button.use();
            if (button.holding() == true) {
                pressed = false;
            }
        }

        if (sight_holding == false) {
            sight.setPosition(getPosition().x + 35, getPosition().y + 155);
        }

        /*sight_button.use(sight);

        if (sight_button.mouseOn() == true)
        {
            sight.setTextureRect(IntRect(300, 0, 300, 300));
        }
        else if (sight_button.mouseOn() == false)
        {
            sight.setTextureRect(IntRect(0, 0, 300, 300));
        }
        if (sight_button.holding() == true)
        {
            sight.setTextureRect(IntRect(300, 0, 300, 300));
        }
        if (sight_button.released() == true && sight_button.mouseOn() == true)
        {
            sight_holding = true;
        }*/
    }
}

void Bedler::writeResult(MainClass &main, vector<Mactangle> &mactangles) {
    if (pressed) {
        std::vector<sf::Keyboard::Key> keys = InputManager::getKeys();
        for (auto &key: keys) {
            sf::String newChar = getCharFromNumber(key);
            if (newChar == "\n") {
                if (testMactangles(mactangles) == true) {
                    add_money = true;
                }
            } else if (newChar == "\b") {
                if (result_text.getSize() >= 1)
                    result_text.erase(result_text.getSize() - 1);
            } else if (newChar == "-") {
                if (result_text[0] != '-')
                    result_text[0] = '-';
                else
                    result_text[0] = ' ';
            } else if (result_text.getSize() < 5) {
                result_text += newChar;
            }

        }
        result.setString(result_text);
    }
}

bool Bedler::testMactangles(vector<Mactangle> &mactangles) {
    for (int i = 0, size = mactangles.size(); i < size; i++) {
        sf::String temp = result_text;
        if (result_text[0] == ' ')
            temp = result_text.substring(1, result_text.getSize() - 1);
        if (temp == to_string(mactangles[i].getResult())) {
            mactangles.erase(mactangles.begin() + (i));
            return true;
        }
    }
}

bool Bedler::addMoney() {
    if (add_money == true) {
        add_money = false;
        return true;
    } else {
        return false;
    }
}

void Bedler::textureReset() {
    sight.setTexture(sight_texture);
    this->setTexture(bedler_texture);
}

void Bedler::display(MainClass &main) {
    main.m_window.draw(result);
    main.m_window.draw(sight);
}

void Bedler::setSetted() {
    seted = true;
}

bool Bedler::getMainBool() {
    return holding;
}

Texture Bedler::getHimTexture() {
    return bedler_texture;
}