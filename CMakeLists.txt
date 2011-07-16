set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project(PulpJSON)
set(PROJECT_VERSION 0.1)
cmake_minimum_required(VERSION 2.6)

set(SOURCES
	jsonexception.hpp
	parser.cpp
	value.cpp)

add_library(json SHARED ${SOURCES})
set_target_properties(json PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
set_target_properties(json PROPERTIES VERSION ${PROJECT_VERSION})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/pkgconfig ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc @ONLY)
install(TARGETS json DESTINATION lib/ CONFIGURATIONS Release)
install(FILES parser.h value.h DESTINATION include/PulpJSON CONFIGURATIONS Release)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION lib/pkgconfig/ CONFIGURATIONS Release)

add_subdirectory(tests EXCLUDE_FROM_ALL)
