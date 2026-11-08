cmake_minimum_required(VERSION 3.22)

project(sand VERSION 0.1.1)

find_package(LuaJIT REQUIRED)

add_executable(universe "demos/universe.cpp")
add_executable(loop "demos/loop.cpp")

#add_executable(sand "demos/sand.cpp")
#target_link_libraries(sand PRIVATE LuaJIT::LuaJIT)

install(TARGETS universe loop DESTINATION .)