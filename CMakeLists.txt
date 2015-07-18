cmake_minimum_required(VERSION 2.6)
project(generator)

add_definitions(-std=c++11 -pedantic -Wall -Wextra)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(GML_INCLUDE_DIR "" CACHE FILEPATH "GML include path")
if(GML_INCLUDE_DIR)
	include_directories(${GML_INCLUDE_DIR})
endif()

add_subdirectory(src)
add_subdirectory(images)
