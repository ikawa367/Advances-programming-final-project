cmake_minimum_required(VERSION 3.19)
project(test)

set(CMAKE_CXX_STANDARD 17)

link_directories("${PROJECT_SOURCE_DIR}/SFML-2.5.1/lib")

add_executable( ${PROJECT_NAME} main.cpp MainMenu.cpp MainMenu.h SnakeFunc.h ClassApple.h)

target_include_directories( ${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/SFML-2.5.1/include")
target_link_libraries( ${PROJECT_NAME} opengl32 winmm gdi32 sfml-system sfml-window sfml-graphics sfml-audio)