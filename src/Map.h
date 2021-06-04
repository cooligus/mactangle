#include "path.h"
#include <SFML/Graphics.hpp>

/// <summary>
/// Store path, map texture and control it. 
/// </summary>
class Map
{
public:

	/// <summary>
	/// First constructor.
	/// </summary>
	/// <param name="pathPath"></param>
	/// <param name="texturePath"></param>
	Map(std::string pathPath, std::string texturePath);

	/// <summary>
	/// Second constructor.
	/// </summary>
	/// <param name="path"></param>
	/// <param name="texture"></param>
	Map(Path path, sf::Texture texture);

	/// <summary>
	/// Tertiary constructor. 
	/// </summary>
	Map();

	/// <summary>
	/// Destructor
	/// </summary>
	~Map();

private:
	/// <summary>
	/// mactangles’ path
	/// </summary>
	Path m_path;

	/// <summary>
	/// path look and design
	/// </summary>
	sf::Texture m_texture;
};