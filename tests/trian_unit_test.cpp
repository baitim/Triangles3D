#include <gtest/gtest.h>
#include "lingeo.hpp"

TEST(Points_main, test_points_opers)
{
    point::point_t p1(4, 3, 4);
    point::point_t p2(0, 7 ,12);

    ASSERT_EQ(p1, point::point_t(4, 3, 4));
    
    point::point_t p3(-1, 1, 2);
    p1 = p1 + p3;
    p1 += p3;
    p2 = p2 - p3;
    p2 -= p3;

    ASSERT_EQ(p1, p2);
}