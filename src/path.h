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
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <Module.hpp>

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
	/// <param name="thickness">- Thickness of path.</param>
	Path(std::vector<sf::Vector2f> path, float thickness = 1);

	/// <summary>
	/// Second constructor.
	/// </summary>
	/// <param name="path">- Path to file path that ends with name of file (it's extension have to .json).</param>
	Path(std::string path);

	/// <summary>
	/// Third constructor.
	/// </summary>
	Path();

	/// <summary>
	/// Destructor.
	/// </summary>
	~Path();

	/// <summary>
	/// Load path from file.
	/// </summary>
	/// <param name="path">path to file.</param>
	/// <returns>Whether operation succeeded.</returns>
	bool loadPath(std::string path);

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

	/// <summary>
	/// Get know is object on path.
	/// </summary>
	/// <param name="object">- Object you want to check.</param>
	/// <param name="all">- Is all object on path (if true all object must be on path, if false only part of object must be on path to return true).</param>
	/// <returns>True if it is on path or false if not.</returns>
	bool isOnPath(sf::Sprite object, bool all = false);

	/// <summary>
	/// Move object on path by speed.
	/// </summary>
	/// <param name="object">- Object you want to check</param>
	/// <param name="speed">- Distance from start position to end position (after use method).</param>
	/// <returns>Is object on path at all.</returns>
	bool moveOnPath(sf::Sprite object, float speed);

private:


	/// <summary>
	/// Hitbox of path. Class use it to check whether is something on path.
	/// </summary>
	HitboxBuilder::Hitbox m_hitbox;

	/// <summary>
	/// JSON object with path and rest of data.
	/// </summary>
	nlohmann::json m_data;

	/// <summary>
	/// All elements of path. First is start point and last is finish point.
	/// </summary>
	std::vector<sf::Vector2f> m_elements;

	/// <summary>
	/// Thickness of path.
	/// </summary>
	float m_thickness;
};