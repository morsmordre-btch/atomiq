cmake_minimum_required(VERSION 3.5)
project(test_task_atomiq LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread")
endif()

add_executable(atomiq main.cpp color.cpp color.h
		      colorgen.cpp colorgen.h
		      colorsort.cpp colorsort.h)
