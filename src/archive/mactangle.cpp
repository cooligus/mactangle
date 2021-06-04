#include "Mactangle.h"

using namespace sf;
using namespace std;

Mactangle::Mactangle(Map& map, MainClass& main)
{
	mactangle_texture.loadFromFile("../textures/Mactangle.png");
	mactangle_texture.setSmooth(true);

	this->setTexture(mactangle_texture);
	this->setTextureRect(IntRect(0, 0, 250, 250));
	this->setOrigin(125, 125);
	this->setPosition(map.getMainPosition(1));
	this->setScale(0.6, 0.6);
	this->allTextsConfigure(main);
}
int Mactangle::getResult()
{
	return result;
}
void Mactangle::allTextsConfigure(MainClass& main)
{
	srand(time(NULL));

	charset.setFont(main.m_font);
	charset.setCharacterSize(100);
	charset.setFillColor(Color(255, 255, 255));
	charset.setOrigin(15, 80);
	charset.setScale(1.2, 1.2);
	charset.setPosition(getPosition());

	int randomized = rand() % 3 + 1;
	if (randomized == 1)
	{
		charset.setString('+');
	}	
	if (randomized == 2)
	{
		charset.setString('-');
	}	
	if (randomized == 3)
	{
		charset.setString('+');
	}	
	if (randomized == 4)
	{
		charset.setString('-');
	}

	number1.setFont(main.m_font);
	number1.setCharacterSize(100);
	number1.setFillColor(Color(255, 255, 255));
	number1.setOrigin(80, 130);
	number1.setScale(0.7, 0.7);
	number1.setPosition(getPosition());
	int randomized1 = rand() % divider + 1;
	number1.setString(to_string(randomized1));


	number2.setFont(main.m_font);
	number2.setCharacterSize(100);
	number2.setFillColor(Color(255, 255, 255));
	number2.setOrigin(80, 25);
	number2.setScale(0.7, 0.7);
	number2.setPosition(getPosition());

	int randomized2 = rand() % divider + 1;
	
	if (charset.getString() == '/' && randomized1 < randomized2)
	{
		while (randomized1 < randomized2)
			int randomized2 = rand() % divider + 1;
	}	
	
	number2.setString(to_string(randomized2));

	if (randomized == 1)
	{
		result = randomized1 + randomized2;
	}
	if (randomized == 2)
	{
		result = randomized1 - randomized2;
	}
	if (randomized == 3)
	{
		result = randomized1 + randomized2;
	}
	if (randomized == 4)
	{
		result = randomized1 - randomized2;
	}

	//cout << result << " ";
}
void Mactangle::moving(Map& map)
{
	mactangles_position_x = this->getPosition().x;
	mactangles_position_y = this->getPosition().y;

	vector <int> mactangles_steps_counter = map.path_steps_counter;
	vector <char> mactangles_direction = map.path_direction;

	if (mactangles_steps_counter[path_corner] > 0)
	{
		if (mactangles_direction[path_corner] == 'r' && moving_stop < mactangles_steps_counter[path_corner]
			|| mactangles_direction[path_corner] == 'd' && moving_stop < mactangles_steps_counter[path_corner])
		{
			if (mactangles_direction[path_corner] == 'r')
			{
				this->setPosition(Vector2f(mactangles_position_x + mactangles_moving_speed, mactangles_position_y));
				moving_stop += mactangles_moving_speed;
			}
			else if (mactangles_direction[path_corner] == 'd')
			{

				this->setPosition(Vector2f(mactangles_position_x, mactangles_position_y + mactangles_moving_speed));
				moving_stop += mactangles_moving_speed;
			}
		}
		if (moving_stop >= mactangles_steps_counter[path_corner])
		{
			moving_stop = 0;
			path_corner++;
		}
	}
	else if (mactangles_steps_counter[path_corner] < 0)
	{
		if (mactangles_direction[path_corner] == 'l' && moving_stop > mactangles_steps_counter[path_corner]
			|| mactangles_direction[path_corner] == 'u' && moving_stop > mactangles_steps_counter[path_corner])
		{
			if (mactangles_direction[path_corner] == 'l')
			{
				this->setPosition(Vector2f(mactangles_position_x - mactangles_moving_speed, mactangles_position_y));
				moving_stop -= mactangles_moving_speed;
			}
			else if (mactangles_direction[path_corner] == 'u')
			{
				this->setPosition(Vector2f(mactangles_position_x, mactangles_position_y - mactangles_moving_speed));
				moving_stop -= mactangles_moving_speed;
			}
		}
		if (moving_stop <= mactangles_steps_counter[path_corner])
		{
			moving_stop = 0;
			path_corner++;
		}
	}

	charset.setPosition(this->getPosition());
	number1.setPosition(this->getPosition());
	number2.setPosition(this->getPosition());
}
void Mactangle::textureReset()
{
	this->setTexture(mactangle_texture);
}
void Mactangle::displaySomething(MainClass& main)
{
	main.m_window.draw(charset);
	main.m_window.draw(number1);
	main.m_window.draw(number2);
}