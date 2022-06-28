cmake_minimum_required(VERSION 3.20)
project(furthest_building_you_can_reach)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS system timer)

add_executable(furthest_building_you_can_reach main.cpp)
target_include_directories(furthest_building_you_can_reach PRIVATE ${Boost_INCLUDE_DIRS})
message("boost lib dir = ${Boost_LIBRARY_DIRS}")
target_link_directories(furthest_building_you_can_reach PRIVATE ${Boost_LIBRARY_DIRS})
target_link_libraries(furthest_building_you_can_reach ${Boost_LIBRARIES})