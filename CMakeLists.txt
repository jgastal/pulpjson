set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project(libjson)
cmake_minimum_required(VERSION 2.6)

set(SOURCES
	parser.cpp
	value.cpp)

add_library(json SHARED ${SOURCES})


add_subdirectory(tests EXCLUDE_FROM_ALL)
