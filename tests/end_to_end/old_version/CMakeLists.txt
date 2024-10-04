cmake_minimum_required(VERSION 3.11)
project(old_version)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../include)

add_executable(triangles_old triangles_old.cpp)
target_include_directories(triangles_old PUBLIC ${INCLUDE_DIR})