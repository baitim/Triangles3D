cmake_minimum_required(VERSION 3.11)
project(old_version)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(triangles_old triangles_old.cpp)
target_sources(triangles_old
    PRIVATE
    FILE_SET HEADERS
    BASE_DIRS ${INCLUDE_DIR}
)