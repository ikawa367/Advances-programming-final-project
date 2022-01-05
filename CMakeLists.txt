cmake_minimum_required(VERSION 3.19)
project(prj)

set(CMAKE_CXX_STANDARD 14)

link_directories("${PROJECT_SOURCE_DIR}/SFML/lib")

add_executable( ${PROJECT_NAME} main.cpp)

target_include_directories( ${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/SFML/include")
target_link_libraries( ${PROJECT_NAME} opengl32 winmm gdi32 sfml-system sfml-window sfml-graphics)