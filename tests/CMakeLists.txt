include_directories(${CMAKE_SOURCE_DIR})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(tests test.cpp)
target_link_libraries(tests json ${Boost_LIBRARIES})

add_custom_command(TARGET tests POST_BUILD COMMAND "./tests")
