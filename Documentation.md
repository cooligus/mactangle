# Mactangle

# Main

Run all game

----------
# Game

Condense all stuffs in one class.


## Functions
- NOT YET void playGame() - run everything and when while() in that will end game will stop.
## Variables
- sf::RenderWindow m_window - display all game
- sf::View m_camera - specify field of view 
- sf::Font m_font - specify look of texts (it’s font)
- unsigned int m_health - specify how many lifes player has
----------
# Path

Store all points of path and give element of that path or give all path. Path is getting from .json file or from std::vector<sf::Vector2f>.


## Functions
- sf::Vector2f getElement(unsigned index) - get one point of all path, where index is information with element u will get.
- std::vector<sf::Vector2f> getAll() - get all path's points.
## Variables
- std::vector<sf::Vector2f> m_elements - all elements of path. First is start point and last is finish point.
----------
# Map

Store path, map

## Functions
- 
## Variables
- 
----------

Paper link: [+Mactangle](https://paper.dropbox.com/doc/Mactangle-x4KMLIYbxsKgOgiTDDxIM) 

