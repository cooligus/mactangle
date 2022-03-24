# This file is part of Mactangle.
# Mactangle is free software distributed under Mozilla Public License Version 2.0.
# You should have received a copy of the Mozilla Public License 
# along with Mactangle. If not, see <https://www.mozilla.org/en-US/MPL/2.0/>.

# Set minimum version of cmake
cmake_minimum_required (VERSION 3.17)
cmake_policy(SET CMP0054 NEW)

# Set up project
project(Mactangle VERSION 1.1.1.04)

# Add definitions
add_definitions(-DPATH_OBJ_NAME="path")
add_definitions(-DPOINT_OBJ_NAME="point-")
add_definitions(-DPOINT_POSITION_X_NAME="x")
add_definitions(-DPOINT_POSITION_Y_NAME="y")

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

# Add source to executable
add_executable (Mactangle
				"${SOURCE_DIR}/additionals.cpp"
				"${SOURCE_DIR}/bedler.cpp"
				"${SOURCE_DIR}/dacler.cpp"
				"${SOURCE_DIR}/mactangle.cpp"
				"${SOURCE_DIR}/main.cpp"
				"${SOURCE_DIR}/mainclasses.cpp"
				"${SOURCE_DIR}/map.cpp"
				"${SOURCE_DIR}/offert.cpp"
				"${SOURCE_DIR}/shop.cpp"
				"${SOURCE_DIR}/PPSaB.cpp"
				"${RESOURCES_DIR}/icon/icon.rc"
				  )


# Set global include string s
set(INCLUDE_STR "include")
set(SINGLE_INCLUDE_STR "single-include")

include(FetchContent)

FetchContent_Declare(
	sfml
	GIT_REPOSITORY https://github.com/SFML/SFML.git 
	GIT_TAG 2f11710abc5aa478503a7ff3f9e654bd2078ebab
	SOURCE_DIR 
)

#
#   ITS HERE
# =========================

FetchContent_GetProperties(sfml)
if(NOT sfml_POPULATED)
  # Fetch the content using previously declared details
  FetchContent_Populate(sfml)

  # Set custom variables, policies, etc.
  # ...

  # Bring the populated content into the build
  add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
endif()

#FetchContent_MakeAvailable(uses_other)

# Add json .h files
#include_directories(SYSTEM "${JSON_PATH}/${INCLUDE_STR}")


# Link libs with mactangle
target_link_libraries(Mactangle PUBLIC sfml-system sfml-window sfml-graphics sfml-network sfml-audio )
 
# Add local cmake subdirectory to CMAKE_MODULE_PATH
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
  
# Add LW subdirectory for install_stuffs cmake function
include(InstallStuffs)

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
