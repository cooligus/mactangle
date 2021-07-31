// This file is part of Mactangle.
// Mactangle is free software distributed under Mozilla Public License Version 2.0.
// You should have received a copy of the Mozilla Public License 
// along with Mactangle. If not, see <https://www.mozilla.org/en-US/MPL/2.0/>.

#include <iostream>
#include "Map.h"
#include "Game.h"
#include "Path.h"
#include <simpleCollision.h>

int main()
{
	Map textureContainer; 

	textureContainer.addPath(BACKGROUND_PNG);
    Path path;
    
    // Create the main window
    Game game;

    textureContainer.fitToVector(game.getSize());
    sf::Sprite sprite = textureContainer.getSprite();
    
    sf::CircleShape circle;
    circle.setPosition(0, 0);
    circle.setFillColor(sf::Color(200, 200, 200));
    circle.setScale(2.2, 2.2);
    circle.setRadius(500);

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

        // Draw the sprite
        game.draw(circle);

        // Update the window
        game.display();
    }

	return 0;
}