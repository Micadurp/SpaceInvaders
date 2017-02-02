# CMake settings
cmake_minimum_required(VERSION 3.6)

set(SOLUTION_NAME SpaceInvaders)
project(${SOLUTION_NAME})

option(COMPILE_RELEASE_BUILD "Unchecked is debug" OFF)

set(OUTPUT_FOLDER ${CMAKE_BINARY_DIR}/build)
set(OUTPUT_FOLDER ${OUTPUT_FOLDER}/32)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_FOLDER})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_FOLDER})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_FOLDER})

# Path for copying .dll to correct folder
if(COMPILE_RELEASE_BUILD)
	set(OUTPUT_FOLDER ${OUTPUT_FOLDER}/Release)	
else()
	set(OUTPUT_FOLDER ${OUTPUT_FOLDER}/Debug)
endif()

# Find external libraries and modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/Modules/")
include(create_source_group)

# SFML paths and libs

set(SFML_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/SFML/include)
if(COMPILE_RELEASE_BUILD)
	set(SFML_LIBRARIES sfml-audio.lib sfml-graphics.lib sfml-main.lib sfml-network.lib sfml-system.lib sfml-window.lib)	
else()
	set(SFML_LIBRARIES sfml-audio-d.lib sfml-graphics-d.lib sfml-main-d.lib sfml-network-d.lib sfml-system-d.lib sfml-window-d.lib)	
endif()

# Add SFML
add_subdirectory(SFML)
include_directories(${SFML_INCLUDE_DIR})


set(EXTERNAL_INCLUDE_DIRS)
set(EXTERNAL_LIBRARIES_ALL)
include_directories(${EXTERNAL_INCLUDE_DIRS})

# Set global compiler options
add_definitions(-DUNICODE -D_UNICODE)

# Add subdirectories
add_subdirectory(Dependencies)
add_subdirectory(Game)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Game)

# Copy game resources
add_custom_target(_resourceCopy ALL 
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Assets ${OUTPUT_FOLDER}
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Assets ${CMAKE_BINARY_DIR}/Game
)


# Set the default configuration
if (COMPILE_RELEASE_BUILD)
    set(CMAKE_BUILD_TYPE "Release")
else()
    set(CMAKE_BUILD_TYPE "Debug")
endif()
set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE STRING "" FORCE)