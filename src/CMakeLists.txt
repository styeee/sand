cmake_minimum_required(VERSION 3.22)

project(sand VERSION 0.3.2)

set(LUAJIT_USE_STATIC ON)
find_package(LuaJIT REQUIRED)

add_executable(universe "demos/universe.cpp")
add_executable(loop "demos/loop.cpp")

add_executable(inter "demos/inter.cpp")
target_link_libraries(inter PRIVATE LuaJIT::LuaJIT)
set_target_properties(inter PROPERTIES
    INSTALL_RPATH "$ORIGIN"
)

install(TARGETS universe loop inter RUNTIME_DEPENDENCIES DESTINATION .)
