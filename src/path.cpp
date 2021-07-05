#include "path.h"
#include <iostream>

using json = nlohmann::json;

//define first contructor
Path::Path(std::vector<sf::Vector2f> path, float thickness)
	:m_elements(path), m_thickness(thickness)
{
}

//define second contructor
Path::Path(std::string path)
	: m_elements(), m_thickness(1)
{
	//load path
	loadPath(path);
}

//define third contructor
Path::Path()
	:m_elements(), m_thickness(1)
{
}

//define desctructor
Path::~Path()
{
}


//define first getter
sf::Vector2f Path::getElement(unsigned index)
{
	//return element
	return m_elements[index];
}

//define second getter
std::vector<sf::Vector2f> Path::getAll()
{
	//return path
	return m_elements;
}

bool Path::isOnPath(sf::Sprite object, bool all)
{
	return false;
}

bool Path::moveOnPath(sf::Sprite object, float speed)
{
	return false;
}

bool Path::loadPath(std::string path)
{
	//new in-file stream
	std::ifstream file(path, std::ifstream::in);

	//check is file good
	if (!file.good())
	{
		//check is file good adding extension
		file = std::ifstream(path + ".json", std::ifstream::in);

		//if file isn't good throw error and end constructor's work
		if (!file.good())
		{
			//close stream
			file.close();

			//throw error
			throw std::exception("Can't open .json file!");

			//end work
			return json();
		}
	}

	m_data = json::parse(file)["path"];

	//close file
	file.close();

	//vector with path's points
	m_elements = std::vector<sf::Vector2f>();

	//setup vector if m_data is not null
	if (!m_data[PATH_OBJ_NAME].is_null())
	{
		//make new json object with path
		json path = m_data[PATH_OBJ_NAME];

		//get all elements of path if size of path object doesn't equal to 0
		for (int i = 0; i < path.size(); i++)
		{
			//actual point name
			std::string name = POINT_OBJ_NAME + std::to_string(i);

			//push to pathPoints next point
			m_elements.push_back(sf::Vector2f(path[name][POINT_POSITION_X_NAME], path[name][POINT_POSITION_Y_NAME]));

			//display points (uncomment it before)
			std::cout << "x: " << m_elements[i].x << " y: " << m_elements[i].y << std::endl;
		}

		//return success
		return true;
	}
	//return failure
	return false;
}
