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
#include <iostream>

/// <summary>
/// Container that stores one or more textures and one sprite. It's mainly for Map class use because it has been designed to store map in some resolutions and to fit actual mained to window.
/// </summary>
class Map
{
public:
	/// <summary>
	/// Worst type of constuctor for this class because than you forget to push texture to it then some methods will not work.
	/// </summary>
	Map();

	/// <summary>
	/// Type of constuctor where you will have only one texture there.
	/// </summary>
	Map(std::string path);

	/// <summary>
	/// Type of constuctor where you will have some textures there.
	/// </summary>
	Map(std::vector<std::string> paths);

	/// <summary>
	/// Without being does nothing.
	/// </summary>
	~Map();


	/// <summary>
	/// Set one path with texture. Best way is to do that using cmake-generated definitions.
	/// </summary>
	/// <param name="path">- Path to texture.</param>
	/// <param name="index">- "Place" where path to texture have to be.</param>
	/// <param name="withLoad">- Load texture from file and push it into sf::Texture class if true or not if false.</param>
	/// <returns>Does operation succeeded or not.</returns>
	bool addPath(std::string path, int index = -1, bool withLoad = true);

	/// <summary>
	/// Change old vector with all paths with textures to new included in vector.
	/// </summary>
	/// <param name="paths">- Paths to textures.</param>
	/// <param name="newIndex">- New index.</param>
	/// <param name="withLoad">- Load texture from file and push it into sf::Texture class if true or not if false.</param>
	/// <returns>Does operation succeeded or not</returns>
	bool setPaths(std::vector<std::string> paths, int newIndex = -1, bool withLoad = true);

	/// <summary>
	/// Get vector with paths to textures.
	/// </summary>
	/// <returns>Vector with paths to textures</returns>
	std::vector<std::string> getPaths();


	/// <summary>
	/// Set actual index smaller by 1.
	/// </summary>
	/// <param name="withLoad">- Load texture from file and push it into sf::Texture class if true or not if false.</param>
	/// <returns>True if operation succeeded or false if not.</returns>
	bool setSmaller(bool withLoad = true);

	/// <summary>
	/// Set actual index bigger by 1.
	/// </summary>
	/// <param name="withLoad">- Load texture from file and push it into sf::Texture class if true or not if false.</param>
	/// <returns>True if operation succeeded or false if not.</returns>
	bool setBigger(bool withLoad = true);

	/// <summary>
	/// Set new actual index.
	/// </summary>
	/// <param name="index">- New index of path to texture.</param>
	/// <param name="withLoad">- Load texture from file and push it into sf::Texture class if true or not if false.</param>
	/// <returns></returns>
	bool setIndex(unsigned int index, bool withLoad = true);

	/// <summary>
	/// Get actual index.
	/// </summary>
	/// <returns>Actual index.</returns>
	unsigned int getIndex();


	/// <summary>
	/// Load texture from file using actual index.
	/// </summary>
	/// <param name="withSpriteSetting">- Set new texture to sprite if true or not if false.</param>
	/// <returns>Does loading from file succeeded.</returns>
	bool loadTexture(bool withSpriteSetting = true);

	/// <summary>
	/// Get texture object.
	/// </summary>
	/// <returns>Texture object.</returns>
	sf::Texture getTexture();


	/// <summary>
	/// Set texture to sprite.
	/// </summary>
	/// <param name="withCenter">- Set new centered position of sprite if true or not if false.</param>
	void loadSprite(bool withCenter = true);

	/// <summary>
	/// Get sprite object.
	/// </summary>
	/// <returns>Sprite object.</returns>
	sf::Sprite getSprite();

	/// <summary>
	/// Fit sprite scale to sf::Vector2u which should be size of window.
	/// </summary>
	/// <param name="toFit">- Size of window.</param>
	/// <param name="withSet">- Set new centered position of sprite if true or not if false.</param>
	/// <returns>Scale of sprite. If it's -1 operation didn't success.</returns>
	sf::Vector2f fitToVector(sf::Vector2u toFit, bool withSet = true);

	/// <summary>
	/// Set new centered position of sprite on window.
	/// </summary>
	/// <returns>Does width and height of window is bigger than 0.</returns>
	bool centerSprite();
	
private:

	/// <summary>
	/// Check does path really leads to file and does loading from it succeeded.
	/// </summary>
	/// <param name="path">- Path to check.</param>
	/// <returns>Does path is good.</returns>
	bool checkTexturePath(std::string path);

	/// <summary>
	/// Check does paths really leads to files and does loading from them succeeded.
	/// </summary>
	/// <param name="paths">- Paths to check.</param>
	/// <returns>Does paths are good.</returns>
	bool checkTexturesPath(std::vector<std::string> paths);

	/// <summary>
	/// Index of texture that is now used as main.
	/// </summary>
	unsigned int m_currentIndex;

	/// <summary>
	/// All paths to textures.
	/// </summary>
	std::vector<std::string> m_paths;

	/// <summary>
	/// Size of window. You can set it in fitToVector() functon.
	/// </summary>
	sf::Vector2u m_windowSize;

	/// <summary>
	/// Object with texture got from path.
	/// </summary>
	sf::Texture m_texture;

	/// <summary>
	/// Sprite with texture.
	/// </summary>
	sf::Sprite m_sprite;
};