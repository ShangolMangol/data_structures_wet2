cmake_minimum_required(VERSION 3.22)
project(wet2)

set(CMAKE_CXX_STANDARD 11)

add_executable(wet2 main.cpp ComparePlayerById.cpp ComparePlayerById.h CompareTeamById.cpp CompareTeamById.h AVLTree.h AVLTree.cpp Team.cpp Team.h HashTable.cpp HashTable.h Player.cpp Player.h CompareTeamByAbility.cpp CompareTeamByAbility.h)

add_executable(segelTests main23a2.cpp ComparePlayerById.cpp ComparePlayerById.h CompareTeamById.cpp CompareTeamById.h AVLTree.h AVLTree.cpp Team.cpp Team.h HashTable.cpp HashTable.h Player.cpp Player.h CompareTeamByAbility.cpp CompareTeamByAbility.h worldcup23a2.h worldcup23a2.cpp)

add_executable(studentTest1 main23a2.cpp ComparePlayerById.cpp ComparePlayerById.h CompareTeamById.cpp CompareTeamById.h AVLTree.h AVLTree.cpp Team.cpp Team.h HashTable.cpp HashTable.h Player.cpp Player.h CompareTeamByAbility.cpp CompareTeamByAbility.h worldcup23a2.h worldcup23a2.cpp)
