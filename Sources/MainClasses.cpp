#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "../Headers/MainClasses.h"

using namespace sf;
using namespace std;

MainClass::MainClass()
{
	window_size_x = 3840;
	window_size_y = 2160;
	game_runing = false;

	game_font.loadFromFile("Fonts/CubicCoreMono.ttf");

	VideoMode fullscreen = VideoMode().getDesktopMode();
	window.create(fullscreen, "Mactangle", Style::None);
	window.setVisible(true);
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);
	window.setMouseCursorGrabbed(true);
	window.setActive(true);

	camera.setSize(window_size_x, window_size_y);
	camera.setCenter(window_size_x / 2, window_size_y / 2);
	camera.setViewport(FloatRect(0, 0, 1, 1));

	float base_mouse_position_x = window.getSize().x / 2;
	float base_mouse_position_y = window.getSize().y / 2;
	Mouse::setPosition(Vector2i((int)base_mouse_position_x, (int)base_mouse_position_y));

	window.setView(camera);
}