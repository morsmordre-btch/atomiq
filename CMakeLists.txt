cmake_minimum_required(VERSION 3.5)
project(atomiq LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread -g -O0")
endif()

add_executable(start_atomiq main.cpp color.cpp color.h
			    colorgen.cpp colorgen.h
			    colorsort.cpp colorsort.h)
