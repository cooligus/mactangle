#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include "../Headers/PPSaB.h"
#include "../Headers/Bedler.h"
#include "../Headers/Shop.h"
#include "../Headers/Map.h"
#include "../Headers/Mactangle.h"
#include "../Headers/MainClasses.h"

using namespace sf;
using namespace std;

Bedler::Bedler(MainClass& main)
{
	bedler_texture.loadFromFile("Textures/Bedler.png");
	bedler_texture.setSmooth(true);

	this->setTexture(bedler_texture);
	this->setTextureRect(IntRect(0, 0, 300, 300));
	this->setOrigin(150, 150);
	this->setPosition(0, 0);
	this->setScale(0, 0);

	result.setFont(main.game_font);
	result.setCharacterSize(100);
	result.setFillColor(Color(255, 255, 255));
	result.setOrigin(100, 30);
	result.setScale(1.2, 1.2);
	result.setPosition(getPosition());;
	result.setString(" ");
}
void Bedler::nowCanBeSetted()
{
	holding = true;
}
void Bedler::setSomething(MainClass& object)
{
	button.setSomething(300, 300, object.window, object.camera);
	sight_button.setSomething(300, 300, object.window, object.camera);
}
void Bedler::set(Map& map, MainClass& object)
{
	if (seted == false)
	{
		float mouse_position_x = (float)Mouse::getPosition().x / object.window.getSize().x * object.camera.getSize().x;
		float mouse_position_y = (float)Mouse::getPosition().y / object.window.getSize().y * object.camera.getSize().y;

		Vector2f path_positions;

		bool path_on_x = false;
		bool can_be_setted = false;

		if (seted == false && holding == true)
		{
			this->setTextureRect(IntRect(0, 0, 300, 300));
			this->setScale(1.0, 1.0);

			float upp_wall = 0;
			float downn_wall = 0;
			float leftt_wall = 0;
			float rightt_wall = 0;

			int smallest_stopper = 220;
			int smaller_stopper = 220;
			int bigger_stopper = 420;

			for (int i = 1; i < map.getCountOfPathBlocks(); i++)
			{
				path_positions = map.getPathBlocksPosition(i - 1);

				if (map.getWhereIsGoingPath(i) == 'x' && path_on_x == true)
				{
					upp_wall = path_positions.y - smaller_stopper;
					downn_wall = path_positions.y + smaller_stopper;
					leftt_wall = path_positions.x - bigger_stopper;
					rightt_wall = path_positions.x + bigger_stopper;
				}
				if (map.getWhereIsGoingPath(i) == 'y' && path_on_x == false)
				{
					upp_wall = path_positions.y - bigger_stopper;
					downn_wall = path_positions.y + bigger_stopper;
					leftt_wall = path_positions.x - smaller_stopper;
					rightt_wall = path_positions.x + smaller_stopper;
				}

				if (map.getWhereIsGoingPath(i) == 'x' && path_on_x == false)
				{
					upp_wall = path_positions.y - smallest_stopper;
					downn_wall = path_positions.y + smallest_stopper;
					leftt_wall = path_positions.x - smallest_stopper;
					rightt_wall = path_positions.x + smallest_stopper;

					path_on_x = true;
				}
				if (map.getWhereIsGoingPath(i) == 'y' && path_on_x == true)
				{
					upp_wall = path_positions.y - smallest_stopper;
					downn_wall = path_positions.y + smallest_stopper;
					leftt_wall = path_positions.x - smallest_stopper;
					rightt_wall = path_positions.x + smallest_stopper;

					path_on_x = false;
				}


				if (this->getPosition().y > upp_wall && this->getPosition().y < downn_wall &&
					this->getPosition().x > leftt_wall && this->getPosition().x < rightt_wall)
				{
					can_be_setted = false;
					this->setTextureRect(IntRect(600, 0, 300, 300));
					i = map.getCountOfPathBlocks() + 1;
				}

				else if (this->getPosition().y <= upp_wall || this->getPosition().y >= downn_wall ||
					this->getPosition().x <= leftt_wall || this->getPosition().x >= rightt_wall)
				{
					can_be_setted = true;
					this->setTextureRect(IntRect(0, 0, 300, 300));
				}
			}
		}
		if (button.holding() == false)
		{
			this->setPosition(mouse_position_x, mouse_position_y);
		}
		if (can_be_setted == true)
		{
			button.use();
			if (button.holding() == true)
			{
				this->setScale(0.98, 0.98);
			}
		}
		if (button.released() == true && seted == false && holding == true && can_be_setted == true)
		{
			seted = true;
			holding = false;

			this->setRotation(0);
			this->setTextureRect(IntRect(0, 0, 300, 300));
			this->setScale(0.95, 0.95);

			result.setPosition(getPosition());;
		}
	}
}
void Bedler::work(Bedler object, Map& map, MainClass& main, vector<Mactangle>& mactangles)
{
	this->setTexture(bedler_texture);
	this->setSomething(main);
	this->testForClick(object);
	this->writeResult(main, mactangles);
}
void Bedler::testForClick(Bedler object)
{
	if (seted == true)
	{
		button.use(object);

		if (button.mouseOn() == true)
		{
			this->setTextureRect(IntRect(300, 0, 300, 300));
		}
		else if (button.mouseOn() == false)
		{
			this->setTextureRect(IntRect(0, 0, 300, 300));
		}
		if (button.holding() == true && button.mouseOn() == true)
		{
			this->setTextureRect(IntRect(300, 0, 300, 300));
			pressed = false;
		}
		if (button.released() == true && button.mouseOn() == true)
		{
			pressed = true;
		}
		if (button.mouseOn() == false)
		{
			button.use();
			if (button.holding() == true)
			{
				pressed = false;
			}
		}

		if (sight_holding == false)
		{
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
void Bedler::writeResult(MainClass& main, vector<Mactangle>& mactangles)
{
	if (pressed == true)
	{
		while (main.window.pollEvent(eventus))
		{
			if (result_text.getSize() < 5)
			{
				if (touch_counter == 0 && Keyboard::isKeyPressed(Keyboard::Num0) || Keyboard::isKeyPressed(Keyboard::Numpad0) && touch_counter == 0)
				{
					result_text += "0";
					touch_counter++;
				}
				if (touch_counter == 0 && Keyboard::isKeyPressed(Keyboard::Num1) || Keyboard::isKeyPressed(Keyboard::Numpad1) && touch_counter == 0)
				{
					result_text += "1";
					touch_counter++;
				}
				if (touch_counter == 0 && Keyboard::isKeyPressed(Keyboard::Num2) || Keyboard::isKeyPressed(Keyboard::Numpad2) && touch_counter == 0)
				{
					result_text += "2";
					touch_counter++;
				}
				if (touch_counter == 0 && Keyboard::isKeyPressed(Keyboard::Num3) || Keyboard::isKeyPressed(Keyboard::Numpad3) && touch_counter == 0)
				{
					result_text += "3"; 
					touch_counter++;
				}
				if (touch_counter == 0 && Keyboard::isKeyPressed(Keyboard::Num4) || Keyboard::isKeyPressed(Keyboard::Numpad4) && touch_counter == 0)
				{
					result_text += "4";
					touch_counter++;
				}
				if (touch_counter == 0 && Keyboard::isKeyPressed(Keyboard::Num5) || Keyboard::isKeyPressed(Keyboard::Numpad5) && touch_counter == 0)
				{
					result_text += "5";
					touch_counter++;
				}
				if (touch_counter == 0 && Keyboard::isKeyPressed(Keyboard::Num6) || Keyboard::isKeyPressed(Keyboard::Numpad6) && touch_counter == 0)
				{
					result_text += "6";
					touch_counter++;
				}
				if (touch_counter == 0 && Keyboard::isKeyPressed(Keyboard::Num7) || Keyboard::isKeyPressed(Keyboard::Numpad7) && touch_counter == 0)
				{
					result_text += "7";
					touch_counter++;
				}
				if (touch_counter == 0 && Keyboard::isKeyPressed(Keyboard::Num8) || Keyboard::isKeyPressed(Keyboard::Numpad8) && touch_counter == 0)
				{
					result_text += "8";
					touch_counter++;
				}
				if (touch_counter == 0 && Keyboard::isKeyPressed(Keyboard::Num9) || Keyboard::isKeyPressed(Keyboard::Numpad9) && touch_counter == 0)
				{
					result_text += "9";
					touch_counter++;
				}
			}
			if (result_text.getSize() != 0)
			{
				if (Keyboard::isKeyPressed(Keyboard::Backspace))result_text.erase(result_text.getSize() - 1);
				touch_counter++;
			}
			if (result_text.getSize() == 0)
			{
				if (Keyboard::isKeyPressed(Keyboard::Dash))result_text += "-";
				touch_counter++;
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				if(testMactangles(mactangles) == true)
					add_money = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))pressed = false;
		}
		if (touch_counter > 0)
		{
			touch_counter++;
		}
		if (touch_counter > 1)
		{
			touch_counter = 0;
		}
	}
	result.setString(result_text);
}
bool Bedler::testMactangles(vector<Mactangle>& mactangles)
{
	for (int i = 1; mactangles.size() > i; i++)
	{
		if (result.getString() == to_string(mactangles[i].getResult()))
		{
			mactangles.erase(mactangles.begin() + (i));
			return true;
		}	
	}
}
bool Bedler::addMoney()
{
	if (add_money == true)
	{
		add_money = false;
		return true;
	}
	else
	{
		return false;
	}
}
void Bedler::textureReset()
{
	sight.setTexture(sight_texture);
	this->setTexture(bedler_texture);
}
void Bedler::display(MainClass& main)
{
	main.window.draw(result);
	main.window.draw(sight);
}
void Bedler::setSetted()
{
	seted = true;
}
bool Bedler::getMainBool()
{
	return holding;
}
Texture Bedler::getHimTexture()
{
	return bedler_texture;
}