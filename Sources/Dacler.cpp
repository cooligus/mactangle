#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "../Headers/PPSaB.h"
#include "../Headers/Dacler.h"
#include "../Headers/Shop.h"
#include "../Headers/Map.h"
#include "../Headers/MainClasses.h"

using namespace sf;
using namespace std;

Dacler::Dacler()
{
	dacler_texture.loadFromFile("Textures/Dacler.png");
	dacler_texture.setSmooth(true);

	this->setTexture(dacler_texture);
	this->setTextureRect(IntRect(0, 0, 300, 300));
	this->setOrigin(150, 150);
	this->setPosition(0, 0);
	this->setScale(0, 0);
}
void Dacler::nowCanBeSetted()
	{
		holding = true;
	}
void Dacler::setSomething(MainClass& object)
{
	button.setSomething(300, 300, object.window, object.camera);
}
void Dacler::set(Map& map, MainClass& object)
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
				this->setScale(0.8, 0.8);

				scale = 0.8;

				float upp_wall = 0;
				float downn_wall = 0;
				float leftt_wall = 0;
				float rightt_wall = 0;

				int smallest_stopper = 8;
				int smaller_stopper = 8;
				int bigger_stopper = 180;

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


					if (this->getPosition().y >= upp_wall && this->getPosition().y <= downn_wall &&
						this->getPosition().x >= leftt_wall && this->getPosition().x <= rightt_wall)
					{
						can_be_setted = true;
						this->setTextureRect(IntRect(600, 0, 300, 300));
						i = map.getCountOfPathBlocks() + 1;
					}

					else if (this->getPosition().y < upp_wall || this->getPosition().y > downn_wall ||
						this->getPosition().x < leftt_wall || this->getPosition().x > rightt_wall)
					{
						can_be_setted = false;
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
			}
		if (button.released() == true && seted == false && holding == true && can_be_setted == true)
			{
				seted = true;
				holding = false;
				this->setRotation(0);
				this->setTextureRect(IntRect(300, 0, 300, 300));
				this->setColor(Color(250, 250, 250));
				this->setScale(0.78, 0.78);
				scale = 0.78;
			}
		}
	}
void Dacler::work(Map& map, MainClass& main)
{
	//this->setTexture(dacler_texture);
}
void Dacler::textureReset()
{
	this->setScale(scale, scale);
	this->setTexture(dacler_texture);
}
void Dacler::display(Dacler& to_draw, MainClass& object)
{
	object.window.draw(to_draw);
}
void Dacler::setSetted()
{
	seted = true;
}
bool Dacler::canDestroy(Mactangle& test_object)
{
	if (seted == true)
	{
		if (test_object.getGlobalBounds().intersects(this->getGlobalBounds()))
		{
			return true;
		}	
	}
	else
	{
		return false;
	}
}
bool Dacler::getMainBool()
{
	return holding;
}
Texture Dacler::getHimTexture()
{
	return dacler_texture;
}