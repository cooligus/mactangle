#include <iostream>
#include "TextureContainer.h"


int main()
{
	// */* TESTING SPACE */*

	TextureContainer textureContainer;

	textureContainer.addPath(DACLER_PNG);

        
	// *\* END OF TESTING SPACE *\*
    

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(200, 50), "SFML window");
    // Load a sprite to display

    sf::Texture textt = textureContainer.getTexture();

    //textureContainer.setTexture(textt);
    textt.loadFromFile(MACTANGLE_PNG);

    textureContainer.fitToVector(sf::Vector2u(200, 50));
    sf::Sprite sprite = textureContainer.getSprite();

    std::cout << sprite.getTexture()->getSize().x;
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        // Update the window
        window.display();
    }

	return 0;
}