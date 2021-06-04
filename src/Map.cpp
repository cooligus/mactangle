#include "map.h"

Map::Map(std::string pathPath, std::string texturePath)
	:m_path(pathPath), m_texture()
{
	m_texture.loadFromFile(texturePath);
}

Map::Map(Path path, sf::Texture texture)
	: m_path(path), m_texture(texture)
{
}
