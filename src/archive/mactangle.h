#pragma once

#include "MainClasses.h"
#include "map.h"

using namespace sf;
using namespace std;


class Mactangle : public Sprite
{
	Texture mactangle_texture;

	Text charset;
	Text number1;
	Text number2;

	float moving_stop = 0;
	float mactangles_moving_speed = 5;
	float mactangles_position_x = 0;
	float mactangles_position_y = 0;
	int result = 0;
	int divider = 120;
	int path_corner = 0;

	void allTextsConfigure(MainClass& main);
public:
	Mactangle(Map& map, MainClass& main);
	int getResult();
	void moving(Map& map);
	void textureReset();
	void displaySomething(MainClass& main);
};