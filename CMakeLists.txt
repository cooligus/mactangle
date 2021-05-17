# Set minimum version of cmake
cmake_minimum_required (VERSION 3.19)

# Set c++ and cmake dependencies
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

# Set up project
project(Mactangle VERSION 1.1)

# Set project version
add_definitions(-DVERSION_MAJOR=${ConsoleGame_VERSION_MAJOR})
add_definitions(-DVERSION_MINOR=${ConsoleGame_VERSION_MINOR})


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
set(PATHS_DIR "${RESOURCES_DIR}/paths")

# Set where fonts have to be installed
set(PATHS_INSTALL_DIR "paths")

# Set where fonts will be (through the eyes of program)
set(PATHS_PROGRAM_DIR "../paths")

# Set extension of fonts
set(PATHS_EXT "json")

# Set names of fonts (All fonts have to be .ttf files)
set(NAMES_OF_PATHS
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
				"${RESOURCES_DIR}/icon/icon.rc"
				  )


# Add SFML subdirectory
add_subdirectory("${LIBS_DIR}/SFML-2.5.1/")

# Add JSON subdirectory
add_subdirectory("${LIBS_DIR}/json/")

# Link libs with Mactangle
target_link_libraries(Mactangle PUBLIC sfml-system sfml-window sfml-graphics sfml-network sfml-audio nlohmann_json::nlohmann_json)


### Convert list of names to more useful variables and install objects
# LIST_NAME - name of list that you will can use
# LIST_OBJ - name of list with names of objects, NAMES_OF_TEXTURES for example
# DIR - cmake directory to file (cmake compile)
# INSTALL_DIRS - cmake installation directories where to install file
# PROGRAM_DIRS - program directories where is file (to bypass problems amount of its elements should be as much as INSTALL_DIRS, else if it's less cmake will loop that)
# EXTENSION - extension of file
function(make_useful_variables LIST_NAME LIST_OBJ DIR INSTALL_DIRS PROGRAM_DIRS EXTENSION)

	# Get size of INSTALL_DIRS
	list(LENGTH ${INSTALL_DIRS} INSTALL_LENGTH)

	# Set INSTALL_NUM to 0 if 1 is less or equal to INSTALL_LENGTH
	if(1 LESS_EQUAL ${INSTALL_LENGTH})
		set(INSTALL_NUM 0)
	endif()

	# Set INSTALL_NOT_LIST to TRUE and set ACTUAL_PROGRAM_DIR to PROGRAM_DIRS if INSTALL_LENGTH equals 1
	if(${INSTALL_LENGTH} EQUAL 0)
		set(INSTALL_NOT_LIST TRUE)
		set(ACTUAL_PROGRAM_DIR ${PROGRAM_DIRS})
	endif()

	# Get size of PROGRAM_DIRS
	list(LENGTH ${PROGRAM_DIRS} PROGRAM_LENGTH)

	# Set PROGRAM_NUM to 0 if 1 is less or equal to PROGRAM_LENGTH
	if(1 LESS_EQUAL ${PROGRAM_LENGTH})
		set(PROGRAM_NUM 0)
	endif()

	# Set PROGRAM_NOT_LIST to TRUE and set ACTUAL_INSTALL_DIR to INSTALL_DIRS if PROGRAM_LENGTH equals 1
	if(${PROGRAM_LENGTH} EQUAL 0)
		set(PROGRAM_NOT_LIST TRUE)
		set(ACTUAL_INSTALL_DIR ${INSTALL_DIRS})
	endif()

	# Make uppertext EXTENSION
	string(TOUPPER ${EXTENSION} UPPERED_EXTENSION)

	# Convert NAME_OF_LIST to more useful variables
	foreach(OBJ_NAME IN LISTS ${LIST_OBJ})
	
		# If PROGRAM_NOT_LIST equal TRUE set ACTUAL_PROGRAM_OBJ
		if(NOT PROGRAM_NOT_LIST)
 			list(GET ${PROGRAM_DIRS} ${PROGRAM_NUM} ACTUAL_PROGRAM_DIR)
		endif()

		# If INSTALL_NOT_LIST equal TRUE set ACTUAL_INSTALL_DIR
		if(NOT INSTALL_NOT_LIST)
 			list(GET ${INSTALL_DIRS} ${INSTALL_NUM} ACTUAL_INSTALL_DIR)
		endif()

		# Set ACTUAL_OBJ
		set(ACTUAL_OBJ "${DIR}/${OBJ_NAME}.${EXTENSION}")

		# Add to LIST next object with its position 
		list(APPEND ${LIST_NAME} ACTUAL_OBJ)
		
		# Set object's dir that program will use
		set(ACTUAL_OBJ_DIR "${ACTUAL_PROGRAM_DIR}/${OBJ_NAME}.${EXTENSION}")
	
		# Make uppertext OBJ_NAME
		string(TOUPPER ${OBJ_NAME} UPPERED_OBJ_NAME)
	
		# Make new definition that mactagnle will use to find object
		add_compile_definitions(${UPPERED_OBJ_NAME}_${UPPERED_EXTENSION}="${ACTUAL_OBJ_DIR}")
 
 		# Install readme
 		install(FILES ${ACTUAL_OBJ}
 			DESTINATION ${ACTUAL_INSTALL_DIR}
 			)

		# Increment variables
 		MATH(EXPR INSTALL_NUM "${INSTALL_NUM}+1")
		MATH(EXPR PROGRAM_NUM "${PROGRAM_NUM}+1")

		# Set INSTALL_NUM to 0 if it's larger or it equals to INSTALL_LENGTH
		if(${INSTALL_NUM} GREATER_EQUAL ${INSTALL_LENGTH})
			set(INSTALL_NUM 0)
		endif()

		# Set PROGRAM_NUM to 0 if it's larger or it equals to PROGRAM_LENGTH
		if(${PROGRAM_NUM} GREATER_EQUAL ${PROGRAM_LENGTH})
			set(PROGRAM_NUM 0)
		endif()
	endforeach()
endfunction()

# Use make_useful_variables() function for textures
make_useful_variables(TEXTURES NAMES_OF_TEXTURES ${TEXTURES_DIR} ${TEXTURES_INSTALL_DIR} ${TEXTURES_PROGRAM_DIR} ${TEXTURES_EXT})

# Use make_useful_variables() function for paths	
make_useful_variables(APATHS NAMES_OF_PATHS ${PATHS_DIR} ${PATHS_INSTALL_DIR} ${PATHS_PROGRAM_DIR} ${PATHS_EXT})

# Use make_useful_variables() function for PATHS	
make_useful_variables(FONTS NAMES_OF_FONTS ${FONTS_DIR} ${FONTS_INSTALL_DIR} ${FONTS_PROGRAM_DIR} ${FONTS_EXT})

# Use make_useful_variables() function for readmes
make_useful_variables(READMES NAMES_OF_READMES ${READMES_DIR} READMES_INSTALL_DIRS READMES_PROGRAM_DIRS ${READMES_EXT})

# Install Mactangle
install(TARGETS Mactangle DESTINATION bin)
install(TARGETS Mactangle
		CONFIGURATIONS Release
        RUNTIME DESTINATION Release)