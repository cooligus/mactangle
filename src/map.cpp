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

#include "Map.h"

//first type of construtor
Map::Map()
	:m_currentIndex(0), m_paths(), m_texture(), m_sprite(), m_windowSize()
{
}

//second type of construtor
Map::Map(std::string path)
	:m_currentIndex(0), m_paths(), m_texture(), m_sprite(), m_windowSize()
{
	//Add first path to object
	addPath(path);
}

//third type of construtor
Map::Map(std::vector<std::string> paths)
	:m_currentIndex(0), m_paths(), m_texture(), m_sprite(), m_windowSize()
{	
	//Add first paths to object
	setPaths(paths);
}

//destructor
Map::~Map()
{
}

//m_texture getter
sf::Texture Map::getTexture()
{
	//return actual texture
	return m_texture;
}

//method that will fit sprite to window
sf::Vector2f Map::fitToVector(sf::Vector2u toFit, bool withSet)
{
	//set texutre sizes into variable
	sf::Vector2u size = m_texture.getSize();

	//set minus float variable
	float scale = -1;

	//fit sprite if there is a texture in object, and width and height of it is bigger than 0 
	if (!m_paths.size() == 0 || size.x > 0 && size.y > 0)
	{
		//count scales if X size of texture doesn't equal to widow X size or situation is the same on Y axis or both
		if (size.x != toFit.x || size.y != toFit.y)
		{
			float scaleX = static_cast<float>(toFit.x) / size.x;
			float scaleY = static_cast<float>(toFit.y) / size.y;

			if (scaleX > scaleY)
				scale = scaleX;
			else
				scale = scaleY;
		}

		//set new scale if user want it
		m_sprite.setScale(scale, scale);

		//set window size which should toFit variable contain
		m_windowSize = toFit;

		//center sprite
		if (withSet)
			centerSprite();
	}

	//return actual scale
	return sf::Vector2f(scale, scale);
}

//m_sprite getter
sf::Sprite Map::getSprite()
{
	//return actual sprite
	return m_sprite;
}

//center sprite in window method
bool Map::centerSprite()
{
	//center sprite if size of window doesn't equal to 0
	if (m_windowSize.x != 0 && m_windowSize.y != 0)
	{
		//put size of texture into variable
		sf::Vector2u textureSize = m_texture.getSize();

		//put scale of sprite into variable
		sf::Vector2f spriteScale = m_sprite.getScale();

		
		//multiply width of texture by scale X
		textureSize.x *= static_cast<float>(spriteScale.x);

		//multiply height of texture by scale Y
		textureSize.y *= static_cast<float>(spriteScale.y);


		//define variable with position of sprite
		sf::Vector2f spritePos;

		//count new positon on X if width of texture and window doesn't equal
		if (textureSize.x != m_windowSize.x)
			spritePos.x = (m_windowSize.x - static_cast<float>(textureSize.x)) / 2;

		//count new positon on Y if height of texture and window doesn't equal
		if (textureSize.y != m_windowSize.y)
			spritePos.y = (m_windowSize.y - static_cast<float>(textureSize.y)) / 2;

		//set new position of sprite
		m_sprite.setPosition(spritePos);

		//return success
		return true;
	}
	//return failure
	return false;
}

//add new path with texture method
bool Map::addPath(std::string path, int index, bool withLoad)
{
	//push new path if it's good
	if (checkTexturePath(path))
	{
		//push path back if index is minus or is bigger than size-1
		if (index < 0 || index >= m_paths.size())
			m_paths.push_back(path);
		
		//else put it into place defined by index
		else
			m_paths.insert(m_paths.begin() + index, path);
		
		//set new index
		setIndex(index);
		
		//load texture to texture (logic) if user want it
		if (withLoad)
			m_texture.loadFromFile(path);
		
		//return success
		return true;
	}
	//else return failure
	else
		return false;
	
}

//set new paths method
bool Map::setPaths(std::vector<std::string> paths, int newIndex, bool withLoad)
{
	//replace paths if paths in new vector are good
	if(checkTexturesPath(paths))
	{
		//replace vectors
		m_paths = paths;
	
		//set new index if actual is bigger than size or user want it
		setIndex(newIndex);

		//load texture if user want it
		if (withLoad)
			loadTexture();

		//return success
		return true;
	}
	//return failru
	return false;
}

//texture load method
bool Map::loadTexture(bool withSpriteSetting)
{
	//variable with success or failure
	bool toReturn = m_texture.loadFromFile(m_paths[m_currentIndex]);

	//set new texture to sprite if user want it
	if (withSpriteSetting)
		m_sprite.setTexture(m_texture);

	//return success or failure
	return toReturn;
}

//set bigger index method
bool Map::setBigger(bool withLoad)
{
	//set bigger index
	if (m_currentIndex < m_paths.size()-1)
	{
		//incrase index
		m_currentIndex++;
		
		//load new texture if user want it
		if (withLoad)
			loadTexture();
		
		//return success
		return true;
	}
	//return failure
	return false;
}

//set smaller index method
bool Map::setSmaller(bool withLoad)
{
	//return failure if index equals 0
	if (m_currentIndex == 0)
		return false;

	//decrement index
	m_currentIndex--;

	//load new texture if user want it
	if (withLoad)
		loadTexture();

	//return success
	return true;
}

//set new index method
bool Map::setIndex(unsigned int index, bool withLoad)
{
	//define new variable
	bool toReturn = false;

	//set new index if actual doesn't equal to new
	if (index != m_currentIndex)
	{
		if (index < 1)
			m_currentIndex = 0;

		else if (index < m_paths.size() - 1)
			m_currentIndex = index;

		else
			m_currentIndex = m_paths.size() - 1;

		//set return to success
		toReturn = true;
	}

	//load new texture if user want it
	if (withLoad)
		loadTexture();
	
	//return success or failure
	return toReturn;
}

//actual index getter
unsigned int Map::getIndex()
{
	//return actual index
	return m_currentIndex;
}

//vector with paths getter
std::vector<std::string> Map::getPaths()
{
	//return vector with paths
	return m_paths;
}

//load texture to sprite method
void Map::loadSprite(bool withCenter)
{
	//set new texture
	m_sprite.setTexture(m_texture);

	//center sprite if user want it
	if (withCenter)
		centerSprite();
}

//check path to texture method
bool Map::checkTexturePath(std::string path)
{
	//create temporary variable
	sf::Texture temp;

	//return load check
	return temp.loadFromFile(path);
}

//check paths to textures method
bool Map::checkTexturesPath(std::vector<std::string> paths)
{
	//create temporary variable
	sf::Texture temp;

	//define boolean that will tell is vector good or not
	bool isGood = true;

	//check all elements of vector
	for (int i = 0; i < paths.size(); i++)
	{
		//if actual path is bad break loop and set boolean to false
		if (!temp.loadFromFile(paths[i]))
		{
			isGood = false;
			break;
		}
	}

	//return success or failure
	return isGood;
}
