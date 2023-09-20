#pragma once

#include "mainclasses.h"
#include "map.h"
#include "dacler.h"
#include "mactangle.h"

using namespace sf;
using namespace std;

class Dacler : public Sprite
{
	//-----VARIABLES-----//

	Texture dacler_texture;
	Button button;
	bool seted = false;
	bool holding = false;
	bool can_do_animation = false;
	bool pressed = false;
	int counter_of_mouth_animation = 0;
	float scale = 0;

	//-----FUNCTIONS-----//
public:
	Dacler();
	void nowCanBeSetted();
	void setSomething(MainClass& object);
	void set(OldMap& map, MainClass& object);
	void textureReset();
	void setSetted();

	Texture getHimTexture();
	bool canDestroy(Mactangle& test_object);
	bool getMainBool();

	void work(OldMap& map, MainClass& main);
	void display(Dacler& to_draw, MainClass& object);
};