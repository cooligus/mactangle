#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "MainClasses.h"

using namespace sf;
using namespace std;

class Map
{
	Sprite background;
	Texture background_texture;
	Texture path_texture;
	Vector2f main_positions[2];
	vector <Sprite> path;

	int path_block_size = 175;
	int paths_block_corner = 0;
	int path_blocks_counter;
	int path_size;
	int path_axle_stop = 0;
	int path_position_x;
	int path_position_y;


	void backgroundConfigure();
	void wayConfigure();
	void pathConfigure();
	void pathBlocksMultiplier();
	void pathCreate();

public:
	vector <int> path_blocks_count;
	vector <int> path_steps_counter;
	vector <char> path_direction;

	Map();
	Vector2f getPathBlocksPosition(int which);
	Vector2f getMainPosition(int i);
	int getCountOfPathBlocks();
	char getWhereIsGoingPath(int which);
	void display(MainClass& main);
};

