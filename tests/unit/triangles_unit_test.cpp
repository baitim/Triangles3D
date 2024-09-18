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
    ASSERT_EQ(p1 * p2, point::point_t(4, 25, 64));
    ASSERT_EQ(p1 / p2, point::point_t(1, 1, 1));
}

TEST(Point_main, test_point_cross_product)
{
    point::point_t p1(-8, 7, 13);
    point::point_t p2(41, 3, 37);

    point::point_t p3 = point::cross_product(p1, p2);
    point::point_t ans{220, 829, -311};

    ASSERT_EQ(p3, ans);
}

TEST(Point_main, test_point_length)
{
    point::point_t p1(3, 4, 5);
    point::point_t p2(5, 5, 0);
    point::point_t p3(3, 4, 4);

    ASSERT_NEAR(p1.length(), p2.length(), doubles::EPSILON);
    ASSERT_EQ(doubles::is_double_equal(p1.length(), p3.length()), false);
}

TEST(Line_main, test_line_opers)
{
    point::point_t p1(3, 4, 5);
    point::point_t p2(6, 3, 2);

    line::line_t l1(p1, p2);

    point::point_t p3(1, 2, 7);
    point::point_t p4(6, 3, 2);

    line::line_t l2(p3, p4);

    ASSERT_EQ(l1.get_v(), l2.get_v());
    ASSERT_NE(l1.get_x(), l2.get_x());

    point::point_t p5(3, 4, 5);
    line::line_t l3(p5, p2);

    ASSERT_EQ(l1, l3);
}

TEST(Segment_main, test_segment_line_intersection)
{
    point::point_t p1(1, 1, 1);
    point::point_t p2(3, 5, 7);
    segment::segment_t s1(p1, p2);

    line::line_t l1(p1, p2 - p1);

    ASSERT_EQ(s1.is_line_intersect(l1), true);

    point::point_t p3(p2 + 1);
    line::line_t l2(p1 - 1, p3);

    ASSERT_EQ(s1.is_line_intersect(l2), true);

    point::point_t p4((p1 + p2) / 2);
    line::line_t l3(p3, p4 - p3);

    ASSERT_EQ(s1.is_line_intersect(l3), true);

    point::point_t p5(0, 0, 0);
    point::point_t p6(1, 0, 1);
    line::line_t l4(p5, p6);
    ASSERT_EQ(s1.is_line_intersect(l4), false);

    point::point_t p7(0, 0, 0);
    point::point_t p8(1, 1, 1);
    line::line_t l5(p7, p8);
    ASSERT_EQ(s1.is_line_intersect(l5), true);
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

TEST(Plane_main, test_plane_parallel)
{
    point::point_t p1( 7, 1, 1);
    point::point_t p2( 2, 3, 1);
    point::point_t p3(-3, 4, 1);
    plane::plane_t pl1(p1, p2, p3);

    point::point_t p4(1,  4, 2);
    point::point_t p5(7, -2, 2);
    point::point_t p6(6, -3, 2);
    plane::plane_t pl2(p4, p5, p6);

    ASSERT_EQ(plane::is_planes_parallel(pl1, pl2), true);
}

TEST(Plane_main, test_plane_intersection_exist)
{
    point::point_t p1( 3, -9,  5);
    point::point_t p2( 13, 11, 7);
    point::point_t p3(-3, -4,  23);
    plane::plane_t pl1(p1, p2, p3);

    point::point_t p4(-10,  5, 13);
    point::point_t p5( 17, -2, 11);
    point::point_t p6( 6,  -7, 9);
    plane::plane_t pl2(p4, p5, p6);

    point::point_t ans(27784, 74880, 27368);

    ASSERT_EQ(plane::get_planes_intersection(pl1, pl2).get_v(), ans);
}

TEST(Plane_main, test_plane_intersection_not_exist)
{
    point::point_t p1(0, 0, 1);
    point::point_t p2(1, 0, 1);
    point::point_t p3(1, 1, 1);
    plane::plane_t pl1(p1, p2, p3);

    point::point_t p4(1, 1, 2);
    point::point_t p5(2, 3, 2);
    point::point_t p6(4, 4, 2);
    plane::plane_t pl2(p4, p5, p6);

    ASSERT_EQ(plane::get_planes_intersection(pl1, pl2).is_valid(), false);
}

TEST(Triangle_main, test_triangle_opers)
{
    point::point_t p1(1, 0, 0);
    point::point_t p2(1, 1, 0);
    point::point_t p3(1, 1, 1);

    segment::segment_t s1(p1, p2);
    segment::segment_t s2(p2, p3);
    segment::segment_t s3(p3, p1);

    triangle::triangle_t t1(s1, s2, s3);
    triangle::triangle_t t2(p1, p2, p3);

    ASSERT_EQ(t1, t2);
    ASSERT_EQ(t1.get_plane(), t2.get_plane());

    point::point_t p4(1,  4, -6);
    point::point_t p5(1, -2,  10);
    point::point_t p6(1, -3,  5);
    triangle::triangle_t t3(p4, p5, p6);

    ASSERT_EQ(t1.get_plane(), t3.get_plane());
}

TEST(Triangle_main, test_triangle_square)
{
    point::point_t p1(1, 2, 3);
    point::point_t p2(4, 5, 6);
    point::point_t p3(7, 8, 9);
    point::point_t p4(10, 11, 12);
    point::point_t p5(10, 11, 13);

    triangle::triangle_t t1(p1, p2, p3);
    triangle::triangle_t t2(p1, p2, p4);
    triangle::triangle_t t3(p2, p3, p4);

    ASSERT_NEAR(t1.square(), t2.square(), doubles::EPSILON);
    ASSERT_NEAR(t1.square(), t3.square(), doubles::EPSILON);

    triangle::triangle_t t4(p1, p2, p5);
    triangle::triangle_t t5(p2, p3, p5);

    ASSERT_NEAR(t4.square(), t5.square(), doubles::EPSILON);
    ASSERT_EQ(doubles::is_double_equal(t1.square(), t4.square()), false);
    ASSERT_EQ(doubles::is_double_equal(t2.square(), t5.square()), false);
}

TEST(Triangle_main, test_point_in_triangle)
{
    point::point_t p1(-3,  4,  6);
    point::point_t p2( 7,  8, -3);
    point::point_t p3( 2, -5,  1);

    triangle::triangle_t t1(p1, p2, p3);
    plane::plane_t triang_plane{-101, 5, -110, 337};

    ASSERT_EQ(t1.get_plane(), triang_plane);
    ASSERT_EQ(t1.is_point_in(p1), true);
    ASSERT_EQ(t1.is_point_in(p2), true);
    ASSERT_EQ(t1.is_point_in(p3), true);

    ASSERT_EQ(t1.is_point_in((p1 + p2) / 2), true);
    ASSERT_EQ(t1.is_point_in((p1 + p2 + p3) / 3), true);

    point::point_t tp1(1, 2, 3);
    point::point_t tp2(1, 16, 2);
    point::point_t tp3(3, -2.4, 0.2);
    point::point_t tp4(2, -5, 1);

    ASSERT_EQ(t1.is_point_in(tp1), false);
    ASSERT_EQ(t1.is_point_in(tp2), false);
    ASSERT_EQ(t1.is_point_in(tp3), true);
    ASSERT_EQ(t1.is_point_in(tp4), true);
}

TEST(Triangle_main, test_line_intersect_edges)
{
    point::point_t p1(1,  2, 3);
    point::point_t p2(3,  4, 3);
    point::point_t p3(3, -1, 3);
    triangle::triangle_t t1(p1, p2, p3);

    point::point_t p4(2, -1,  6);
    point::point_t p5(-1, 3, -3);
    line::line_t l1(p4, p5);

    ASSERT_EQ(t1.is_line_intersect_edges(l1), true);

    point::point_t p6(1,  4, 3);
    point::point_t p7(3, -1, 0);
    line::line_t l2(p4, p5);

    ASSERT_EQ(t1.is_line_intersect_edges(l2), true);

    point::point_t p8(2, 2,  4.42);
    point::point_t p9(1, 1, -1);
    line::line_t l3(p8, p9);

    ASSERT_EQ(t1.is_line_intersect_edges(l3), false);
}