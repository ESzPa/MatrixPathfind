cmake_minimum_required(VERSION 3.20)
project(MatrixSearch LANGUAGES CXX)

set(bin msearch)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
# set(RAYLIB_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# set(RAYLIB_BUILD_GAMES OFF CACHE BOOL "" FORCE)

# add_subdirectory(${CMAKE_SOURCE_DIR}/external/raylib)

file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(${bin} ${SOURCES})

target_include_directories(${bin} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)

# target_link_libraries(${bin} PRIVATE raylib)
