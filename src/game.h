// This file is part of Mactangle.
// Mactangle is free software distributed under Mozilla Public License Version 2.0.
// You should have received a copy of the Mozilla Public License 
// along with Mactangle. If not, see <https://www.mozilla.org/en-US/MPL/2.0/>.

#pragma once

#include <SFML/Graphics.hpp>

/// <summary>
/// SFML RenderWindow but with Font, View and some methods that will be used to play game.
/// </summary>
class Game : public sf::RenderWindow
{
public:
	/// <summary>
	/// It's constructor.
	/// </summary>
	Game(sf::VideoMode videoMode = sf::VideoMode().getDesktopMode(), sf::String windowName = "Mactangle", sf::String fontPath = CUBICCOREMONO_TTF, unsigned int health = 3);

	/// <summary>
	/// It's destructor.
	/// </summary>
	~Game();

private:

	/// <summary>
	/// SFML view.
	/// </summary>
	sf::View m_camera;

	/// <summary>
	/// SFML font.
	/// </summary>
	sf::Font m_font;

	/// <summary>
	/// Number of hearts.
	/// </summary>
	unsigned int m_health;
};