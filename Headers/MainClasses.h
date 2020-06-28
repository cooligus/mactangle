#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

using namespace sf;
using namespace std;

class MainClass
{
public:
	RenderWindow window;
	View camera;
	Font game_font;
	float window_size_x;
	float window_size_y;
	bool game_runing;

	MainClass();
};
class BetterSprite: public Sprite
{
public:
	BetterSprite(Texture texture, IntRect size, Vector2f origin_position, Vector2f starter_position, Vector2f scale);
};