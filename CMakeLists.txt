cmake_minimum_required(VERSION 3.25)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 20)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(SnakeGame main.cpp Screen.cpp Snake.cpp Snake.cpp Stage.cpp Stage.h Gate.cpp Gate.h Mission.cpp Mission.h SnakeGame.cpp SnakeGame.h)

target_link_libraries(SnakeGame ${CURSES_LIBRARIES})

