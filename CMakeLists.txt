cmake_minimum_required(VERSION 3.28)
set(CMAKE_LANGUAGE_COMPILER "/Library/Developer/CommandLineTools/usr/bin/c++")
project(AntDraw LANGUAGES CXX VERSION 3.28)
add_definitions(-std=c++17)
add_executable(AntDraw src/main.cpp src/ant.cpp src/color.cpp)
target_include_directories(AntDraw PUBLIC /opt/homebrew/include/)

target_link_directories(AntDraw PUBLIC /opt/homebrew/lib /Users/johnwhitman/Projects/vivid)
target_link_libraries(AntDraw -lsfml-graphics -lsfml-window -lsfml-system -lvivid)
find_library(AntDraw sfml)
set(CXXFLAGS "-g -O3")

set(SOURCE_DIR src)

