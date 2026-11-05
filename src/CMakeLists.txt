cmake_minimum_required(VERSION 3.22)

project(sand)

add_executable(universe "demos/universe.cpp")
install(TARGETS universe DESTINATION .)