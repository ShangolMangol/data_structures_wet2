cmake_minimum_required(VERSION 3.22)
project(wet2)

set(CMAKE_CXX_STANDARD 11)

add_executable(wet2 main.cpp CompareTeamById.cpp CompareTeamById.h AVLTree.h AVLTree.cpp Team.cpp Team.h)
