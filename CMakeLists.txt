# Set minimum version of cmake
cmake_minimum_required (VERSION 3.19)

# Set c++ and cmake dependencies
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

# Set up project
project(Mactangle VERSION 1.1.1.02)


# Set positions of sources and resources for cmake
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/rc")
set(LIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")

### Set textures's stuffs 
# Set where textures are
set(TEXTURES_DIR "${RESOURCES_DIR}/textures")

# Set where textures have to be installed
set(TEXTURES_INSTALL_DIR "textures")

# Set where textures will be (through the eyes of program)
set(TEXTURES_PROGRAM_DIR "../textures")

# Set extension of textures
set(TEXTURES_EXT "png")

# Set names of textures (All textures have to be .ttf files)
set(NAMES_OF_TEXTURES
	"Background" 
	"Bedler"
	"BuyButton"
	"Cart"
	"Cartt"
	"Coin"
	"Dacler"
	"FirstScreen"
	"Heart"
	"Mactangle"
	"Menu"
	"Path"
	"Sharp"
	"Sharpp"
	"Shop"
	)

### Set paths's stuffs 
# Set where fonts are
set(DATA_DIR "${RESOURCES_DIR}/data")

# Set where fonts have to be installed
set(DATA_INSTALL_DIR "data")

# Set where fonts will be (through the eyes of program)
set(DATA_PROGRAM_DIR "../data")

# Set extension of fonts
set(DATA_EXT "json")

# Set names of fonts (All fonts have to be .ttf files)
set(NAMES_OF_DATA
	"default"
	)

### Set fonts's stuffs 
# Set where fonts are
set(FONTS_DIR "${RESOURCES_DIR}/fonts")

# Set where fonts have to be installed
set(FONTS_INSTALL_DIR "fonts")

# Set where fonts will be (through the eyes of program)
set(FONTS_PROGRAM_DIR "../fonts")

# Set extension of fonts
set(FONTS_EXT "ttf")

# Set names of fonts (All fonts have to be .ttf files)
set(NAMES_OF_FONTS
	"CubicCoreMono"
	)

### Set readmes's stuffs 
# Set where readmes are
set(READMES_DIR "${RESOURCES_DIR}/readmes")

# Set where readmes have to be installed
set(READMES_INSTALL_DIRS
	"bin"
	"textures"
	)

# Set where readmes will be (through the eyes of program)
set(READMES_PROGRAM_DIRS
	"."
	"../textures"
	)

# Set extension of readmes
set(READMES_EXT "md")

# Set names of readmes (All readmes have to be .md files)
set(NAMES_OF_READMES
	"LICENSE"
	"TexturesInstruction"
	)
	

message(${TEXTURES_DIR})

# Add source to executable
add_executable (Mactangle
				"${SOURCE_DIR}/Game.cpp"
				"${SOURCE_DIR}/Main.cpp"
				"${SOURCE_DIR}/Map.cpp"
				"${SOURCE_DIR}/Path.cpp"
				"${SOURCE_DIR}/TextureContainer.cpp"
				"${RESOURCES_DIR}/icon/icon.rc"
				  )


# Add SFML subdirectory
add_subdirectory("${LIBS_DIR}/SFML-2.5.1/")

# Add JSON subdirectory
add_subdirectory("${LIBS_DIR}/json/")

# Link libs with Mactangle
target_link_libraries(Mactangle PUBLIC sfml-system sfml-window sfml-graphics sfml-network sfml-audio nlohmann_json::nlohmann_json)

# Add LW subdirectory
add_subdirectory("${LIBS_DIR}/LW/")

# Add LW to Mactangle 
target_include_directories(Mactangle PUBLIC LW)

# Use install_stuffs() function for textures
install_stuffs(TEXTURES NAMES_OF_TEXTURES ${TEXTURES_DIR} ${TEXTURES_INSTALL_DIR} ${TEXTURES_PROGRAM_DIR} ${TEXTURES_EXT})

# Use install_stuffs() function for data	
install_stuffs(DATA NAMES_OF_DATA ${DATA_DIR} ${DATA_INSTALL_DIR} ${DATA_PROGRAM_DIR} ${DATA_EXT})

# Use install_stuffs() function for fonts	
install_stuffs(FONTS NAMES_OF_FONTS ${FONTS_DIR} ${FONTS_INSTALL_DIR} ${FONTS_PROGRAM_DIR} ${FONTS_EXT})

# Use install_stuffs() function for readmes
install_stuffs(READMES NAMES_OF_READMES ${READMES_DIR} READMES_INSTALL_DIRS READMES_PROGRAM_DIRS ${READMES_EXT})

# Install Mactangle
install(TARGETS Mactangle DESTINATION bin)
install(TARGETS Mactangle
		CONFIGURATIONS Release
        RUNTIME DESTINATION Release)