#include "additionals.h"

using namespace sf;
using namespace std;

Addidtionals::Addidtionals(MainClass& main)
{
	characterColor = 255;
	animation_speed = 5;
	going_down = true;

	firstscreen_texture.loadFromFile(FIRSTSCREEN_PNG);
	firstscreen_texture.setSmooth(true);

	firstscreen.setTexture(firstscreen_texture);
	firstscreen.setTextureRect(IntRect(0, 0, 300, 300));
	firstscreen.setOrigin(150, 150);
	firstscreen.setPosition(0, 0);
	firstscreen.setScale(30, 30);
	firstscreen.setColor(Color(15, 15, 15));


	start_text.setFont(main.m_font);
	start_text.setCharacterSize(200);
	start_text.setOrigin(0, 0);
	start_text.setPosition(1450 ,800);
	start_text.setString("Click to play");
	start_text.setFillColor(Color(255, 255, 255));

	moneyConfigure(main);
	heartsConfigure(main, 3);
}
void Addidtionals::moneyConfigure(MainClass& main)
{
	coin_texture.loadFromFile(COIN_PNG);
	coin_texture.setSmooth(true);

	coin.setTexture(coin_texture);
	coin.setTextureRect(IntRect(0, 0, 200, 200));
	coin.setOrigin(100, 100);
	coin.setPosition(100, 100);
	coin.setScale(0.5, 0.5);

	moneey.setOrigin(0, 0);
	moneey.setFillColor(Color(255, 227, 38));
	moneey.setPosition(165, 8);
	moneey.setFont(main.m_font);
	moneey.setCharacterSize(130);
	moneey.setString(to_string(0));
	moneey.setOutlineColor(Color(255, 207, 38));
	moneey.setOutlineThickness(1);
	moneey.setLetterSpacing(1.3);
}
void Addidtionals::heartsConfigure(MainClass& main, int count)
{
	heart_texture.loadFromFile(HEART_PNG);

	for (int i = 1; i <= count; i++)
	{
		hearts.push_back(Sprite());
		hearts.back().setTexture(heart_texture);
		hearts.back().setTextureRect(IntRect(0, 0, 300, 300));
		hearts.back().setOrigin(0, 300);
		hearts.back().setPosition((150 * (i-1)) + 40, main.m_camera.getSize().y - 30);
		hearts.back().setScale(0.5, 0.5);
	}
}
void Addidtionals::doAnimation()
{
	if (characterColor >= 50 && going_down == true)
	{
		characterColor -= animation_speed;
		start_text.setFillColor(Color(characterColor, characterColor, characterColor));
		going_down = true;
	}
	else if (characterColor <= 255 && going_down == false)
	{
		characterColor += animation_speed;
		if(characterColor < 255)
		start_text.setFillColor(Color(characterColor, characterColor, characterColor));
		going_down = false;
	}

	if (characterColor < 50 && going_down == true)
	{
		going_down = false;
	}
	if (characterColor > 255 && going_down == false)
	{
		going_down = true;
	}
}
void Addidtionals::clickToPlay(MainClass& main)
{
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		main.m_gameRuning = true;
	}
}
bool Addidtionals::takeHp(OldMap& map, Mactangle& object)
{
	if (object.getPosition().x == map.getMainPosition(2).x && object.getPosition().y == map.getMainPosition(2).y)
	{
		hearts.pop_back();
		return true;
	}
	return false;
}
bool Addidtionals::gameOver()
{
	if (hearts.size() == 0)
	{
		return true;
	}
	else return false;
}
void Addidtionals::display(Shop& shop, MainClass& main)
{
	if (main.m_gameRuning == false)
	{
		doAnimation();
		main.m_window.draw(firstscreen);
		main.m_window.draw(start_text);
	}
	if (main.m_gameRuning == true)
	{
		moneey.setString(to_string(shop.getMoney()));
		main.m_window.draw(coin);
		main.m_window.draw(moneey);
		for (int i = 1; i <= hearts.size() ; i++)
		{
			main.m_window.draw(hearts[i-1]);
		}
	}	
}