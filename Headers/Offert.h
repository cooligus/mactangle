#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include "MainClasses.h"
#include "Map.h"
#include "PPSaB.h"
#include "Shop.h"

using namespace sf;
using namespace std;

class Offert
{
	//-------VARIABLES-------//
	Sprite offert;
	Texture offert_texture;
	Sprite coin;
	Texture coin_texture;
	Sprite button;
	Texture button_texture;
	Button button_button;
	Text value;

	float scale;
	int position_x;
	int position_y;
	int starter_position_x;
	int starter_position_y;
	int valuee;
	int which;
	bool mouse_on_offert = false;

	//-------FUNCTIONS-------//
	void offertConfigure(Sprite like_offert, Texture texturee, float scale);
	void buttonConfigure(float scale);
	void coinConfigure(float scale);
	void valueConfigure(int money, MainClass& main);

	void go(Shop& shop);
	void ifHidden(Shop& shop);
	void press(Shop& shop, MainClass& main);
	void addDacler(Shop& shop);
	void addBecler(Shop& shop, MainClass& main);

public:
	Offert(Sprite like_offert, Texture texturee, int offert_position_x, int offert_position_y, int value, float sccale, MainClass& main, int the_which);
	void offertUseful(Shop& shop, MainClass& main);
	void setSomething(MainClass& main);
	void display(Shop& shop, MainClass& main);
};