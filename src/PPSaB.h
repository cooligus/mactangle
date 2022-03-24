#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Button
{
	bool object_pressed;
	bool object_holding;
	bool object_released;
	bool mouse_on_object;
	int first_holding_counter;
	int second_holding_counter;
	int camera_size_x;
	int camera_size_y;
	int window_size_x;
	int window_size_y;
	int object_size_x;
	int object_size_y;

public:
	Button();
	Button(float false_object_size_x, float false_object_size_y, RenderWindow& window);
	Button(float false_object_size_x, float false_object_size_y, RenderWindow& window, View& camera);
	void setSomething(float false_object_size_x, float false_object_size_y, RenderWindow& window);
	void setSomething(float false_object_size_x, float false_object_size_y, RenderWindow& window, View& camera);
	void use(Sprite& object);
	void use();
	bool mouseOn();
	bool holding();
	bool released();
};
class PercentagePosition : public Vector2f
{
public:
	PercentagePosition(float percentage_position_x, float percentage_position_y, RenderWindow& window);
	PercentagePosition(float percentage_position_x, float percentage_position_y, View& camera);
};
class PercentageScale : public Vector2f
{
public:
	PercentageScale(double percentage_scale_x, double percentage_scale_y, Vector2f object_size, RenderWindow& window);
	PercentageScale(double percentage_scale, Vector2f object_size, RenderWindow& window);
	PercentageScale(double percentage_scale_x, double percentage_scale_y, Vector2f object_size, View& camera);
	PercentageScale(double percentage_scale, Vector2f object_size, View& camera);
};
