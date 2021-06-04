#include <vector>
#include <SFML/System.hpp>

/// <summary>
/// Store all points of path and give element of that path or give all path. Path is getting from .json file or from special vector.
/// </summary>
class Path
{
public:
	/// <summary>
	/// First constructor.
	/// </summary>
	/// <param name="path">- All elements of path. First is start point and last is finish point.</param>
	Path(std::vector<sf::Vector2f> path);

	/// <summary>
	/// Second constructor.
	/// </summary>
	/// <param name="path">- Path to file path that ends with name of file (it's extension have to .json).</param>
	Path(std::string path);

	/// <summary>
	/// Tertiary constructor.
	/// </summary>
	Path();

	/// <summary>
	/// Destructor.
	/// </summary>
	~Path();

	/// <summary>
	/// Get one point of all path, where index is information with element u will get.
	/// </summary>
	/// <param name="index">- Index of path's element. It should be like in normal array.</param>
	/// <returns>Element that you will choose.</returns>
	sf::Vector2f getElement(unsigned index);

	/// <summary>
	/// Get all path's points.
	/// </summary>
	/// <returns>All path's elements.</returns>
	std::vector<sf::Vector2f> getAll();

private:
	/// <summary>
	/// All elements of path. First is start point and last is finish point.
	/// </summary>
	std::vector<sf::Vector2f> m_elements;
};