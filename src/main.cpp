#include <iostream>
#include "TextureContainer.h"
#include "Game.h"
#include "Path.h"

int main()
{
	TextureContainer textureContainer;

	textureContainer.addPath(BACKGROUND_PNG);
    Path path;
    
    // Create the main window
    Game game;

    textureContainer.fitToVector(game.getSize());
    sf::Sprite sprite = textureContainer.getSprite();
    
    // Start the game loop
    while (game.isOpen())
    {
        // Process events
        sf::Event event;
        while (game.pollEvent(event))
        {
            // Close window: exit
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                game.close();

            // Close window: exit
            if (event.type == sf::Event::Closed)
                game.close();
        }

        // Clear screen
        game.clear();

        // Draw the sprite
        game.draw(sprite);

        // Update the window
        game.display();
    }

	return 0;
}