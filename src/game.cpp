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

#include "game.h"

//define contructor
Game::Game(sf::VideoMode videoMode, sf::String windowName, sf::String fontPath, unsigned int health)
	:RenderWindow(videoMode, windowName, sf::Style::Fullscreen), m_font(), m_health(3)
{
	//load font using prepared by cmake variable with font's position
	if(!m_font.loadFromFile(CUBICCOREMONO_TTF))
		throw std::exception("Can't load font!");

	//set camera's stuffs
	m_camera.setSize(videoMode.width, videoMode.height);
	m_camera.setCenter(videoMode.width / 2, videoMode.height / 2);
	m_camera.setViewport(sf::FloatRect(0, 0, 1, 1));

	//set window's properties
	setVisible(true);
	setVerticalSyncEnabled(true);
	setKeyRepeatEnabled(false);
	setMouseCursorGrabbed(false);
	setActive(true);
	setView(m_camera);
}

//define desctructor
Game::~Game()
{
}