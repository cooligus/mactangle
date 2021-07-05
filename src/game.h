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