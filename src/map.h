#include "Path.h"
#include "TextureContainer.h"
#include <SFML/Graphics.hpp>

/// <summary>
/// Store path, map data, textures and control all of it. 
/// </summary>
class Map : public TextureContainer, Path
{
public:

	/// <summary>
	/// First constructor.
	/// </summary>
	/// <param name="dataPath"></param>
	/// <param name="texturePath"></param>
	Map(std::string dataPath, std::string texturePath);

	/// <summary>
	/// Second constructor. 
	/// </summary>
	Map();

	/// <summary>
	/// Destructor.
	/// </summary>
	~Map();


private:

	/// <summary>
	/// mactangles’ path
	/// </summary>
	Path m_path;
};