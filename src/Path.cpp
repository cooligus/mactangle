#include <fstream>
#include "Path.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <ctype.h>

using json = nlohmann::json;

//define first contructor
Path::Path(std::vector<sf::Vector2f> path)
	:m_elements(path)
{
}

//define second contructor
Path::Path(std::string path)
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
			return;
		}
	}

	//vector with path's points
	std::vector<sf::Vector2f> pathPoints;
		
	//parse json file
	json pathObject = json::parse(file)["path"];

	for (auto i = 0; i < pathObject.size(); i++)
	{
		//actual point name
		std::string name = "point-" + std::to_string(i);

		//push to pathPoints next point
		pathPoints.push_back(sf::Vector2f(pathObject[name]["x"], pathObject[name]["y"]));

		//display points (uncomment it before)
		//std::cout << "x: " << pathPoints[i].x << " y: " << pathPoints[i].y << std::endl;
	}

	//close file
	file.close();
}

//define tertiary contructor
Path::Path()
	:m_elements()
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