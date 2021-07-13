# MIT License
# 
# Copyright (c) 2021 Gienczyslaw
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Set up LW library (list work)
project(LW VERSION 1.1)

### Check is LIST_NAME variable and set special variables (use onle in make_useful_variables function before it's foreach())
# LIST_NAME - name of list or variable
# INCREMENTER_NAME - name of variable that will be incementer
# LENGTH_NAME - name of variable that will be size of list
# BOOL_NAME - name of variable that will tell is variable list or not
# ACTUAL_OBJECT - name of variable that will be actual object
function(prepare_incrementer LIST_NAME INCREMENTER_NAME LENGTH_NAME BOOL_NAME ACTUAL_OBJECT)

	# Get size of INSTALL_DIRS and set it
	list(LENGTH ${LIST_NAME} LIST_LENGTH)
	set(${LENGTH_NAME} ${LIST_LENGTH} PARENT_SCOPE)
	set(${INCREMENTER_NAME} 0 PARENT_SCOPE)
	
	# Set INSTALL_NUM to 0 if 1 is less or equal to INSTALL_LENGTH
	if(${LIST_LENGTH} GREATER_EQUAL 2)
		set(${BOOL_NAME} FALSE PARENT_SCOPE)
		list(GET ${LIST_NAME} 0 ${ACTUAL_OBJECT})
		set(${ACTUAL_OBJECT} ${${ACTUAL_OBJECT}} PARENT_SCOPE)
		
	# Set LIST_NOT_LIST to TRUE and set ACTUAL_LIST_DIR to LIST_DIRS if LIST_LENGTH is greter or equals 1 or 0
	elseif(${LIST_LENGTH} LESS_EQUAL 1)
		set(${BOOL_NAME} TRUE PARENT_SCOPE)
		set(${ACTUAL_OBJECT} ${LIST_NAME} PARENT_SCOPE)
	
	endif()
	
endfunction()

### Check is OBJ_BOOL false and if it is set actual object, increment variable and check is inctrementer too large (use onle in make_useful_variables function in it's foreach())
# OBJ_BOOL - 
# LIST_NAME - 
# LIST_LENGHT - 
# OBJ_NUM - 
# ACTUAL_OBJ - 
function(check_is_variable_not_list OBJ_BOOL LIST_NAME LIST_LENGHT OBJ_NUM ACTUAL_OBJ)

	# Check is OBJ_BOOL 
	if(NOT ${OBJ_BOOL})
 
		# Get ACTUAL_OBJ from list 
		list(GET ${${LIST_NAME}} ${${OBJ_NUM}} ${ACTUAL_OBJ})
		
		# Increment variables
 		MATH(EXPR ${OBJ_NUM} "${${OBJ_NUM}}+1")
		
		# Set INSTALL_NUM to 0 if it's larger or it equals to INSTALL_LENGTH
		if(${${OBJ_NUM}} GREATER_EQUAL ${LIST_LENGHT})
			set(${OBJ_NUM} 0)
		endif()

		set(${OBJ_NUM} ${${OBJ_NUM}} PARENT_SCOPE)
		set(${ACTUAL_OBJ} ${${ACTUAL_OBJ}} PARENT_SCOPE)

	endif()

endfunction()

### Convert list of names to more useful variables and install objects
# LIST_NAME - name of list that you will can use
# LIST_OBJ - name of list with names of objects, NAMES_OF_TEXTURES for example
# DIR - cmake directory to file (cmake compile)
# INSTALL_DIRS - cmake installation directories where to install file
# PROGRAM_DIRS - program directories where is file (to bypass problems amount of its elements should be as much as INSTALL_DIRS, else if it's less cmake will loop that)
# EXTENSION - extension of file
function(install_stuffs LIST_NAME LIST_OBJ DIR INSTALL_DIRS PROGRAM_DIRS EXTENSION)

	# Prepare incrementer or set 
	prepare_incrementer(${INSTALL_DIRS} INSTALL_NUM INSTALL_LENGTH INSTALL_NOT_LIST ACTUAL_INSTALL)

	# Prepare incrementer or set 
	prepare_incrementer(${PROGRAM_DIRS} PROGRAM_NUM PROGRAM_LENGTH PROGRAM_NOT_LIST ACTUAL_PROGRAM)
	
	# Make uppertext EXTENSION
	string(TOUPPER ${EXTENSION} UPPERED_EXTENSION)

	set(${INSTALL_NUM} ${INSTALL_NUM})

	
	# Convert NAME_OF_LIST to more useful variables
	foreach(OBJ_NAME IN LISTS ${LIST_OBJ})

		# Check is PROGRAM_NOT_LIST not TRUE and do something if it
		check_is_variable_not_list(${PROGRAM_NOT_LIST} PROGRAM_DIRS ${PROGRAM_LENGTH} PROGRAM_NUM ACTUAL_PROGRAM)
		
		# Check is INSTALL_NOT_LIST not TRUE and do something if it
		check_is_variable_not_list(${INSTALL_NOT_LIST} INSTALL_DIRS ${INSTALL_LENGTH} INSTALL_NUM ACTUAL_INSTALL)
		
		# Set ACTUAL_OBJ
		set(ACTUAL_OBJ "${DIR}/${OBJ_NAME}.${EXTENSION}")

		# Add to LIST next object with its position 
		list(APPEND ${LIST_NAME} ACTUAL_OBJ PARENT_SCOPE)
		
		# Set object's dir that program will use
		set(ACTUAL_OBJ_DIR "${ACTUAL_PROGRAM}/${OBJ_NAME}.${EXTENSION}")
	
		# Make uppertext OBJ_NAME
		string(TOUPPER ${OBJ_NAME} UPPERED_OBJ_NAME)
	
		# Make new definition that mactagnle will use to find object
		add_compile_definitions(${UPPERED_OBJ_NAME}_${UPPERED_EXTENSION}="${ACTUAL_OBJ_DIR}")
 
 		# Install readme
 		install(FILES ${ACTUAL_OBJ}
 			DESTINATION ${ACTUAL_INSTALL}
 			)
			
	endforeach()

endfunction()