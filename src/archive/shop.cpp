#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "MainClasses.h"
#include "Map.h"
#include "Shop.h"
#include "PPSaB.h"

using namespace sf;
using namespace std;

Shop::Shop(MainClass& main, Map map)
{
	money = 100;
	sharp_stopper = 0;
	cart_stopper = 0;

	shop_visible = false;
	sharp_can_go = false;
	cart_can_go = false;
	sharp_pressed = false;
	cart_pressed = false;

	shop_size_x = 0.01;
	shop_size_y = 7.2;
	sharp_position_x = 3900;
	sharp_position_y = 100;
	cart_position_x = 3900;
	cart_position_y = 100;
	cart_scale = 1;
	sharp_scale = 0.75;

	daclers.push_back(Dacler());
	bedlers.push_back(Bedler(main));
	mactangles.push_back(Mactangle(map, main));

	shopConfigure(main);
	cartConfigure();
	sharpConfigure();
}
void Shop::shopConfigure(MainClass& main)
{
	shop_texture.loadFromFile("../textures/Shop.png");
	shop_texture.setSmooth(true);

	shop.setTexture(shop_texture);
	shop.setTextureRect(IntRect(0, 0, 300, 300));
	shop.setOrigin(300, 300);
	shop.setPosition(main.m_camera.getSize().x, main.m_camera.getSize().y);
	shop.setScale(0.0, shop_size_y);
}
void Shop::cartConfigure()
{
	cart_texture.loadFromFile("../textures/Cart.png");
	cart_texture.setSmooth(true);

	cart.setTexture(cart_texture);
	cart.setTextureRect(IntRect(0, 0, 150, 150));
	cart.setOrigin(75, 75);
	cart.setPosition(cart_position_x, cart_position_y);
	cart.setScale(cart_scale, cart_scale);
}
void Shop::sharpConfigure()
{
	sharp_texture.loadFromFile("../textures/Sharp.png");
	sharp_texture.setSmooth(true);

	sharp.setTexture(sharp_texture);
	sharp.setTextureRect(IntRect(0, 0, 150, 150));
	sharp.setOrigin(75, 75);
	sharp.setPosition(sharp_position_x, sharp_position_y);
	sharp.setScale(sharp_scale, sharp_scale);
}

void Shop::shopOpening()
{
	if (shop_visible == true)
	{
		if (sharp_pressed == true && shop.getScale().x < 0.001)
		{
			shopReset();
		}
		if (sharp_pressed == true)
		{
			shop.setScale(shop_size_x /= 1.2, shop_size_y);
		}
		if (cart_pressed == true && shop_size_x <= 3)
		{
			shop.setScale(shop_size_x *= 1.2, shop_size_y);
		}
	}

	if (cart_pressed == true && shop_visible == false)
	{
		shop.setScale(0.01, shop_size_y);
		shop_visible = true;
	}
	if (shop_size_x > 3)
	{
		sharp_can_go = true;
	}
	if (sharp_can_go == true && sharp_stopper <= 14)
	{
		sharp.setPosition(sharp_position_x -= 10, sharp_position_y);
		sharp_stopper++;
	}

	if (shop_size_x < 3)
	{
		cart_can_go = true;
	}
	if (cart_can_go == true && cart_stopper <= 7)
	{
		cart.setPosition(cart_position_x -= 20, sharp_position_y);
		cart_stopper++;
	}
}
void Shop::shopReset()
{
	shop.setScale(0.0, shop_size_y);
	shop_visible = false;

	sharp_position_x = 3900;
	sharp_pressed = false;
	sharp_can_go = false;
	sharp_stopper = 0;
	sharp.setPosition(sharp_position_x, sharp_position_y);

	cart_position_x = 3900;
	cart_pressed = false;
	cart_can_go = false;
	cart_stopper = 0;
	cart.setPosition(cart_position_x, cart_position_y);
}
void Shop::cartPress()
{
	if (cart_pressed == false && sharp_pressed == false)
	{
		cart_button.use(cart);

		if (cart_button.mouseOn() == true)
		{
			cart.setTextureRect(IntRect(150, 0, 150, 150));
		}
		else
		{
			cart.setTextureRect(IntRect(0, 0, 150, 150));
		}

		if (cart_button.holding() == true)
		{
			cart.setScale(cart_scale - 0.05, cart_scale - 0.05);
			cart.setTextureRect(IntRect(150, 0, 150, 150));
		}
		if (cart_button.released() == true)
		{
			cart.setTextureRect(IntRect(150, 0, 150, 150));
			cart.setScale(cart_scale, cart_scale);
			cart_pressed = true;
			sharp_pressed = false;
		}
	}
}
void Shop::sharpPress()
{
	if (cart_pressed == true && sharp_pressed == false)
	{
		sharp_button.use(sharp);

		if (sharp_button.mouseOn() == true)
		{
			sharp.setTextureRect(IntRect(150, 0, 150, 150));
		}
		else
		{
			sharp.setTextureRect(IntRect(0, 0, 150, 150));
		}

		if (sharp_button.holding() == true)
		{
			sharp.setScale(sharp_scale - 0.05, sharp_scale - 0.05);
			sharp.setTextureRect(IntRect(150, 0, 150, 150));
		}
		if (sharp_button.released() == true)
		{
			sharp.setTextureRect(IntRect(150, 0, 150, 150));
			sharp.setScale(sharp_scale, sharp_scale);
			cart_pressed = false;
			sharp_pressed = true;
		}
	}
}

void Shop::setSomething(MainClass& main)
	{
		cart_button.setSomething(300, 300, main.m_window, main.m_camera);
		sharp_button.setSomething(150, 150, main.m_window, main.m_camera);
	}
void Shop::offertPressed(int value)
	{
		sharp_pressed = true;
		cart_pressed = false;
		cart_can_go = false;
		money -= value;
	}
void Shop::addMactangles(Map& map, MainClass& main)
{
	mactangles_counter++;
	if (mactangles_counter >= 300)
	{
		mactangles.push_back(Mactangle(map, main));
		mactangles_counter = 0;
	}
}
void Shop::destroyMactangle()
{
	for (int i = 1; i < daclers.size(); i++)
	{
		for (int j = 1; j < mactangles.size(); j++)
		{
			if (daclers[1].canDestroy(mactangles[1]) == true)
			{
				destroy_counter++;
				if (destroy_counter >= 40)
				{
					daclers.erase(daclers.begin());
					mactangles.erase(mactangles.begin());
					destroy_counter = 0;
					money += 20;
				}
			}
			else if (daclers[i].canDestroy(mactangles[j]) == true)
			{
				destroy_counter++;
				if (destroy_counter >= 40)
				{
					daclers.erase(daclers.begin() + (i));
					mactangles.erase(mactangles.begin() + (j));
					destroy_counter = 0;
					money += 20;
				}
			}
		}
	}
}

bool Shop::getVisible()
	{
		if (cart_pressed == true && sharp_pressed == false && shop_visible == true)
			return true;
		else
			return false;
	}
bool Shop::getCanOffertGo()
	{
		if (sharp_can_go == true && sharp_stopper <= 14)
			return true;
		else
			return false;
	}
int Shop::getMoney()
	{
		return money;
	}

void Shop::working(Map& map, MainClass& main)
{
	addMactangles(map, main);
	shopOpening();
	cartPress();
	sharpPress();
}
void Shop::display(MainClass& main)
	{
		main.m_window.draw(shop);
		if (cart_pressed == false && shop_visible == false)
		{
			main.m_window.draw(cart);
		}
		else if (cart_pressed == true && sharp_pressed == false && shop_visible == true)
		{
			main.m_window.draw(sharp);
		}
	}