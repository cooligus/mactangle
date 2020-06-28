#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include "MainClasses.h"
#include "Map.h"
#include "Dacler.h"
#include "Bedler.h"
#include "Mactangle.h"
#include "PPSaB.h"

using namespace sf;
using namespace std;

class Shop
{
	//-------VARIABLES-------//

	Sprite shop;
	Texture shop_texture;
	Sprite cart;
	Button cart_button;
	Texture cart_texture;
	Sprite sharp;
	Button sharp_button;
	Texture sharp_texture;
	
	int sharp_stopper;
	int cart_stopper;
	int mactangles_counter;
	int destroy_counter;

	bool shop_visible;
	bool sharp_can_go;
	bool cart_can_go;
	bool sharp_pressed;
	bool cart_pressed;

	float shop_size_x;
	float shop_size_y;
	float sharp_position_x;
	float sharp_position_y;
	float cart_position_x;
	float cart_position_y;
	float cart_scale;
	float sharp_scale;

	//---CONFIGURE_FUNCTIONS---//
	void shopConfigure(MainClass& main);
	void cartConfigure();
	void sharpConfigure();

	//----NORMAL_FUNCTIONS----//
	void shopOpening();
	void shopReset();
	void cartPress();
	void sharpPress();
	void addMactangles(Map& map, MainClass& main);

public:
	Shop(MainClass& main, Map map);

	void setSomething(MainClass& main);
	void offertPressed(int value);
	void destroyMactangle();
	bool getVisible();
	bool getCanOffertGo();
	int getMoney();

	void working(Map& map, MainClass& main);
	void display(MainClass& main);
	
	vector <Mactangle> mactangles;
	vector <Dacler> daclers;
	vector <Bedler> bedlers;
	int money;
};