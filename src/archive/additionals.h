#pragma once

#include "Shop.h"

using namespace sf;
using namespace std;

class Addidtionals
{
	Text start_text;
	Sprite firstscreen;
	Texture firstscreen_texture;

	Texture heart_texture;
	vector <Sprite> hearts;

	Sprite coin;
	Texture coin_texture;
	Text moneey;

	float characterColor;
	float animation_speed;
	bool going_down;
	int hp;

	void heartsConfigure(MainClass& main, int count);
	void moneyConfigure(MainClass& main);

public:
	Addidtionals(MainClass& main);
	void doAnimation();
	void clickToPlay(MainClass& main);
	
	bool takeHp(Map& map, Mactangle& object);
	bool gameOver();
	void display(Shop& shop, MainClass& object);
};
