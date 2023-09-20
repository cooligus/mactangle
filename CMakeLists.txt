# This file is part of Mactangle.
# Mactangle is free software distributed under Mozilla Public License Version 2.0.
# You should have received a copy of the Mozilla Public License 
# along with Mactangle. If not, see <https://www.mozilla.org/en-US/MPL/2.0/>.

# Set minimum version of cmake
cmake_minimum_required(VERSION 3.17)
cmake_policy(SET CMP0054 NEW)

# Set up project
project(Mactangle VERSION 1.1.1.04)

# Set positions of sources and resources for cmake
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/rc")
set(LIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")

### Set textures' stuffs
# Set where textures are
set(TEXTURES_DIR "${RESOURCES_DIR}/textures")
set(TEXTURES_INSTALL_DIR "textures")
set(TEXTURES_PROGRAM_DIR "./textures")
set(TEXTURES_EXT "png")
set(NAMES_OF_TEXTURES
        "Background"
        "Bedler"
        "BuyButton"
        "Cart"
        "Coin"
        "Dacler"
        "FirstScreen"
        "Heart"
        "Mactangle"
        "Menu"
        "Path"
        "Sharp"
        "Shop"
)

### Set fonts' stuffs
# Set where fonts are
set(FONTS_DIR "${RESOURCES_DIR}/fonts")
set(FONTS_INSTALL_DIR "fonts")
set(FONTS_PROGRAM_DIR "./fonts")
set(FONTS_EXT "ttf")
set(NAMES_OF_FONTS
        "CubicCoreMono"
)

# Add source to executable
add_executable(Mactangle
        "${SOURCE_DIR}/main.cpp"

        "${SOURCE_DIR}/additionals.cpp"
        "${SOURCE_DIR}/bedler.cpp"
        "${SOURCE_DIR}/dacler.cpp"
        "${SOURCE_DIR}/mactangle.cpp"
        "${SOURCE_DIR}/mainclasses.cpp"
        "${SOURCE_DIR}/map.cpp"
        "${SOURCE_DIR}/offert.cpp"
        "${SOURCE_DIR}/shop.cpp"
        "${SOURCE_DIR}/PPSaB.cpp"
        "${SOURCE_DIR}/MainExecutor.cpp"

        "${SOURCE_DIR}/Layout/Map.cpp"

        "${SOURCE_DIR}/Managers/InputManager.cpp"
        "${SOURCE_DIR}/Managers/Renderer.cpp"
        "${SOURCE_DIR}/Managers/Master.cpp"
        "${SOURCE_DIR}/Managers/MainResources.cpp"

        "${SOURCE_DIR}/Helpers/StringKey.cpp"

        "${SOURCE_DIR}/BaseClasses/Entity.cpp"
        "${SOURCE_DIR}/BaseClasses/PositionableEntity.cpp"
        "${SOURCE_DIR}/BaseClasses/MovingEntity.cpp"
        "${RESOURCES_DIR}/icon/icon.rc"
)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

option(LINKER_OPTIONS "Some additional linker options" "")
# Link libs with mactangle
target_link_libraries(Mactangle PUBLIC sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${LINKER_OPTIONS})

# Add local cmake subdirectory to CMAKE_MODULE_PATH
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Add LW subdirectory for install_stuffs cmake function
include(InstallStuffs)

# Use install_stuffs() function for textures
install_stuffs(TEXTURES NAMES_OF_TEXTURES ${TEXTURES_DIR} ${TEXTURES_INSTALL_DIR} ${TEXTURES_PROGRAM_DIR} ${TEXTURES_EXT})

# Use install_stuffs() function for fonts	
install_stuffs(FONTS NAMES_OF_FONTS ${FONTS_DIR} ${FONTS_INSTALL_DIR} ${FONTS_PROGRAM_DIR} ${FONTS_EXT})

# Install license
install(FILES "${PROJECT_SOURCE_DIR}/LICENSE.md"
        DESTINATION .
)

# Install Mactangle
install(TARGETS Mactangle DESTINATION .)
install(TARGETS Mactangle
        CONFIGURATIONS Release
        RUNTIME DESTINATION Release)
