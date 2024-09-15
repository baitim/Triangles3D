#include <gtest/gtest.h>
#include "triangle.hpp"

TEST(Point_main, test_point_opers)
{
    point::point_t p1(4, 3, 4);
    point::point_t p2(0, 7, 12);

    ASSERT_EQ(p1, point::point_t(4, 3, 4));
    
    point::point_t p3(-1, 1, 2);
    p1 = p1 + p3;
    p1 += p3;
    p2 = p2 - p3;
    p2 -= p3;

    ASSERT_EQ(p1, p2);
}

TEST(Segment_main, test_segment_opers)
{
    point::point_t p1(4, 3, 4);
    point::point_t p2(0, 7, 12);
    segment::segment_t s1(p1, p2);

    point::point_t p3(-4, 4, 8);

    ASSERT_EQ(s1.vector(), p3);
}

TEST(Plane_main, test_plane_opers)
{
    point::point_t p1( 1, 7,   4);
    point::point_t p2(-2, 11,  12);
    point::point_t p3( 3, 13, -8);

    plane::plane_t pl1(p1, p2, p3);
    plane::plane_t pl2(48, 10, 13, -170);

    ASSERT_EQ(pl1, pl2);
    ASSERT_EQ(pl1.norm(), pl2.norm());
}

TEST(Triangle_main, test_triangle_opers)
{
    point::point_t p1(1, 0, 0);
    point::point_t p2(1, 1, 0);
    point::point_t p3(1, 1, 1);

    segment::segment_t s1(p1, p2);
    segment::segment_t s2(p2, p3);
    segment::segment_t s3(p3, p1);

    triangle::triangle_t pl1(s1, s2, s3);
    triangle::triangle_t pl2(p1, p2, p3);

    ASSERT_EQ(pl1, pl2);
    ASSERT_EQ(pl1.plane(), pl2.plane());

    point::point_t p4(1,  4, -6);
    point::point_t p5(1, -2,  10);
    point::point_t p6(1, -3,  5);
    triangle::triangle_t pl3(p4, p5, p6);

    ASSERT_EQ(pl1.plane(), pl3.plane());
}