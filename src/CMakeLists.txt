cmake_minimum_required(VERSION 3.11)
project(src)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(triangles triangles.cpp)
target_include_directories(triangles PUBLIC ${INCLUDE_DIR})

set(PYTHON_SCRIPT "${CMAKE_SOURCE_DIR}/tests/end_to_end/run_tests.py")
add_test(
    NAME end_to_end_triangles_target
    COMMAND python3 ${PYTHON_SCRIPT}
)