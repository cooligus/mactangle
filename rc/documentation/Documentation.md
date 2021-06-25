# Mactangle

# Main

Run all game

----------
# Game

Condense all stuffs in one class.


## Methods
    public:
    /// <summary>
    /// It's constructor.
    /// </summary>
    Game(sf::VideoMode videoMode = sf::VideoMode().getDesktopMode(), sf::String windowName = "Mactangle", sf::String fontPath = CUBICCOREMONO_TTF, unsigned int health = 3);
    
    /// <summary>
    /// It's destructor.
    /// </summary>
    ~Game();
## Variables
    private:
    /// <summary>
    /// SFML window.
    /// </summary>
    sf::RenderWindow m_window;
    
    /// <summary>
    /// SFML view.
    /// </summary>
    sf::View m_camera;
    
    /// <summary>
    /// SFML font.
    /// </summary>
    sf::Font m_font;
    
    /// <summary>
    /// Number of hearts.
    /// </summary>
    unsigned int m_health;
----------
# Path

Store all points of path and give element of that path or give all path. Path is getting from .json file or from std::vector<sf::Vector2f>.


## Methods
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
## Variables
    private:
    /// <summary>
    /// All elements of path. First is start point and last is finish point.
    /// </summary>
    std::vector<sf::Vector2f> m_elements;
----------
# TextureContainer

Store texture of map, control it and prepare to use for map class. 

## Methods
    public:
    /// <summary>
    /// Worst type of constuctor for this class because than you forget to push texture to it then something methods will not work.
    /// </summary>
    TextureContainer();
    
    /// <summary>
    /// Type of constuctor where you will have only one texture there.
    /// </summary>
    TextureContainer(std::string path);
    
    /// <summary>
    /// Type of constuctor where you will have some textures there.
    /// </summary>
    TextureContainer(std::vector<std::string> paths);
    
    /// <summary>
    /// Without being does nothing.
     /// </summary>
    ~TextureContainer();
    
    /// Set one path with texture. Best way is to do that using cmake-generated definitions.
    /// <param name="path">- Path to texture.</param>
    /// <param name="index">- "Place" where path to texture have to be.</param>
    /// <param name="withLoad">- Load texture from file and push it into sf::Texture class if true or not if false.</param>
    /// <returns></returns>
    
    bool addPath(std::string path, int index = -1, bool withLoad = true);
    /// <summary>
    /// Change old vector with all paths with textures to new included in vector.
    /// </summary>
    /// <param name="paths">- Paths to textures.</param>
    /// <param name="newIndex">- New index.</param>
    /// <param name="withLoad">- Load texture from file and push it into sf::Texture class if true or not if false.</param>
    /// <returns></returns>
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
    unsigned int getIndex()
    
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
## Variables
    private:
    /// <summary>
    /// Index of texture that is now used as main.
    /// </summary>
    unsigned int m_actualIndex;
    
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

Effect of fitting:

![Case 1: width of texture is bigger than height](https://paper-attachments.dropbox.com/s_BFD4E04807FD1D2555268DDEC7478F24B1D684DFD6DEE60F6C9C168DE38AA391_1624458035458_Case+1+-+width+of+texture+is+bigger+than+height.png)



![Case 2: height of texture is bigger than width](https://paper-attachments.dropbox.com/s_BFD4E04807FD1D2555268DDEC7478F24B1D684DFD6DEE60F6C9C168DE38AA391_1624458038477_Case+2+-+height+of+texture+is+bigger+than+width.png)



----------
# Map - work on that

Store path, map texture and control it. 

## Methods
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
    /// <param name="path"></param>
    /// <param name="texture"></param>
    Map(Path path, sf::Texture texture);
    
    /// <summary>
    /// Tertiary constructor. 
    /// </summary>
    Map();
    
    /// <summary>
    /// Destructor
    /// </summary>
    ~Map();
## Variables
    private:
    /// <summary>
    /// mactangles’ path
    /// </summary>
    Path m_path;
    
    /// <summary>
    /// path look and design
    /// </summary>
    sf::Texture m_texture;
----------
# Paper link

https://www.dropbox.com/scl/fi/n8k3i6gtv7c1vhgzs0m56/Mactangle.paper?dl=0&rlkey=uo2u6cte5u4qyk6ngkhf67y0o 

