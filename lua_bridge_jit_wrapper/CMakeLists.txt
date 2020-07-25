cmake_minimum_required(VERSION 3.16)

set(EXECUTABLE_OUTPUT_PATH ../bin)
set(CMAKE_CXX_FLAGS "-g -std=c++17 -pthread -ldl -lstdc++fs")

project(lua_bridge_jit_wrapper VERSION 1.0)

if(CMAKE_COMPILER_IS_GNUCC)
    message("COMPILER IS GNUCC")
    message(${CMAKE_CURRENT_SOURCE_DIR})
    ADD_DEFINITIONS ( -std=c++1z)
endif(CMAKE_COMPILER_IS_GNUCC)

INCLUDE_DIRECTORIES(../3rd)
INCLUDE_DIRECTORIES(../3rd/lua)
INCLUDE_DIRECTORIES(../3rd/LuaBridge)

file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
source_group("Header" FILES ${CURRENT_HEADERS}) 

aux_source_directory(. DIR_SRCS)
add_executable(lua_bridge_jit_wrapper ${DIR_SRCS} ${CURRENT_HEADERS})

target_link_libraries(lua_bridge_jit_wrapper ${CMAKE_CURRENT_SOURCE_DIR}/../lib/luajit51.a stdc++fs)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
