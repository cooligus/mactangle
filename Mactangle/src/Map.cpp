#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "MainClasses.h"
#include "Map.h"

using namespace sf;
using namespace std;

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
	main_positions[1] = (Vector2f(3950, 730));

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
	if (main.game_runing == true)
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
/*
vector <int> Map::getPathSteps()
{
	return getPathSteps();
}
vector <char> Map::getPathDirection()
{
	return getPathDirection();
}*/
