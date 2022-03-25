#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

//using namespace sf;
//using namespace std;

class MainClass
{

public:
	sf::RenderWindow m_window;
	sf::View m_camera;
	sf::Font m_font;
	float m_windowSizeX;
	float m_windowSizeY;
	bool m_gameRuning;

	MainClass();
};

class BetterSprite: public sf::Sprite
{
public:
	BetterSprite(sf::Texture texture, sf::IntRect size, sf::Vector2f origin_position, sf::Vector2f starter_position, sf::Vector2f scale)
	{

	}
};