# MIT License

cmake_minimum_required(VERSION 2.8.4)
project(ConwaysGameOfLife)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(SOURCE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(SOURCE_FILES "${SOURCE_DIRECTORY}/main.cxx" "${SOURCE_DIRECTORY}/cell.cxx")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(ConwaysGameOfLife ${SOURCE_FILES})
target_link_libraries(ConwaysGameOfLife ${SDL2_LIBRARIES})
