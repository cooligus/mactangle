#include <SFML/Graphics.hpp>
#include "mainclasses.h"


MainClass::MainClass()
	:m_windowSizeX(3840.f), m_windowSizeY(2160.f), m_gameRuning(false), m_camera(), m_window(sf::VideoMode().getDesktopMode(), "Mactangle", sf::Style::Fullscreen), m_font()
{
	m_font.loadFromFile("../fonts/CubicCoreMono.ttf");

	m_window.setVisible(true);
	m_window.setVerticalSyncEnabled(true);
	m_window.setKeyRepeatEnabled(false);
	m_window.setMouseCursorGrabbed(true);
	m_window.setActive(true);
	m_window.setPosition(sf::Vector2i(0, 0));
	
	m_camera.setSize(m_windowSizeX, m_windowSizeY);
	m_camera.setCenter(m_windowSizeX / 2, m_windowSizeY / 2);
	m_camera.setViewport(sf::FloatRect(0, 0, 1, 1));
	
	float base_mouse_position_x = m_window.getSize().x / 2;
	float base_mouse_position_y = m_window.getSize().y / 2;
	sf::Mouse::setPosition(sf::Vector2i((int)base_mouse_position_x, (int)base_mouse_position_y));
	
	m_window.setView(m_camera);
}