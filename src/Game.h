#include <SFML/Graphics.hpp>

class Game
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
	/// SFML window.
	/// </summary>
	sf::RenderWindow m_window;

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