#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "../Headers/PPSaB.h"

using namespace sf;
using namespace std;

//Button. No lama.
Button::Button()
{
	object_pressed = false;
	object_holding = false;
	object_released = false;
	mouse_on_object = false;
	first_holding_counter = 0;
	second_holding_counter = 0;
	window_size_x = 0;
	window_size_y = 0;
	camera_size_x = 0;
	camera_size_y = 0;
	object_size_x = 0;
	object_size_y = 0;
}
Button::Button(float false_object_size_x, float false_object_size_y, RenderWindow& window)
{
	object_pressed = false;
	object_holding = false;
	object_released = false;
	mouse_on_object = false;
	first_holding_counter = 0;
	second_holding_counter = 0;
	window_size_x = window.getSize().x;
	window_size_y = window.getSize().y;
	camera_size_x = window.getSize().x;
	camera_size_y = window.getSize().y;
	object_size_x = false_object_size_x;
	object_size_y = false_object_size_y;
}
Button::Button(float false_object_size_x, float false_object_size_y, RenderWindow& window, View& camera)
{
	object_pressed = false;
	object_holding = false;
	object_released = false;
	mouse_on_object = false;
	first_holding_counter = 0;
	second_holding_counter = 0;
	window_size_x = window.getSize().x;
	window_size_y = window.getSize().y;
	camera_size_x = window.getSize().x;
	camera_size_y = window.getSize().y;
	object_size_x = false_object_size_x;
	object_size_y = false_object_size_y;
}
void Button::setSomething(float false_object_size_x, float false_object_size_y, RenderWindow& window)
{
	window_size_x = window.getSize().x;
	window_size_y = window.getSize().y;
	camera_size_x = window.getSize().x;
	camera_size_y = window.getSize().y;
	object_size_x = false_object_size_x;
	object_size_y = false_object_size_y;
}
void Button::setSomething(float false_object_size_x, float false_object_size_y, RenderWindow& window, View& camera)
{
	window_size_x = window.getSize().x;
	window_size_y = window.getSize().y;
	camera_size_x = camera.getSize().x;
	camera_size_y = camera.getSize().y;
	object_size_x = false_object_size_x;
	object_size_y = false_object_size_y;
}
void Button::use(Sprite& object)
{
	float mouse_position_x = (float)Mouse::getPosition().x / window_size_x * camera_size_x;
	float mouse_position_y = (float)Mouse::getPosition().y / window_size_y * camera_size_y;

	int cart_positon_left = object.getPosition().x - object_size_x / 2 * object.getScale().x;
	int cart_positon_up = object.getPosition().y - object_size_y / 2 * object.getScale().y;
	int cart_positon_right = object.getPosition().x + object_size_x / 2 * object.getScale().x;
	int cart_positon_down = object.getPosition().y + object_size_y / 2 * object.getScale().y;

	if (mouse_position_x > cart_positon_left&& mouse_position_x < cart_positon_right &&
		mouse_position_y > cart_positon_up&& mouse_position_y < cart_positon_down)
	{
		mouse_on_object = true;
	}
	else
	{
		mouse_on_object = false;
	}

	second_holding_counter = first_holding_counter;

	if (Mouse::isButtonPressed(Mouse::Left) && mouse_on_object == true && object_pressed == false)
	{
		if (first_holding_counter < 10)
		{
			first_holding_counter++;
		}
		if (first_holding_counter >= 10)
		{
			first_holding_counter = 0;
		}

		object_pressed = true;
		object_holding = true;
		object_released = false;
	}
	if (Mouse::isButtonPressed(Mouse::Left) && object_pressed == true)
	{
		if (first_holding_counter < 10)
		{
			first_holding_counter++;
		}
		if (first_holding_counter >= 10)
		{
			first_holding_counter = 0;
		}

		object_pressed = true;
		object_holding = true;
		object_released = false;
	}
	if (second_holding_counter == first_holding_counter && object_holding == true)
	{
		object_pressed = false;
		object_holding = false;
		object_released = true;
	}
}
void Button::use()
{
	second_holding_counter = first_holding_counter;
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (first_holding_counter < 10)
		{
			first_holding_counter++;
		}
		if (first_holding_counter >= 10)
		{
			first_holding_counter = 0;
		}

		object_holding = true;
		object_released = false;
	}
	if (second_holding_counter == first_holding_counter && object_holding == true)
	{
		object_holding = false;
		object_released = true;
	}
}
bool Button::mouseOn()
{
	return mouse_on_object;
}
bool Button::holding()
{
	return object_holding;
}
bool Button::released()
{
	if (object_released == true)
	{
		object_released = false;
		return true;
	}
	else
	{
		return object_released;
	}
}

//Special class. You can use that to set your sprite on percentage position.
PercentagePosition::PercentagePosition(float percentage_position_x, float percentage_position_y, RenderWindow& window)
{
	this->x = (float)percentage_position_x / 100 * window.getSize().x;
	this->y = (float)percentage_position_y / 100 * window.getSize().y;
}
//Special class. You can use that to set your sprite on percentage position.
PercentagePosition::PercentagePosition(float percentage_position_x, float percentage_position_y, View& camera)
{
	this->x = (float)percentage_position_x / 100 * camera.getSize().x;
	this->y = (float)percentage_position_y / 100 * camera.getSize().y;
}

//Special class. You can use that to set your sprite on percentage scale.
PercentageScale::PercentageScale(double percentage_scale_x, double percentage_scale_y, Vector2f object_size, RenderWindow& window)
{
	this->x = (double)1 / object_size.x * window.getSize().x * (percentage_scale_x / 100);
	this->y = (double)1 / object_size.y * window.getSize().y * (percentage_scale_y / 100);
}
//Special class. You can use that to set your sprite on percentage scale.
PercentageScale::PercentageScale(double percentage_scale, Vector2f object_size, RenderWindow& window)
{
	this->x = (double)1 / object_size.x * window.getSize().x * (percentage_scale / 100);
	this->y = (double)1 / object_size.y * window.getSize().y * (percentage_scale / 100);
}
//Special class. You can use that to set your sprite on percentage scale.
PercentageScale::PercentageScale(double percentage_scale_x, double percentage_scale_y, Vector2f object_size, View& camera)
{
	this->x = (double)1 / object_size.x * camera.getSize().x * (percentage_scale_x / 100);
	this->y = (double)1 / object_size.y * camera.getSize().y * (percentage_scale_y / 100);
}
//Special class. You can use that to set your sprite on percentage scale.
PercentageScale::PercentageScale(double percentage_scale, Vector2f object_size, View& camera)
{
	this->x = (double)1 / object_size.x * camera.getSize().x * (percentage_scale / 100);
	this->y = (double)1 / object_size.y * camera.getSize().y * (percentage_scale / 100);
}