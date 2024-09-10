cmake_minimum_required(VERSION 3.11)
project(tests)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

include_directories(${gtest_SOURCE_DIR})

add_executable(unit_triangles trian_unit_test.cpp)
target_include_directories(unit_triangles PUBLIC ${INCLUDE_DIR})
target_link_libraries(unit_triangles gtest gtest_main)

set(RUN_TESTS ./unit_triangles --gtest_color=yes)
add_custom_target(
    unit_triangles_target ALL
    COMMAND ${RUN_TESTS}
    DEPENDS unit_triangles
)