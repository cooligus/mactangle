// This file is part of Mactangle.
// 
// Mactangle is free software : you can redistribute it and /or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Mactangle is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Mactangle. If not, see < https://www.gnu.org/licenses/>.

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