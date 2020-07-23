cmake_minimum_required(VERSION 3.16)

set(EXECUTABLE_OUTPUT_PATH ../bin)
set(CMAKE_CXX_FLAGS "-g -pthread -lstdc++fs")

project(lua_bridge_jit_wrapper VERSION 1.0)

if(CMAKE_COMPILER_IS_GNUCC)
    message("COMPILER IS GNUCC")
    ADD_DEFINITIONS ( -std=c++1y)
endif(CMAKE_COMPILER_IS_GNUCC)

file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp ../3rd/lua/*.h ../3rd/lua/*.hpp ../3rd/LuaBridge/*.h ../3rd/LuaBridge/*.hpp)
source_group("Header" FILES ${CURRENT_HEADERS}) 

aux_source_directory(. DIR_SRCS)
add_executable(lua_bridge_jit_wrapper ${DIR_SRCS} ${CURRENT_HEADERS})

target_link_libraries(lua_bridge_jit_wrapper ../lib/luajit51.a)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)