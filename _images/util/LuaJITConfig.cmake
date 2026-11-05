find_package(PkgConfig REQUIRED)
pkg_check_modules(PC_LUAJIT REQUIRED IMPORTED_TARGET luajit)

add_library(LuaJIT::LuaJIT INTERFACE IMPORTED)
target_link_libraries(LuaJIT::LuaJIT INTERFACE PkgConfig::PC_LUAJIT)

message(STATUS "LuaJIT::LuaJIT loaded!")