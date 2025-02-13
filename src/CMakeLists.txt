cmake_minimum_required(VERSION 3.11)
project(src)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(triangles triangles.cpp)
target_sources(triangles
    PRIVATE
    FILE_SET HEADERS
    BASE_DIRS ${INCLUDE_DIR}
)

add_library(Triangles3D triangles.cpp)
target_include_directories(Triangles3D PUBLIC
    $<BUILD_INTERFACE:${INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS Triangles3D EXPORT Triangles3DTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY ${INCLUDE_DIR}/Triangles3D DESTINATION include)

install(EXPORT Triangles3DTargets
    FILE Triangles3DConfig.cmake
    DESTINATION lib/cmake/Triangles3D
)