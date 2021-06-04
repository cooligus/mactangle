#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "MainClasses.h"
#include "Offert.h"
#include "PPSaB.h"

using namespace sf;
using namespace std;

Offert::Offert(Sprite like_offert, Texture texture, int offert_position_x, int offert_position_y, int value, float sccale, MainClass& main, int the_which)
{
	scale = sccale;
	position_x = offert_position_x;
	position_y = offert_position_y;

	valuee = value;
	which = the_which;

	starter_position_x = offert_position_x;
	starter_position_y = offert_position_y;

	offertConfigure(like_offert, texture, scale);
	buttonConfigure(scale);
	coinConfigure(0.3);
	valueConfigure(value, main);
}
void Offert::offertConfigure(Sprite like_offert, Texture texture, float scale)
{
	offert_texture = texture;
	offert.setTexture(offert_texture);
	offert.setTextureRect(like_offert.getTextureRect());
	offert.setOrigin(like_offert.getOrigin());
	offert.setPosition(position_x, position_y);
	offert.setScale(scale, scale);
}
void Offert::buttonConfigure(float scale)
{
	button_texture.loadFromFile("../textures/BuyButton.png");
	button_texture.setSmooth(true);

	button.setTexture(button_texture);
	button.setTextureRect(IntRect(0, 0, 300, 100));
	button.setOrigin(150, 50);
	button.setPosition(position_x, position_y);
	button.setScale(scale, scale);
}
void Offert::coinConfigure(float scale)
{
	coin_texture.loadFromFile("../textures/Coin.png");
	coin_texture.setRepeated(2);

	coin.setTexture(coin_texture);
	coin.setTextureRect(IntRect(0, 0, 200, 200));
	coin.setOrigin(150, 80);
	coin.setPosition(position_x, position_y);
	coin.setScale(scale, scale);
}
void Offert::valueConfigure(int money, MainClass& main)
{
	value.setOrigin(28, 18);
	value.setFillColor(Color(255, 227, 38));
	value.setPosition(position_x, position_y);
	value.setFont(main.m_font);
	value.setCharacterSize(80);
	value.setString(to_string(money));
	value.setOutlineColor(Color(255, 207, 38));
	value.setOutlineThickness(1);
	value.setLetterSpacing(1.3);
}

void Offert::go(Shop& shop)
{
	if (shop.getCanOffertGo() == true)
	{
		offert.setPosition(position_x -= 50, position_y);
		button.setPosition(position_x, position_y);
		coin.setPosition(position_x + 60, position_y + 90);
		value.setPosition(position_x - 60, position_y + 60);
	}
}
void Offert::ifHidden(Shop& shop)
{
	if (shop.getVisible() == false)
	{
		position_x = starter_position_x;

		offert.setPosition(position_x, position_y);
		button.setPosition(position_x, position_y);
		coin.setPosition(position_x, position_y);
		value.setPosition(position_x, position_y);
	}
}
void Offert::press(Shop& shop, MainClass& main)
{
	button_button.use(button);
	int money = shop.getMoney();

	if (button_button.mouseOn() == true)
	{
		button.setTextureRect(IntRect(300, 0, 300, 100));
	}
	else
	{
		button.setTextureRect(IntRect(0, 0, 300, 300));
	}

	if (button_button.holding() == true)
	{
		button.setScale(scale - 0.05, scale - 0.05);
		button.setTextureRect(IntRect(300, 0, 300, 100));
	}
	if (button_button.released() == true && money >= valuee)
	{
		position_x = starter_position_x;

		if (which == 1)
		{
			addDacler(shop);
		}
		if (which == 2)
		{
			addBecler(shop, main);
		}

		shop.offertPressed(valuee);

		button.setScale(scale, scale);
		offert.setPosition(position_x, position_y);
		button.setPosition(position_x, position_y);
		coin.setPosition(position_x, position_y);
		value.setPosition(position_x, position_y);
	}
}
void Offert::addDacler(Shop& shop)
{
	shop.daclers.push_back(Dacler());
	shop.daclers.back().nowCanBeSetted();
}
void Offert::addBecler(Shop& shop, MainClass& main)
{
	shop.bedlers.push_back(Bedler(main));
	shop.bedlers.back().nowCanBeSetted();
}

void Offert::offertUseful(Shop& shop, MainClass& main)
	{
		go(shop);
		ifHidden(shop);
		press(shop, main);
	}
void Offert::setSomething(MainClass& main)
	{
		button_button.setSomething(300, 100, main.m_window, main.m_camera);
	}
void Offert::display(Shop& shop, MainClass& main)
	{
		if (shop.getVisible() == true)
		{
			main.m_window.draw(offert);
			main.m_window.draw(button);
			main.m_window.draw(coin);
			main.m_window.draw(value);
		}
	}