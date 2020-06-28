#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "../Headers/Additionals.h"
#include "../Headers/MainClasses.h"
#include "../Headers/Mactangle.h"
#include "../Headers/Offert.h"
#include "../Headers/PPSaB.h"

using namespace sf;
using namespace std;

MainClass::MainClass()
{
	window_size_x = 3840;
	window_size_y = 2160;
	game_started = false;

	game_font.loadFromFile("Fonts/CelticHand.ttf");

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

Addidtionals::Addidtionals(MainClass& main)
{
	characterSize = 150;
	animation_speed = 1;
	animation_counter = 0;
	animation_stopper = 35;

	firstscreen_texture.loadFromFile("Textures/Firstscreen.png");
	firstscreen_texture.setSmooth(true);

	firstscreen.setTexture(firstscreen_texture);
	firstscreen.setTextureRect(IntRect(0, 0, 300, 300));
	firstscreen.setOrigin(150, 150);
	firstscreen.setPosition(0, 0);
	firstscreen.setScale(30, 30);
	firstscreen.setColor(Color(15, 15, 15));


	start_text.setFont(main.game_font);
	start_text.setCharacterSize(150);
	start_text.setOrigin(0, 0);
	start_text.setPosition(main.camera.getSize().x / 2 - 500, main.camera.getSize().y / 2 - 200);
	start_text.setString("Click to play");
	start_text.setFillColor(Color(255, 255, 255));
}
void Addidtionals::doAnimation()
{
	if (animation_counter < animation_stopper)
	{
		characterSize += animation_speed;
		start_text.setPosition(start_text.getPosition().x - animation_speed * 2, start_text.getPosition().y - animation_speed);
		animation_counter++;
		start_text.setCharacterSize(characterSize);
	}
	else if (animation_counter >= animation_stopper && animation_counter < animation_stopper * 2)
	{
		characterSize -= animation_speed;
		start_text.setPosition(start_text.getPosition().x + animation_speed * 2, start_text.getPosition().y + animation_speed);
		animation_counter++;
		start_text.setCharacterSize(characterSize);
	}

	if (animation_counter >= animation_stopper * 2)
	{
		animation_counter = 0;
	}
}
void Addidtionals::clickToPlay(MainClass& main)
{
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		main.game_started = true;
	}
}
void Addidtionals::display(Shop shop, MainClass& main)
{
	if (main.game_started == false)
	{
		doAnimation();
		main.window.draw(firstscreen);
		main.window.draw(start_text);
	}
	if (main.game_started == true)
	{
		moneey.setString(to_string(shop.getMoney()));
		main.window.draw(coin);
		main.window.draw(moneey);
	}
}

Map::Map()
{
	path_block_size = 175;
	paths_block_corner = 0;
	path_blocks_counter = 0;
	path_size = 0;
	path_axle_stop = 0;
	path_position_x = 0;
	path_position_y = 0;

	backgroundConfigure();
	wayConfigure();
	pathConfigure();
	pathCreate();
}
void Map::backgroundConfigure()
{
	background_texture.loadFromFile("Textures/Background.png");
	background_texture.setSmooth(true);

	background.setTexture(background_texture);
	background.setTextureRect(IntRect(0, 0, 960, 540));
	background.setScale(4, 4);
}
void Map::wayConfigure()
{
	main_positions[0] = (Vector2f(-250, 1080));
	main_positions[1] = (Vector2f(2750, -170));

	path_steps_counter.push_back(1050);
	path_direction.push_back('r');
	path_blocks_count.push_back(6);

	path_steps_counter.push_back(-700);
	path_direction.push_back('u');
	path_blocks_count.push_back(4);

	path_steps_counter.push_back(525);
	path_direction.push_back('r');
	path_blocks_count.push_back(3);

	path_steps_counter.push_back(1575);
	path_direction.push_back('d');
	path_blocks_count.push_back(9);

	path_steps_counter.push_back(700);
	path_direction.push_back('r');
	path_blocks_count.push_back(4);

	path_steps_counter.push_back(-1050);
	path_direction.push_back('u');
	path_blocks_count.push_back(6);

	path_steps_counter.push_back(525);
	path_direction.push_back('r');
	path_blocks_count.push_back(3);

	path_steps_counter.push_back(700);
	path_direction.push_back('d');
	path_blocks_count.push_back(4);

	path_steps_counter.push_back(700);
	path_direction.push_back('r');
	path_blocks_count.push_back(4);

	path_steps_counter.push_back(-875);
	path_direction.push_back('u');
	path_blocks_count.push_back(5);

	path_steps_counter.push_back(700);
	path_direction.push_back('r');
	path_blocks_count.push_back(4);

	path_position_x = main_positions[0].x;
	path_position_y = main_positions[0].y;

	pathBlocksMultiplier();
}
void Map::pathConfigure()
{
	Vector2f path_position = Vector2f(path_position_x, path_position_y);

	path_texture.loadFromFile("Textures/Path.png");
	path_texture.setSmooth(true);

	path.push_back(Sprite());
	path.back().setTexture(path_texture);
	path.back().setTextureRect(IntRect(0, 0, 250, 250));
	path.back().setOrigin(125, 125);
	path.back().setPosition(path_position);
	path.back().setScale(0.7, 0.7);
}
void Map::pathBlocksMultiplier()
{
	for (int i = 1; i <= path_steps_counter.size(); i++)
	{
		if (path_steps_counter[i - 1] >= 0)
			path_blocks_counter += path_steps_counter[i - 1] / path_block_size;
		else if (path_steps_counter[i - 1] < 0)
			path_blocks_counter += path_steps_counter[i - 1] * -1 / path_block_size;
	}
}
void Map::pathCreate()
{
	for (int i = 1; i <= path_blocks_counter; i++)
	{
		if (path_steps_counter[paths_block_corner] > 0)
		{
			if (path_direction[paths_block_corner] == 'r' && path_axle_stop < path_steps_counter[paths_block_corner]
				|| path_direction[paths_block_corner] == 'd' && path_axle_stop < path_steps_counter[paths_block_corner])
			{
				if (path_direction[paths_block_corner] == 'r')
				{
					path_position_x += path_block_size;
					pathConfigure();
					path_axle_stop += path_block_size;
				}
				else if (path_direction[paths_block_corner] == 'd')
				{
					path_position_y += path_block_size;
					pathConfigure();
					path_axle_stop += path_block_size;
				}
			}
			if (path_axle_stop >= path_steps_counter[paths_block_corner])
			{
				path_axle_stop = 0;
				paths_block_corner++;
			}
		}
		else if (path_steps_counter[paths_block_corner] < 0)
		{
			if (path_direction[paths_block_corner] == 'l' && path_axle_stop < path_steps_counter[paths_block_corner] * -1
				|| path_direction[paths_block_corner] == 'u' && path_axle_stop < path_steps_counter[paths_block_corner] * -1)
			{
				if (path_direction[paths_block_corner] == 'l')
				{
					path_position_x -= path_block_size;
					pathConfigure();
					path_axle_stop += path_block_size;
				}
				else if (path_direction[paths_block_corner] == 'u')
				{
					path_position_y -= path_block_size;
					pathConfigure();
					path_axle_stop += path_block_size;
				}
			}
			if (path_axle_stop >= path_steps_counter[paths_block_corner] * -1)
			{
				path_axle_stop = 0;
				paths_block_corner++;
			}
		}
	}
}
void Map::display(MainClass& main)
{
	main.window.draw(background);
	if (main.game_started == true)
	{
		for (int i = 1; i <= path.size(); i++)
		{
			main.window.draw(path[i - 1]);
		}
	}
}
int Map::getCountOfPathBlocks()
{
	return path.size() - 1;
}
char Map::getWhereIsGoingPath(int which)
{
	which--;

	int second_counter = 0;
	int special_counter = 0;

	for (int i = 1; i < path_blocks_count.size() + 1; i++)
	{
		second_counter += path_blocks_count[i - 1];
		special_counter++;
		if (which < second_counter)
		{
			i = path_blocks_count.size() + 1;
		}
	}

	if (path_direction[special_counter - 1] == 'r' || path_direction[special_counter - 1] == 'l')
		return 'x';
	if (path_direction[special_counter - 1] == 'u' || path_direction[special_counter - 1] == 'd')
		return 'y';
}
Vector2f Map::getPathBlocksPosition(int which)
{
	return path[which].getPosition();
}
Vector2f Map::getMainPosition(int i)
{
	return main_positions[i - 1];
}
vector <int> Map::getPathSteps()
{
	return getPathSteps();
}
vector <char> Map::getPathDirection()
{
	return getPathDirection();
}

Macler::Macler()
{
	macler_texture.loadFromFile("Textures/Macler.png");
	macler_texture.setSmooth(true);

	this->setTexture(macler_texture);
	this->setTextureRect(IntRect(1500, 300, 300, 300));
	this->setOrigin(150, 150);
	this->setPosition(0, 0);
	this->setScale(0, 0);
}
void Macler::press(Macler object)
{
	if (seted == true && can_do_animation == false)
	{
		button.use(object);

		if (button.mouseOn() == true)
		{
			this->setTextureRect(IntRect(1800, 300, 300, 300));
		}
		else
		{
			this->setTextureRect(IntRect(0, 0, 300, 300));
		}

		if (button.holding() == true)
		{
			this->setScale(0.7, 0.7);
		}
		if (button.released() == true && pressed == false)
		{
			this->setTextureRect(IntRect(0, 0, 300, 300));
			this->setScale(0.72, 0.72);
			pressed = true;
			can_do_animation = true;
		}
	}
}
void Macler::mouthAnimation()
{
	int stopper = 2;
	int which_macler = 300;

	if (seted == true)
	{
		if (can_do_animation == true)
		{
			if (counter_of_mouth_animation <= stopper)
			{
				this->setTextureRect(IntRect(which_macler, 0, 300, 300));
			}
			if (counter_of_mouth_animation > stopper&& counter_of_mouth_animation <= stopper * 2)
			{
				this->setTextureRect(IntRect(which_macler * 2, 0, 300, 300));
			}
			if (counter_of_mouth_animation > stopper * 2 && counter_of_mouth_animation <= stopper * 3)
			{
				this->setTextureRect(IntRect(which_macler * 3, 0, 300, 300));
			}
			if (counter_of_mouth_animation > stopper * 3 && counter_of_mouth_animation <= stopper * 4)
			{
				this->setTextureRect(IntRect(which_macler * 4, 0, 300, 300));
			}
			if (counter_of_mouth_animation > stopper * 4 && counter_of_mouth_animation <= stopper * 5)
			{
				this->setTextureRect(IntRect(which_macler * 5, 0, 300, 300));
			}
			if (counter_of_mouth_animation > stopper * 5 && counter_of_mouth_animation <= stopper * 6)
			{
				this->setTextureRect(IntRect(which_macler * 6, 0, 300, 300));
			}

			counter_of_mouth_animation++;
		}
		if (counter_of_mouth_animation >= stopper * 6 + 1)
		{
			counter_of_mouth_animation = 62;
		}
	}
}
void Macler::nowCanBeSetted()
{
	holding = true;
}
void Macler::setSomething(MainClass& object)
{
	button.setSomething(300, 300, object.window, object.camera);
}
void Macler::set(Map map, MainClass& object)
{
	if (seted == false)
	{
		float mouse_position_x = (float)Mouse::getPosition().x / object.window.getSize().x * object.camera.getSize().x;
		float mouse_position_y = (float)Mouse::getPosition().y / object.window.getSize().y * object.camera.getSize().y;

		Vector2f path_positions;

		bool path_on_x = false;
		bool can_be_setted = false;

		if (seted == false && holding == true)
		{
			this->setTextureRect(IntRect(1500, 300, 300, 300));
			this->setScale(0.8, 0.8);

			float upp_wall = 0;
			float downn_wall = 0;
			float leftt_wall = 0;
			float rightt_wall = 0;

			int smallest_stopper = 8;
			int smaller_stopper = 8;
			int bigger_stopper = 180;

			for (int i = 1; i < map.getCountOfPathBlocks(); i++)
			{
				path_positions = map.getPathBlocksPosition(i - 1);

				if (map.getWhereIsGoingPath(i) == 'x' && path_on_x == true)
				{
					upp_wall = path_positions.y - smaller_stopper;
					downn_wall = path_positions.y + smaller_stopper;
					leftt_wall = path_positions.x - bigger_stopper;
					rightt_wall = path_positions.x + bigger_stopper;
				}
				if (map.getWhereIsGoingPath(i) == 'y' && path_on_x == false)
				{
					upp_wall = path_positions.y - bigger_stopper;
					downn_wall = path_positions.y + bigger_stopper;
					leftt_wall = path_positions.x - smaller_stopper;
					rightt_wall = path_positions.x + smaller_stopper;
				}

				if (map.getWhereIsGoingPath(i) == 'x' && path_on_x == false)
				{
					upp_wall = path_positions.y - smallest_stopper;
					downn_wall = path_positions.y + smallest_stopper;
					leftt_wall = path_positions.x - smallest_stopper;
					rightt_wall = path_positions.x + smallest_stopper;

					path_on_x = true;
				}
				if (map.getWhereIsGoingPath(i) == 'y' && path_on_x == true)
				{
					upp_wall = path_positions.y - smallest_stopper;
					downn_wall = path_positions.y + smallest_stopper;
					leftt_wall = path_positions.x - smallest_stopper;
					rightt_wall = path_positions.x + smallest_stopper;

					path_on_x = false;
				}


				if (this->getPosition().y >= upp_wall && this->getPosition().y <= downn_wall &&
					this->getPosition().x >= leftt_wall && this->getPosition().x <= rightt_wall)
				{
					can_be_setted = true;
					this->setColor(Color(255, 255, 0));
					i = map.getCountOfPathBlocks() + 1;
				}

				else if (this->getPosition().y < upp_wall || this->getPosition().y > downn_wall ||
					this->getPosition().x < leftt_wall || this->getPosition().x > rightt_wall)
				{
					can_be_setted = false;
					this->setColor(Color(250, 250, 250));
				}
			}
		}
		if (button.holding() == false)
		{
			this->setPosition(mouse_position_x, mouse_position_y);
		}
		if (can_be_setted == true)
		{
			button.use();
			if (button.holding() == true)
			{
				this->setScale(0.73, 0.73);
			}
		}
		if (button.released() == true && seted == false && holding == true && can_be_setted == true)
		{
			seted = true;
			holding = false;
			this->setRotation(0);
			this->setTextureRect(IntRect(0, 0, 300, 300));
			this->setColor(Color(250, 250, 250));
			this->setScale(0.75, 0.75);
		}
	}
}
void Macler::work(Macler object)
{
	press(object);
	mouthAnimation();
}
void Macler::display(Macler to_draw, MainClass& object)
{
	object.window.draw(to_draw);
}
bool Macler::getMainBool()
{
	return holding;
}
Texture Macler::getHimTexture()
{
	return macler_texture;
}

Mactangle::Mactangle(Map map)
{
	mactangle_texture.loadFromFile("Textures/Mactangle.png");
	mactangle_texture.setSmooth(true);

	this->setTexture(mactangle_texture);
	this->setTextureRect(IntRect(0, 0, 250, 250));
	this->setOrigin(125, 125);
	this->setPosition(map.getMainPosition(1));
	this->setScale(0.6, 0.6);
}
void Mactangle::moving(Map map)
{
	mactangles_position_x = this->getPosition().x;
	mactangles_position_y = this->getPosition().y;

	vector <int> mactangles_steps_counter = map.getPathSteps();
	vector <char> mactangles_direction = map.getPathDirection();

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
}
void Mactangle::display(Mactangle to_draw, MainClass& main)
{
	main.window.draw(to_draw);
}

Offert::Offert(Sprite like_offert, Texture texturee, int offert_position_x, int offert_position_y, float sccale, MainClass& main)
{
	scale = sccale;
	position_x = offert_position_x;
	position_y = offert_position_y;

	starter_position_x = offert_position_x;
	starter_position_y = offert_position_y;

	offertConfigure(like_offert, texturee, scale);
	buttonConfigure(scale);
	coinConfigure(0.3);
	valueConfigure(50, main);
}
void Offert::offertConfigure(Sprite like_offert, Texture texturee, float scale)
{
	offeert_texture = texturee;
	offeert.setTexture(offeert_texture);
	offeert.setTextureRect(like_offert.getTextureRect());
	offeert.setOrigin(like_offert.getOrigin());
	offeert.setPosition(position_x, position_y);
	offeert.setScale(scale, scale);
}
void Offert::buttonConfigure(float scale)
{
	button_texture.loadFromFile("Textures/BuyButton.png");
	button_texture.setSmooth(true);

	button.setTexture(button_texture);
	button.setTextureRect(IntRect(0, 0, 300, 100));
	button.setOrigin(150, 50);
	button.setPosition(position_x, position_y);
	button.setScale(scale, scale);
}
void Offert::coinConfigure(float scale)
{
	coin_texture.loadFromFile("Textures/Coin.png");
	coin_texture.setRepeated(2);

	coin.setTexture(coin_texture);
	coin.setTextureRect(IntRect(0, 0, 200, 200));
	coin.setOrigin(100, 100);
	coin.setPosition(position_x, position_y);
	coin.setScale(scale, scale);
}
void Offert::valueConfigure(int money, MainClass& main)
{
	value.setOrigin(0, 0);
	value.setFillColor(Color(255, 227, 38));
	value.setPosition(position_x, position_y);
	value.setFont(main.game_font);
	value.setCharacterSize(50);
	value.setString(to_string(money));
	value.setOutlineColor(Color(255, 207, 38));
	value.setOutlineThickness(1);
	value.setLetterSpacing(1.3);
}

void Offert::go(Shop shop)
{
	if (shop.getCanOffertGo() == true)
	{
		offeert.setPosition(position_x -= 50, position_y);
		button.setPosition(position_x, position_y);
		coin.setPosition(position_x + 60, position_y + 90);
		value.setPosition(position_x - 60, position_y + 60);
	}
}
void Offert::ifHidden(Shop shop)
{
	if (shop.getVisible() == false)
	{
		position_x = starter_position_x;

		offeert.setPosition(position_x, position_y);
		button.setPosition(position_x, position_y);
		coin.setPosition(position_x, position_y);
		value.setPosition(position_x, position_y);
	}
}
void Offert::press(Shop shop)
{
	button_button.use(button);
	int money = shop.getMoney();

	if (button_button.mouseOn() == true)
	{
		button.setTextureRect(IntRect(300, 0, 300, 100));
	}
	else
	{
		button.setTextureRect(IntRect(0, 0, 300, 300));
	}

	if (button_button.holding() == true)
	{
		button.setScale(scale - 0.05, scale - 0.05);
		button.setTextureRect(IntRect(300, 0, 300, 100));
	}
	if (button_button.released() == true && money >= 50)
	{
		position_x = starter_position_x;
		shop.maclers.push_back(Macler());
		shop.maclers.back().nowCanBeSetted();
		shop.offertPressed();

		button.setScale(scale, scale);
		offeert.setPosition(position_x, position_y);
		button.setPosition(position_x, position_y);
		coin.setPosition(position_x, position_y);
		value.setPosition(position_x, position_y);
	}
}

void Offert::offertUseful(Shop shop)
{
	go(shop);
	ifHidden(shop);
	press(shop);
}
void Offert::setSomething(MainClass& main)
{
	button_button.setSomething(300, 100, main.window, main.camera);
}
void Offert::display(Shop shop, MainClass& main)
{
	if (shop.getVisible() == true)
	{
		main.window.draw(offeert);
		main.window.draw(button);
		main.window.draw(coin);
		main.window.draw(value);
	}
}

Shop::Shop(MainClass& main)
{
	money = 1000;
	sharp_stopper = 0;
	cart_stopper = 0;

	shop_visible = false;
	sharp_can_go = false;
	cart_can_go = false;
	sharp_pressed = false;
	cart_pressed = false;

	shop_size_x = 0.01;
	shop_size_y = 7.2;
	sharp_position_x = 3900;
	sharp_position_y = 100;
	cart_position_x = 3900;
	cart_position_y = 100;
	cart_scale = 1;
	sharp_scale = 0.75;

	shopConfigure(main);
	cartConfigure();
	sharpConfigure();
}
void Shop::shopConfigure(MainClass& main)
{
	shop_texture.loadFromFile("Textures/Shop.png");
	shop_texture.setSmooth(true);

	shop.setTexture(shop_texture);
	shop.setTextureRect(IntRect(0, 0, 300, 300));
	shop.setOrigin(300, 300);
	shop.setPosition(main.camera.getSize().x, main.camera.getSize().y);
	shop.setScale(0.0, shop_size_y);
}
void Shop::cartConfigure()
{
	cart_texture.loadFromFile("Textures/Cart.png");
	cart_texture.setSmooth(true);

	cart.setTexture(cart_texture);
	cart.setTextureRect(IntRect(0, 0, 150, 150));
	cart.setOrigin(75, 75);
	cart.setPosition(cart_position_x, cart_position_y);
	cart.setScale(cart_scale, cart_scale);
}
void Shop::sharpConfigure()
{
	sharp_texture.loadFromFile("Textures/Sharp.png");
	sharp_texture.setSmooth(true);

	sharp.setTexture(sharp_texture);
	sharp.setTextureRect(IntRect(0, 0, 150, 150));
	sharp.setOrigin(75, 75);
	sharp.setPosition(sharp_position_x, sharp_position_y);
	sharp.setScale(sharp_scale, sharp_scale);
}

void Shop::shopOpening()
{
	if (shop_visible == true)
	{
		if (sharp_pressed == true && shop.getScale().x < 0.001)
		{
			shopReset();
		}
		if (sharp_pressed == true)
		{
			shop.setScale(shop_size_x /= 1.2, shop_size_y);
		}
		if (cart_pressed == true && shop_size_x <= 3)
		{
			shop.setScale(shop_size_x *= 1.2, shop_size_y);
		}
	}

	if (cart_pressed == true && shop_visible == false)
	{
		shop.setScale(0.01, shop_size_y);
		shop_visible = true;
	}
	if (shop_size_x > 3)
	{
		sharp_can_go = true;
	}
	if (sharp_can_go == true && sharp_stopper <= 14)
	{
		sharp.setPosition(sharp_position_x -= 10, sharp_position_y);
		sharp_stopper++;
	}

	if (shop_size_x < 3)
	{
		cart_can_go = true;
	}
	if (cart_can_go == true && cart_stopper <= 7)
	{
		cart.setPosition(cart_position_x -= 20, sharp_position_y);
		cart_stopper++;
	}
}
void Shop::shopReset()
{
	shop.setScale(0.0, shop_size_y);
	shop_visible = false;

	sharp_position_x = 3900;
	sharp_pressed = false;
	sharp_can_go = false;
	sharp_stopper = 0;
	sharp.setPosition(sharp_position_x, sharp_position_y);

	cart_position_x = 3900;
	cart_pressed = false;
	cart_can_go = false;
	cart_stopper = 0;
	cart.setPosition(cart_position_x, cart_position_y);
}
void Shop::cartPress()
{
	if (cart_pressed == false && sharp_pressed == false)
	{
		cart_button.use(cart);

		if (cart_button.mouseOn() == true)
		{
			cart.setTextureRect(IntRect(150, 0, 150, 150));
		}
		else
		{
			cart.setTextureRect(IntRect(0, 0, 150, 150));
		}

		if (cart_button.holding() == true)
		{
			cart.setScale(cart_scale - 0.05, cart_scale - 0.05);
			cart.setTextureRect(IntRect(150, 0, 150, 150));
		}
		if (cart_button.released() == true)
		{
			cart.setTextureRect(IntRect(150, 0, 150, 150));
			cart.setScale(cart_scale, cart_scale);
			cart_pressed = true;
			sharp_pressed = false;
		}
	}
}
void Shop::sharpPress()
{
	if (cart_pressed == true && sharp_pressed == false)
	{
		sharp_button.use(sharp);

		if (sharp_button.mouseOn() == true)
		{
			sharp.setTextureRect(IntRect(150, 0, 150, 150));
		}
		else
		{
			sharp.setTextureRect(IntRect(0, 0, 150, 150));
		}

		if (sharp_button.holding() == true)
		{
			sharp.setScale(sharp_scale - 0.05, sharp_scale - 0.05);
			sharp.setTextureRect(IntRect(150, 0, 150, 150));
		}
		if (sharp_button.released() == true)
		{
			sharp.setTextureRect(IntRect(150, 0, 150, 150));
			sharp.setScale(sharp_scale, sharp_scale);
			cart_pressed = false;
			sharp_pressed = true;
		}
	}
}

void Shop::setSomething(MainClass& main)
{
	cart_button.setSomething(300, 300, main.window, main.camera);
	sharp_button.setSomething(150, 150, main.window, main.camera);
}
void Shop::offertPressed()
{
	sharp_pressed = true;
	cart_pressed = false;
	cart_can_go = false;
	money -= 50;
}
bool Shop::getVisible()
{
	if (cart_pressed == true && sharp_pressed == false && shop_visible == true)
		return true;
	else
		return false;
}
bool Shop::getCanOffertGo()
{
	if (sharp_can_go == true && sharp_stopper <= 14)
		return true;
	else
		return false;
}
int Shop::getMoney()
{
	return money;
}

void Shop::working()
{
	shopOpening();
	cartPress();
	sharpPress();
}
void Shop::display(MainClass& main)
{
	main.window.draw(shop);
	if (cart_pressed == false && shop_visible == false)
	{
		main.window.draw(cart);
	}
	else if (cart_pressed == true && sharp_pressed == false && shop_visible == true)
	{
		main.window.draw(sharp);
	}
}