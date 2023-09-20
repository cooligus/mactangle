//
// Created by pewie on 19.09.2023.
//

#ifndef MACTANGLE_MAP_H
#define MACTANGLE_MAP_H

#include "../BaseClasses/Entity.h"

class Map : public Entity {
    sf::Texture background_texture;
    sf::Texture path_texture;
    sf::Vector2f main_positions[2];
    std::vector<sf::Sprite> path;

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
    std::vector<int> path_blocks_count;
    std::vector<int> path_steps_counter;
    std::vector<char> path_direction;

    Map();

    sf::Vector2f getPathBlocksPosition(int which);

    sf::Vector2f getMainPosition(int i);

    int getCountOfPathBlocks();

    char getWhereIsGoingPath(int which);

    void display();
};


#endif //MACTANGLE_MAP_H
