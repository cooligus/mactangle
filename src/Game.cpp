#include "game.h"

//define contructor
Game::Game(sf::VideoMode videoMode, sf::String windowName, sf::String fontPath, unsigned int health)
	:m_window(videoMode, windowName, sf::Style::Fullscreen), m_font(), m_health(3)
{
	//load font using prepared by cmake variable with font's position
	if(!m_font.loadFromFile(CUBICCOREMONO_TTF))
		throw std::exception("Can't load font!");

	//set camera's stuffs
	m_camera.setSize(videoMode.width, videoMode.height);
	m_camera.setCenter(videoMode.width / 2, videoMode.height / 2);
	m_camera.setViewport(sf::FloatRect(0, 0, 1, 1));

	//set window's properties
	m_window.setVisible(true);
	m_window.setVerticalSyncEnabled(true);
	m_window.setKeyRepeatEnabled(false);
	m_window.setMouseCursorGrabbed(false);
	m_window.setActive(true);
	m_window.setView(m_camera);
}

//define desctructor
Game::~Game()
{
}