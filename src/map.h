//This file is part of Mactangle.
//
//Mactangle is free software : you can redistribute it and /or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//Mactangle is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with Mactangle. If not, see < https://www.gnu.org/licenses/>.

#pragma once

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