#include "Triangles3D/octree.hpp"
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

std::vector<std::string> get_sorted_files(std::filesystem::path path) {
    std::vector<std::string> files;

    for (const auto& entry : std::filesystem::directory_iterator(path))
        files.push_back(entry.path().string());

    std::sort(files.begin(), files.end());
    return files;
}

TEST(Octree_end_to_end, end_to_end) 
{
    std::string file{__FILE__};

    std::filesystem::path dir = file.substr(0, file.rfind("/"));
    std::filesystem::path answers_new_path = dir / "../end_to_end/answers_new/";
    std::filesystem::path answers_old_path = dir / "../end_to_end/answers_old/";

    std::vector<std::string> answers_new_str = get_sorted_files(answers_new_path);
    std::vector<std::string> answers_old_str = get_sorted_files(answers_old_path);
    const int count_tests  = answers_new_str.size();

    for (int i = 0, index; i < count_tests; ++i) {
        std::ifstream answer_new_file(answers_new_str[i]);
        std::vector<int> ans_new;
        while (answer_new_file >> index)
            ans_new.push_back(index);
        answer_new_file.close();

        std::ifstream answer_old_file(answers_old_str[i]);
        std::vector<int> ans_old;
        while (answer_old_file >> index)
            ans_old.push_back(index);
        answer_old_file.close();

        EXPECT_EQ(ans_new.size(), ans_old.size());
        for (int j = 0, end = ans_new.size(); j < end; ++j)
            EXPECT_EQ(ans_new[j], ans_old[j]);
    }
}

TEST(Point_main, test_point_opers)
{
    point::point_t<long double> p1(4, 3, 4);
    point::point_t<long double> p2(0, 7, 12);

    ASSERT_EQ(p1, point::point_t<long double>(4, 3, 4));
    
    point::point_t<long double> p3(-1, 1, 2);
    p1 = p1 + p3;
    p1 += p3;
    p2 = p2 - p3;
    p2 -= p3;

    ASSERT_EQ(p1, p2);
    ASSERT_EQ(p1 * p2, point::point_t<long double>(4, 25, 64));
    ASSERT_EQ(p1 / p2, point::point_t<long double>(1, 1, 1));
}

TEST(Point_main, test_point_cross_product)
{
    point::point_t<long double> p1(-8, 7, 13);
    point::point_t<long double> p2(41, 3, 37);

    point::point_t<long double> p3 = point::cross_product(p1, p2);
    point::point_t<long double> ans1{220, 829, -311};

    ASSERT_EQ(p3, ans1);

    point::point_t<long double> p4(0,  1, -2);
    point::point_t<long double> p5(0, -2, -1);

    point::point_t<long double> p6 = point::cross_product(p4, p5);
    point::point_t<long double> ans2{-5, 0, 0};

    ASSERT_EQ(p6, ans2);
}

TEST(Point_main, test_point_length)
{
    point::point_t<long double> p1(3, 4, 5);
    point::point_t<long double> p2(5, 5, 0);
    point::point_t<long double> p3(3, 4, 4);

    ASSERT_NEAR(p1.length(), p2.length(), std::numeric_limits<long double>::epsilon());
    ASSERT_EQ(real_numbers::is_real_eq(p1.length(), p3.length()), false);
}

TEST(Line_main, test_line_opers)
{
    point::point_t<long double> p1(3, 4, 5);
    point::point_t<long double> p2(4, 2, 2);

    line::line_t<long double> l1(p1, p2);

    point::point_t<long double> p3(4, 4, 5);
    point::point_t<long double> p4(4, 2, 2);

    line::line_t<long double> l2(p3, p4);

    ASSERT_EQ(l1.v_, l2.v_);
    ASSERT_NE(l1.x_, l2.x_);

    point::point_t<long double> p5(3, 4, 5);
    line::line_t<long double> l3(p5, p2);

    ASSERT_EQ(l1, l3);
}

TEST(Line_main, test_line_intersects)
{
    point::point_t<long double> p1(3, 4, 5);
    point::point_t<long double> p2(4, 2, 2);

    line::line_t<long double> l1(p1, p2);

    point::point_t<long double> p3(4, 4, 5);
    point::point_t<long double> p4(4, 2, 2);

    line::line_t<long double> l2(p3, p4);

    ASSERT_EQ(line::is_lines_intersect(l1, l2), true);

    point::point_t<long double> p5(3, 4, 5);
    line::line_t<long double> l3(p5, p2);
    ASSERT_EQ(line::is_lines_intersect(l1, l3), true);
}

TEST(Segment_main, test_segment_intersect1)
{
    point::point_t<long double> p1(1, 1, 1);
    point::point_t<long double> p2(2, 2, 2);
    segment::segment_t<long double> s1(p1, p2);

    point::point_t<long double> p3(-1, -1, -1);
    point::point_t<long double> p4(0.5, 0.5, 0.5);
    segment::segment_t<long double> s2(p3, p4);
    segment::segment_t<long double> s3(p3, p1);
    segment::segment_t<long double> s4(p4, p2);

    ASSERT_EQ(s1.is_segment_intersect(s2), false);
    ASSERT_EQ(s1.is_segment_intersect(s3), true);
    ASSERT_EQ(s1.is_segment_intersect(s4), true);

    point::point_t<long double> p5(2, 0, 1);
    segment::segment_t<long double> s5(p5, p1);
    ASSERT_EQ(s1.is_segment_intersect(s5), true);

    point::point_t<long double> p6(1.5, 1.5, 1.5);
    segment::segment_t<long double> s6(p5, p6);
    ASSERT_EQ(s1.is_segment_intersect(s6), true);

    point::point_t<long double> p7(1.6, 1.5, 1.5);
    segment::segment_t<long double> s7(p5, p7);
    ASSERT_EQ(s1.is_segment_intersect(s7), false);

    ASSERT_EQ(s1.is_point_in(point::point_t<long double>(1.5, 1.5, 1.5)), true);
    ASSERT_EQ(s1.is_point_in(p7), false);
}

TEST(Segment_main, test_segment_intersect2)
{
    point::point_t<long double> p1(3, 3, 1);
    point::point_t<long double> p2(6, 6, 1);
    point::point_t<long double> p3(6, 3, 1);
    segment::segment_t<long double> s12(p1, p2);
    segment::segment_t<long double> s23(p2, p3);
    segment::segment_t<long double> s31(p3, p1);

    ASSERT_EQ(s12.is_segment_intersect(s23), true);
    ASSERT_EQ(s12.is_segment_intersect(s31), true);
    ASSERT_EQ(s23.is_segment_intersect(s31), true);


    point::point_t<long double> p4(0, 4, 1);
    point::point_t<long double> p5(0, 5, 1);
    point::point_t<long double> p6(2, 4, 1);
    segment::segment_t<long double> s45(p4, p5);
    segment::segment_t<long double> s56(p5, p6);
    segment::segment_t<long double> s64(p6, p4);

    ASSERT_EQ(s45.is_segment_intersect(s56), true);
    ASSERT_EQ(s45.is_segment_intersect(s64), true);
    ASSERT_EQ(s56.is_segment_intersect(s64), true);

    ASSERT_EQ(s12.is_segment_intersect(s45), false);
    ASSERT_EQ(s12.is_segment_intersect(s56), false);
    ASSERT_EQ(s12.is_segment_intersect(s64), false);
    ASSERT_EQ(s23.is_segment_intersect(s45), false);
    ASSERT_EQ(s23.is_segment_intersect(s56), false);
    ASSERT_EQ(s23.is_segment_intersect(s64), false);
    ASSERT_EQ(s31.is_segment_intersect(s45), false);
    ASSERT_EQ(s31.is_segment_intersect(s56), false);
    ASSERT_EQ(s31.is_segment_intersect(s64), false);
}

TEST(Segment_main, test_segment_intersect3)
{
    point::point_t<long double> p1(3, 0, 1);
    point::point_t<long double> p2(7, 5, 1);
    point::point_t<long double> p3(7, 0, 1);
    segment::segment_t<long double> s12(p1, p2);
    segment::segment_t<long double> s23(p2, p3);
    segment::segment_t<long double> s31(p3, p1);

    point::point_t<long double> p4(3, 0, 1);
    point::point_t<long double> p5(0, 3, 1);
    point::point_t<long double> p6(3, 3, 3);
    segment::segment_t<long double> s45(p4, p5);
    segment::segment_t<long double> s56(p5, p6);
    segment::segment_t<long double> s64(p6, p4);

    ASSERT_EQ(s12.is_segment_intersect(s23), true);
    ASSERT_EQ(s12.is_segment_intersect(s31), true);
    ASSERT_EQ(s23.is_segment_intersect(s31), true);

    ASSERT_EQ(s45.is_segment_intersect(s56), true);
    ASSERT_EQ(s45.is_segment_intersect(s64), true);
    ASSERT_EQ(s56.is_segment_intersect(s64), true);

    ASSERT_EQ(s12.is_segment_intersect(s45), true);
    ASSERT_EQ(s12.is_segment_intersect(s56), false);
    ASSERT_EQ(s12.is_segment_intersect(s64), true);
    ASSERT_EQ(s23.is_segment_intersect(s45), false);
    ASSERT_EQ(s23.is_segment_intersect(s56), false);
    ASSERT_EQ(s23.is_segment_intersect(s64), false);
    ASSERT_EQ(s31.is_segment_intersect(s45), true);
    ASSERT_EQ(s31.is_segment_intersect(s56), false);
    ASSERT_EQ(s31.is_segment_intersect(s64), true);
}

void check_all_sides_segment_intersect(point::point_t<long double> p00,
                                       point::point_t<long double> p01,
                                       point::point_t<long double> p10,
                                       point::point_t<long double> p11) {
    segment::segment_t<long double> s(p11, p11 + p11);
    segment::segment_t<long double> rs(p11 + p11, p11);
    segment::segment_t<long double> s1(p00, p11);
    segment::segment_t<long double> s2(p01, p11);
    segment::segment_t<long double> s3(p10, p11);
    segment::segment_t<long double> s4(p10 + p10, p11);
    segment::segment_t<long double> s5(p01 + p01, p11);
    segment::segment_t<long double> s6(p11 + p11, p11);

    ASSERT_EQ(s.is_segment_intersect(s1), true);
    ASSERT_EQ(s.is_segment_intersect(s2), true);
    ASSERT_EQ(s.is_segment_intersect(s3), true);
    ASSERT_EQ(s.is_segment_intersect(s4), true);
    ASSERT_EQ(s.is_segment_intersect(s5), true);
    ASSERT_EQ(s.is_segment_intersect(s6), true);

    ASSERT_EQ(rs.is_segment_intersect(s1), true);
    ASSERT_EQ(rs.is_segment_intersect(s2), true);
    ASSERT_EQ(rs.is_segment_intersect(s3), true);
    ASSERT_EQ(rs.is_segment_intersect(s4), true);
    ASSERT_EQ(rs.is_segment_intersect(s5), true);
    ASSERT_EQ(rs.is_segment_intersect(s6), true);
}

TEST(Segment_main, test_segment_intersect4)
{
    point::point_t<long double> p00(0, 0, 0);
    point::point_t<long double> p01(0, 1, 0);
    point::point_t<long double> p10(1, 0, 0);
    point::point_t<long double> p11(1, 1, 0);
    check_all_sides_segment_intersect(p00, p01, p10, p11);

    point::point_t<long double> rp01( 0, -1, 0);
    point::point_t<long double> rp10(-1,  0, 0);
    point::point_t<long double> rp11(-1, -1, 0);

    check_all_sides_segment_intersect(p00, rp01, rp10, rp11);

    point::point_t<long double> ryp00(-1, 1, 0);
    check_all_sides_segment_intersect(p00, p01, rp10, ryp00);

    point::point_t<long double> rxp00(1, -1, 0);
    check_all_sides_segment_intersect(p00, rp01, p10, rxp00);
}

TEST(Segment_main, test_segment_line_intersection)
{
    point::point_t<long double> p1(1, 1, 1);
    point::point_t<long double> p2(3, 5, 7);
    segment::segment_t<long double> s1(p1, p2);

    line::line_t<long double> l1(p1, p2 - p1);

    ASSERT_EQ(s1.get_line_intersect(l1).is_valid_, true);

    point::point_t<long double> p3(p2 + point::point_t<long double>{1});
    line::line_t<long double> l2(p1 - point::point_t<long double>{1}, p3);

    ASSERT_EQ(s1.get_line_intersect(l2).is_valid_, true);

    point::point_t<long double> p4((p1 + p2) / point::point_t<long double>{2});
    line::line_t<long double> l3(p3, p4 - p3);

    ASSERT_EQ(s1.get_line_intersect(l3).is_valid_, true);

    point::point_t<long double> p5(0, 0, 0);
    point::point_t<long double> p6(1, 0, 1);
    line::line_t<long double> l4(p5, p6);
    ASSERT_EQ(s1.get_line_intersect(l4).is_valid_, false);

    point::point_t<long double> p7(0, 0, 0);
    point::point_t<long double> p8(1, 1, 1);
    line::line_t<long double> l5(p7, p8);
    ASSERT_EQ(s1.get_line_intersect(l5).is_valid_, true);
}

TEST(Segment_main, test_segment_intersect5)
{
    point::point_t<long double> p1(1, 1,  2);
    point::point_t<long double> p2(1, 1, -2);
    segment::segment_t<long double> s1(p1, p2);

    point::point_t<long double> p3(1, 1,  1);
    point::point_t<long double> p4(1, 1, -1);
    segment::segment_t<long double> s2(p3, p4);

    ASSERT_EQ(s1.is_segment_intersect(s2), true);
}

TEST(Plane_main, test_plane_opers)
{
    point::point_t<long double> p1( 1, 7,   4);
    point::point_t<long double> p2(-2, 11,  12);
    point::point_t<long double> p3( 3, 13, -8);

    plane::plane_t<long double> pl1(p1, p2, p3);
    plane::plane_t<long double> pl2(48, 10, 13, -170);

    ASSERT_EQ(pl1, pl2);
    ASSERT_EQ(pl1.norm(), pl2.norm());
}

TEST(Plane_main, test_plane_opers2)
{
    point::point_t<long double> p4(1,  0,  1);
    point::point_t<long double> p5(1,  1, -1);
    point::point_t<long double> p6(1, -2,  0);
    plane::plane_t<long double> pl3(p4, p5, p6);
    plane::plane_t<long double> pl4(1, 0, 0, -1);

    ASSERT_EQ(pl3.norm(), pl4.norm());
}

TEST(Plane_main, test_plane_parallel)
{
    point::point_t<long double> p1( 7, 1, 1);
    point::point_t<long double> p2( 2, 3, 1);
    point::point_t<long double> p3(-3, 4, 1);
    plane::plane_t<long double> pl1(p1, p2, p3);

    point::point_t<long double> p4(1,  4, 2);
    point::point_t<long double> p5(7, -2, 2);
    point::point_t<long double> p6(6, -3, 2);
    plane::plane_t<long double> pl2(p4, p5, p6);

    ASSERT_EQ(plane::is_planes_parallel(pl1, pl2), true);
}

TEST(Plane_main, test_plane_intersection_exist)
{
    point::point_t<long double> p1( 3, -9,  5);
    point::point_t<long double> p2( 13, 11, 7);
    point::point_t<long double> p3(-3, -4,  23);
    plane::plane_t<long double> pl1(p1, p2, p3);

    point::point_t<long double> p4(-10,  5, 13);
    point::point_t<long double> p5( 17, -2, 11);
    point::point_t<long double> p6( 6,  -7, 9);
    plane::plane_t<long double> pl2(p4, p5, p6);

    point::point_t<long double> ans(27784, 74880, 27368);
    ans = ans.norm();

    ASSERT_EQ(plane::get_planes_intersection(pl1, pl2).v_, ans);
}

TEST(Plane_main, test_plane_intersection_not_exist)
{
    point::point_t<long double> p1(0, 0, 1);
    point::point_t<long double> p2(1, 0, 1);
    point::point_t<long double> p3(1, 1, 1);
    plane::plane_t<long double> pl1(p1, p2, p3);

    point::point_t<long double> p4(1, 1, 2);
    point::point_t<long double> p5(2, 3, 2);
    point::point_t<long double> p6(4, 4, 2);
    plane::plane_t<long double> pl2(p4, p5, p6);

    ASSERT_EQ(plane::get_planes_intersection(pl1, pl2).is_valid(), false);
}

TEST(Triangle_main, test_triangle_opers)
{
    point::point_t<long double> p1(1, 0, 0);
    point::point_t<long double> p2(1, 1, 0);
    point::point_t<long double> p3(1, 1, 1);

    segment::segment_t<long double> s1(p1, p2);
    segment::segment_t<long double> s2(p2, p3);
    segment::segment_t<long double> s3(p3, p1);

    triangle::triangle_t<long double> t1(s1, s2, s3);
    triangle::triangle_t<long double> t2(p1, p2, p3);

    ASSERT_EQ(t1, t2);
    ASSERT_EQ(t1.triag_plane_, t2.triag_plane_);

    point::point_t<long double> p4(1,  4, -6);
    point::point_t<long double> p5(1, -2,  10);
    point::point_t<long double> p6(1, -3,  5);
    triangle::triangle_t<long double> t3(p4, p5, p6);

    ASSERT_EQ(t1.triag_plane_, t3.triag_plane_);
}

TEST(Triangle_main, test_triangle_square)
{
    point::point_t<long double> p1(1, 2, 3);
    point::point_t<long double> p2(4, 5, 6);
    point::point_t<long double> p3(7, 8, 9);
    point::point_t<long double> p4(10, 11, 12);
    point::point_t<long double> p5(10, 11, 13);

    triangle::triangle_t<long double> t1(p1, p2, p3);
    triangle::triangle_t<long double> t2(p1, p2, p4);
    triangle::triangle_t<long double> t3(p2, p3, p4);

    ASSERT_NEAR(t1.square(), t2.square(), std::numeric_limits<long double>::epsilon());
    ASSERT_NEAR(t1.square(), t3.square(), std::numeric_limits<long double>::epsilon());

    triangle::triangle_t<long double> t4(p1, p2, p5);
    triangle::triangle_t<long double> t5(p2, p3, p5);

    ASSERT_NEAR(t4.square(), t5.square(), std::numeric_limits<long double>::epsilon());
    ASSERT_EQ(real_numbers::is_real_eq(t1.square(), t4.square()), false);
    ASSERT_EQ(real_numbers::is_real_eq(t2.square(), t5.square()), false);
}

TEST(Triangle_main, test_point_in_triangle)
{
    point::point_t<long double> p1(-3,  4,  6);
    point::point_t<long double> p2( 7,  8, -3);
    point::point_t<long double> p3( 2, -5,  1);

    triangle::triangle_t<long double> t1(p1, p2, p3);
    plane::plane_t<long double> triang_plane{-101, 5, -110, 337};

    ASSERT_EQ(t1.triag_plane_, triang_plane);
    ASSERT_EQ(t1.is_point_in(p1), true);
    ASSERT_EQ(t1.is_point_in(p2), true);
    ASSERT_EQ(t1.is_point_in(p3), true);

    ASSERT_EQ(t1.is_point_in((p1 + p2) / point::point_t<long double>{2}), true);
    ASSERT_EQ(t1.is_point_in((p1 + p2 + p3) / point::point_t<long double>{3}), true);

    point::point_t<long double> tp1(1, 2, 3);
    point::point_t<long double> tp2(1, 16, 2);
    point::point_t<long double> tp3(3, -2.4, 0.2);
    point::point_t<long double> tp4(2, -5, 1);

    ASSERT_EQ(t1.is_point_in(tp1), false);
    ASSERT_EQ(t1.is_point_in(tp2), false);
    ASSERT_EQ(t1.is_point_in(tp3), true);
    ASSERT_EQ(t1.is_point_in(tp4), true);
}

TEST(Triangle_main, test_line_intersect_edges)
{
    point::point_t<long double> p1(1,  2, 3);
    point::point_t<long double> p2(3,  4, 3);
    point::point_t<long double> p3(3, -1, 3);
    triangle::triangle_t<long double> t1(p1, p2, p3);

    point::point_t<long double> p4(2, -1,  6);
    point::point_t<long double> p5(-1, 3, -3);
    line::line_t<long double> l1(p4, p5);

    ASSERT_EQ(t1.is_line_intersect_edges(l1), true);

    point::point_t<long double> p6(1,  4, 3);
    point::point_t<long double> p7(3, -1, 0);
    line::line_t<long double> l2(p4, p5);

    ASSERT_EQ(t1.is_line_intersect_edges(l2), true);

    point::point_t<long double> p8(2, 2,  4.42);
    point::point_t<long double> p9(1, 1, -1);
    line::line_t<long double> l3(p8, p9);

    ASSERT_EQ(t1.is_line_intersect_edges(l3), false);
}

TEST(Triangle_main, test_triangles_intersect1)
{
    point::point_t<long double> p1(6, 0, 1);
    point::point_t<long double> p2(0, 6, 1);
    point::point_t<long double> p3(0, 0, 1);
    triangle::triangle_t<long double> t1(p1, p2, p3);

    point::point_t<long double> p4(3, 3, 1);
    point::point_t<long double> p5(6, 6, 1);
    point::point_t<long double> p6(6, 3, 1);
    triangle::triangle_t<long double> t2(p4, p5, p6);

    ASSERT_EQ(triangle::is_triangles_intersect(t1, t2), true);

    point::point_t<long double> p7(0, 4, 1);
    point::point_t<long double> p8(0, 5, 1);
    point::point_t<long double> p9(2, 4, 1);
    triangle::triangle_t<long double> t3(p7, p8, p9);
    ASSERT_EQ(triangle::is_triangles_intersect(t2, t3), false);
    ASSERT_EQ(triangle::is_triangles_intersect(t1, t3), true);
}

TEST(Triangle_main, test_triangles_intersect2)
{
    point::point_t<long double> p1(6, 0, 1);
    point::point_t<long double> p2(0, 6, 1);
    point::point_t<long double> p3(0, 0, 1);
    triangle::triangle_t<long double> t1(p1, p2, p3);

    point::point_t<long double> p4(-7, -2, 1);
    point::point_t<long double> p5( 0, -2, 1);
    point::point_t<long double> p6( 0,  8, 1);
    triangle::triangle_t<long double> t2(p4, p5, p6);
    ASSERT_EQ(triangle::is_triangles_intersect(t1, t2), true);

    point::point_t<long double> p7(-9, -2, 1);
    point::point_t<long double> p8( 0, -2, 1);
    point::point_t<long double> p9( 0,  8, 1);
    triangle::triangle_t<long double> t3(p7, p8, p9);
    ASSERT_EQ(triangle::is_triangles_intersect(t2, t3), true);
    ASSERT_EQ(triangle::is_triangles_intersect(t1, t3), true);
}

TEST(Triangle_main, test_triangles_intersect3)
{
    point::point_t<long double> p1(6, 0, 1);
    point::point_t<long double> p2(0, 6, 1);
    point::point_t<long double> p3(0, 0, 1);
    triangle::triangle_t<long double> t1(p1, p2, p3);

    point::point_t<long double> p4(3, 0, 1);
    point::point_t<long double> p5(7, 5, 1);
    point::point_t<long double> p6(7, 0, 1);
    triangle::triangle_t<long double> t2(p4, p5, p6);
    ASSERT_EQ(triangle::is_triangles_intersect(t1, t2), true);

    point::point_t<long double> p7(3, 0, 1);
    point::point_t<long double> p8(0, 3, 1);
    point::point_t<long double> p9(3, 3, 3);
    triangle::triangle_t<long double> t3(p7, p8, p9);

    ASSERT_EQ(triangle::is_triangles_intersect(t2, t3), true);
    ASSERT_EQ(triangle::is_triangles_intersect(t1, t3), true);
}

TEST(Triangle_main, test_triangles_intersect4)
{
    point::point_t<long double> p1(6, 0, 1);
    point::point_t<long double> p2(0, 6, 1);
    point::point_t<long double> p3(0, 0, 1);
    triangle::triangle_t<long double> t1(p1, p2, p3);

    point::point_t<long double> p4( 6, -1, 1);
    point::point_t<long double> p5(-1,  6, 1);
    point::point_t<long double> p6(-1, -1, 1);
    triangle::triangle_t<long double> t2(p4, p5, p6);
    ASSERT_EQ(triangle::is_triangles_intersect(t1, t2), true);

    point::point_t<long double> p7(0,  0,  1);
    point::point_t<long double> p8(7,  11, 1);
    point::point_t<long double> p9(10, 9,  1);
    triangle::triangle_t<long double> t3(p7, p8, p9);

    ASSERT_EQ(triangle::is_triangles_intersect(t2, t3), true);
    ASSERT_EQ(triangle::is_triangles_intersect(t1, t3), true);
}

TEST(Triangle_main, test_triangles_intersect5)
{
    point::point_t<long double> p1(6, 0, 1);
    point::point_t<long double> p2(0, 6, 1);
    point::point_t<long double> p3(0, 0, 1);
    triangle::triangle_t<long double> t1(p1, p2, p3);

    point::point_t<long double> p4( 2,  2, 1);
    point::point_t<long double> p5( 2, -3, 1);
    point::point_t<long double> p6(-2,  3, 1);
    triangle::triangle_t<long double> t2(p4, p5, p6);
    ASSERT_EQ(triangle::is_triangles_intersect(t1, t2), true);

    point::point_t<long double> p7( 2, 2, 1);
    point::point_t<long double> p8(-1, 2, 1);
    point::point_t<long double> p9( 2, 7, 1);
    triangle::triangle_t<long double> t3(p7, p8, p9);

    ASSERT_EQ(triangle::is_triangles_intersect(t2, t3), true);
    ASSERT_EQ(triangle::is_triangles_intersect(t1, t3), true);
}

TEST(Triangle_main, test_triangles_intersect6)
{
    point::point_t<long double> p1(6, 0, 1);
    point::point_t<long double> p2(0, 6, 1);
    point::point_t<long double> p3(0, 0, 1);
    triangle::triangle_t<long double> t1(p1, p2, p3);

    point::point_t<long double> p4(-1,  2, 1);
    point::point_t<long double> p5( 2, -1, 1);
    point::point_t<long double> p6( 4,  4, 1);
    triangle::triangle_t<long double> t2(p4, p5, p6);
    ASSERT_EQ(triangle::is_triangles_intersect(t1, t2), true);

    point::point_t<long double> p7(1,   2,    4);
    point::point_t<long double> p8(2,   1,    3);
    point::point_t<long double> p9(1.5, 1.5, -2);
    triangle::triangle_t<long double> t3(p7, p8, p9);
    ASSERT_EQ(triangle::is_triangles_intersect(t1, t3), true);
    ASSERT_EQ(triangle::is_triangles_intersect(t2, t3), true);
}

TEST(Triangle_main, test_triangles_intersect7)
{
    point::point_t<long double> p1(6, 0, 1);
    point::point_t<long double> p2(0, 6, 1);
    point::point_t<long double> p3(0, 0, 1);
    triangle::triangle_t<long double> t1(p1, p2, p3);

    point::point_t<long double> p4(-1,  2, 5);
    point::point_t<long double> p5( 5,  0, 1);
    point::point_t<long double> p6( 4, -2, 1);
    triangle::triangle_t<long double> t2(p4, p5, p6);
    ASSERT_EQ(triangle::is_triangles_intersect(t1, t2), true);

    point::point_t<long double> p7(1, 2, -5);
    point::point_t<long double> p8(1, 3, 1);
    point::point_t<long double> p9(3, 1, 1);
    triangle::triangle_t<long double> t3(p7, p8, p9);
    ASSERT_EQ(triangle::is_triangles_intersect(t1, t3), true);
    ASSERT_EQ(triangle::is_triangles_intersect(t2, t3), false);

    point::point_t<long double> p10(1, 2, -5);
    point::point_t<long double> p11(1, 3, 3);
    point::point_t<long double> p12(3, 1, 3);
    triangle::triangle_t<long double> t4(p10, p11, p12);
    ASSERT_EQ(triangle::is_triangles_intersect(t1, t4), true);

    ASSERT_EQ(triangle::is_triangles_intersect(t3, t4), true);
}

TEST(Triangle_main, test_triangles_intersect8)
{
    point::point_t<long double> p1(6, 0, 1);
    point::point_t<long double> p2(0, 6, 1);
    point::point_t<long double> p3(0, 0, 1);
    triangle::triangle_t<long double> t1(p1, p2, p3);

    point::point_t<long double> p4(2, 2, 2);
    point::point_t<long double> p5(2, 0, 0);
    point::point_t<long double> p6(5, 5, 1);
    triangle::triangle_t<long double> t2(p4, p5, p6);
    ASSERT_EQ(triangle::is_triangles_intersect(t1, t2), true);

    point::point_t<long double> p7(2, 3,  4);
    point::point_t<long double> p8(3, 2, -1);
    point::point_t<long double> p9(7, 7,  2);
    triangle::triangle_t<long double> t3(p7, p8, p9);
    ASSERT_EQ(triangle::is_triangles_intersect(t1, t3), true);

    point::point_t<long double> p10(-100, 3,  100);
    point::point_t<long double> p11( 100, 3,  100);
    point::point_t<long double> p12( 3,   3, -100);
    triangle::triangle_t<long double> t4(p10, p11, p12);

    ASSERT_EQ(triangle::is_triangles_intersect(t1, t4), true);
}

TEST(Triangle_main, test_triangles_intersect9)
{
    point::point_t<long double> p1(1, 1, 0);
    point::point_t<long double> p2(3, 1, 0);
    point::point_t<long double> p3(1, 1, 2);
    triangle::triangle_t<long double> t1(p1, p2, p3);

    point::point_t<long double> p4(2, 2, 2);
    point::point_t<long double> p5(1, 1, 2);
    point::point_t<long double> p6(2, 1, 2);
    triangle::triangle_t<long double> t2(p4, p5, p6);

    ASSERT_EQ(triangle::is_triangles_intersect(t1, t2), true);

    point::point_t<long double> p7(0, -1, -1);
    point::point_t<long double> p8(2, -1, -1);
    point::point_t<long double> p9(0, -1,  2);
    triangle::triangle_t<long double> t3(p7, p8, p9);

    point::point_t<long double> p10(2, 2, 2);
    point::point_t<long double> p11(1, 1, 2);
    point::point_t<long double> p12(2, 1, 2);
    triangle::triangle_t<long double> t4(p10, p11, p12);

    ASSERT_EQ(triangle::is_triangles_intersect(t3, t4), false);
}

TEST(Triangle_main, test_triangles_intersect10)
{
    point::point_t<long double> p1( 1, 1, -2);
    point::point_t<long double> p2(-2, 0, 4);
    point::point_t<long double> p3( 0, 2, 4);
    triangle::triangle_t<long double> t1(p1, p2, p3);

    point::point_t<long double> p4( 0,  0, 0);
    point::point_t<long double> p5(-1,  0, 0);
    point::point_t<long double> p6( 0, -1, 0);
    triangle::triangle_t<long double> t2(p4, p5, p6);

    ASSERT_EQ(triangle::is_triangles_intersect(t1, t2), false);

    point::point_t<long double> p7(0, 0, 0);
    point::point_t<long double> p8(1, 0, 0);
    point::point_t<long double> p9(0, 1, 0);
    triangle::triangle_t<long double> t3(p7, p8, p9);

    point::point_t<long double> p10(0, 0, 0);
    point::point_t<long double> p11(0, 3, 3);
    point::point_t<long double> p12(0, 0, 3);
    triangle::triangle_t<long double> t4(p10, p11, p12);

    ASSERT_EQ(triangle::is_triangles_intersect(t3, t4), true);
}

TEST(Triangle_main, test_triangles_intersect11)
{
    point::point_t<long double> p1(0, 0, 0);
    point::point_t<long double> p2(0, 5, 0);
    point::point_t<long double> p3(4, 0, 0);
    triangle::triangle_t<long double> t1(p1, p2, p3);

    point::point_t<long double> p4(3, 1.5, 0);
    point::point_t<long double> p5(3, 5,   0);
    point::point_t<long double> p6(7, 1.5, 0);
    triangle::triangle_t<long double> t2(p4, p5, p6);

    ASSERT_EQ(triangle::is_triangles_intersect(t1, t2), false);

    point::point_t<long double> p7(1, 0, 0);
    point::point_t<long double> p8(0, 1, 0);
    point::point_t<long double> p9(0, 0, 1);
    triangle::triangle_t<long double> t3(p7, p8, p9);

    point::point_t<long double> p10(0, 0, 0);
    point::point_t<long double> p11(5, 5, 0);
    point::point_t<long double> p12(5, 5, 10);
    triangle::triangle_t<long double> t4(p10, p11, p12);

    point::point_t<long double> p13(0.5, 0, 0);
    point::point_t<long double> p14(0,   0, 0);
    point::point_t<long double> p15(0,   0, 0.5);
    triangle::triangle_t<long double> t5(p13, p14, p15);

    ASSERT_EQ(triangle::is_triangles_intersect(t3, t5), false);
    ASSERT_EQ(triangle::is_triangles_intersect(t3, t4), true);
    ASSERT_EQ(triangle::is_triangles_intersect(t4, t5), true);
}

TEST(Triangle_main, test_triangles_intersect12)
{
    point::point_t<long double> p1(0, 0, 0);
    point::point_t<long double> p2(2, 0, 0);
    point::point_t<long double> p3(0, 2, 0);
    triangle::triangle_t<long double> t1(p1, p2, p3);

    point::point_t<long double> p4(1,  0,  1);
    point::point_t<long double> p5(1,  0, -1);
    point::point_t<long double> p6(1, -2,  0);
    triangle::triangle_t<long double> t2(p4, p5, p6);

    ASSERT_EQ(triangle::is_triangles_intersect(t1, t2), true);

    point::point_t<long double> p7(1, 0,  1);
    point::point_t<long double> p8(1, 0, -1);
    point::point_t<long double> p9(5, 0,  0);
    triangle::triangle_t<long double> t3(p7, p8, p9);

    ASSERT_EQ(triangle::is_triangles_intersect(t1, t3), true);
    ASSERT_EQ(triangle::is_triangles_intersect(t2, t3), true);
}

TEST(Triangle_main, test_triangles_intersect13)
{
    point::point_t<long double> p1(0, 0, 0);
    point::point_t<long double> p2(1, 0, 0);
    point::point_t<long double> p3(0, 1, 0);
    triangle::triangle_t<long double> t1(p1, p2, p3);

    point::point_t<long double> p4(0, 0,  0.01);
    point::point_t<long double> p5(5, 5,  0.01);
    point::point_t<long double> p6(5, 5, -0.09);
    triangle::triangle_t<long double> t2(p4, p5, p6);

    ASSERT_EQ(triangle::is_triangles_intersect(t1, t2), true);

    point::point_t<long double> p7(0, -0.3,  0.01);
    point::point_t<long double> p8(5,  5,    0.01);
    point::point_t<long double> p9(5,  5,   -0.09);
    triangle::triangle_t<long double> t3(p7, p8, p9);

    ASSERT_EQ(triangle::is_triangles_intersect(t1, t3), true);
}

TEST(Triangle_main, test_triangles_intersect14)
{
    point::point_t<long double> p1(0, 0, 0);
    point::point_t<long double> p2(1, 0, 0);
    point::point_t<long double> p3(0, 1, 0);
    triangle::triangle_t<long double> t1(p1, p2, p3);

    point::point_t<long double> p4(5, 5, 5);
    point::point_t<long double> p5(5, 5, 5);
    point::point_t<long double> p6(5, 5, 5);
    triangle::triangle_t<long double> t2(p4, p5, p6);

    ASSERT_EQ(triangle::is_triangles_intersect(t1, t2), false);

    point::point_t<long double> p7(0,  0.5, -0.5);
    point::point_t<long double> p8(0,  0.5,  0.5);
    point::point_t<long double> p9(-1, 0,    0);
    triangle::triangle_t<long double> t3(p7, p8, p9);

    ASSERT_EQ(triangle::is_triangles_intersect(t2, t3), false);
    ASSERT_EQ(triangle::is_triangles_intersect(t1, t3), true);
    ASSERT_EQ(triangle::is_triangles_intersect(t3, t1), true);
}

TEST(Triangle_main, test_triangles_point)
{
    point::point_t<long double> p1(6, 0, 1);
    point::point_t<long double> p2(0, 6, 1);
    point::point_t<long double> p3(0, 0, 1);
    triangle::triangle_t<long double> t1(p1, p2, p3);

    point::point_t<long double> p4(3, 3, 1);
    point::point_t<long double> p5(3, 3, 1);
    point::point_t<long double> p6(3, 3, 1);
    triangle::triangle_t<long double> t2(p4, p5, p6);

    ASSERT_EQ(t2.is_triangle_is_point(), true);
    ASSERT_EQ(triangle::is_triangles_intersect(t1, t2), true);

    point::point_t<long double> p7(0, 0, 0);
    point::point_t<long double> p8(0, 0, 0);
    point::point_t<long double> p9(0, 0, 0);
    triangle::triangle_t<long double> t3(p7, p8, p9);

    ASSERT_EQ(t3.is_triangle_is_point(), true);
    ASSERT_EQ(triangle::is_triangles_intersect(t1, t3), false);
    ASSERT_EQ(triangle::is_triangles_intersect(t2, t3), false);
    ASSERT_EQ(triangle::is_triangles_intersect(t3, t3), true);
}

TEST(Triangle_main, test_triangles_lines)
{
    point::point_t<long double> p1(6, 0, 1);
    point::point_t<long double> p2(0, 6, 1);
    point::point_t<long double> p3(0, 0, 1);
    triangle::triangle_t<long double> t1(p1, p2, p3);

    point::point_t<long double> p4(3, 3,  4);
    point::point_t<long double> p5(3, 3, -2);
    point::point_t<long double> p6(3, 3,  0);
    triangle::triangle_t<long double> t2(p4, p5, p6);

    ASSERT_EQ(t2.is_triangle_is_segment(), true);
    ASSERT_EQ(triangle::is_triangles_intersect(t1, t2), true);

    point::point_t<long double> p7(1, 1,  2);
    point::point_t<long double> p8(1, 1, -2);
    point::point_t<long double> p9(1, 1, -1);
    triangle::triangle_t<long double> t3(p7, p8, p9);

    point::point_t<long double> p10(1, 1,  1);
    point::point_t<long double> p11(1, 1, -1);
    point::point_t<long double> p12(1, 1,  0);
    triangle::triangle_t<long double> t4(p10, p11, p12);

    ASSERT_EQ(t3.is_triangle_is_segment(), true);
    ASSERT_EQ(t4.is_triangle_is_segment(), true);
    ASSERT_EQ(triangle::is_triangles_intersect(t3, t4), true);
}

TEST(Octree_main, test_octree_intersect1)
{
    point::point_t<long double> p1(0, 0, 0);
    point::point_t<long double> p2(1, 0, 0);
    point::point_t<long double> p3(0, 1, 0);
    triangle::triangle_t<long double> t1(p1, p2, p3);

    point::point_t<long double> p4(5, 5, 5);
    point::point_t<long double> p5(5, 5, 5);
    point::point_t<long double> p6(5, 5, 5);
    triangle::triangle_t<long double> t2(p4, p5, p6);

    point::point_t<long double> p7(0,  0.5, -0.5);
    point::point_t<long double> p8(0,  0.5,  0.5);
    point::point_t<long double> p9(-1, 0,    0);
    triangle::triangle_t<long double> t3(p7, p8, p9);

    int count = 3;
    std::vector<triangle::triangle_t<long double>> triangles = {t1, t2, t3};

    octree::octree_t<long double> octree(count, triangles.begin(), triangles.end());
    std::set<int> ans = octree.get_set_intersecting_triangles();
    
    ASSERT_EQ(ans.find(0) != ans.end(), true);
    ASSERT_EQ(ans.find(2) != ans.end(), true);
}

TEST(Octree_main, test_octree_intersect2)
{
    point::point_t<long double> p1(1, 0, 0);
    point::point_t<long double> p2(0, 1, 0);
    point::point_t<long double> p3(0, 0, 1);
    triangle::triangle_t<long double> t1(p1, p2, p3);

    point::point_t<long double> p4(-1,   -1,   0.5);
    point::point_t<long double> p5(-0.5, -0.5, 0.5);
    point::point_t<long double> p6( 0.3,  0.3, 0.5);
    triangle::triangle_t<long double> t2(p4, p5, p6);

    point::point_t<long double> p7(-1,   -1,    0.25);
    point::point_t<long double> p8( 0,    0,    0.25);
    point::point_t<long double> p9( 0.25, 0.25, 0.35);
    triangle::triangle_t<long double> t3(p7, p8, p9);

    const int count = 3;
    std::vector<triangle::triangle_t<long double>> triangles = {t1, t2, t3};

    octree::octree_t<long double> octree(count, triangles.begin(), triangles.end());
    std::set<int> ans = octree.get_set_intersecting_triangles();
    
    ASSERT_EQ(ans.find(0) != ans.end(), true);
    ASSERT_EQ(ans.find(1) != ans.end(), true);
    ASSERT_EQ(ans.find(2) != ans.end(), false);
}

TEST(Octree_main, test_octree_intersect3)
{
    point::point_t<long double> p1(0,   0, 0);
    point::point_t<long double> p3(-1,  0, 0);
    point::point_t<long double> p2( 0, -1, 0);
    triangle::triangle_t<long double> t1(p1, p2, p3);

    point::point_t<long double> p4(-1,    0,   0.5);
    point::point_t<long double> p5(-0.2, -0.4, 0.15);
    point::point_t<long double> p6(-0.1, -0.45, 0.1);
    triangle::triangle_t<long double> t2(p4, p5, p6);

    point::point_t<long double> p7(0, -0.5, -0.2);
    point::point_t<long double> p8(0, -0.5,  0.2);
    point::point_t<long double> p9(1,  0,    0);
    triangle::triangle_t<long double> t3(p7, p8, p9);

    const int count = 3;
    std::vector<triangle::triangle_t<long double>> triangles = {t1, t2, t3};

    octree::octree_t<long double> octree(count, triangles.begin(), triangles.end());
    std::set<int> ans = octree.get_set_intersecting_triangles();
    
    ASSERT_EQ(ans.find(0) != ans.end(), true);
    ASSERT_EQ(ans.find(1) != ans.end(), false);
    ASSERT_EQ(ans.find(2) != ans.end(), true);
}

TEST(Octree_main, test_octree_intersect4_lines)
{
    point::point_t<long double> p1(0, 0, 0);
    point::point_t<long double> p3(0, 0, 0);
    point::point_t<long double> p2(0, 0, 0);
    triangle::triangle_t<long double> t1(p1, p2, p3);

    point::point_t<long double> p4(1.1, 1.1, 1.1);
    point::point_t<long double> p5(1.1, 1.1, 1.1);
    point::point_t<long double> p6(2,   2,   2);
    triangle::triangle_t<long double> t2(p4, p5, p6);

    point::point_t<long double> p7(1.05, 1.05, 1.05);
    point::point_t<long double> p8(1.05, 1.05, 0);
    point::point_t<long double> p9(1.05, 1.05, 2);
    triangle::triangle_t<long double> t3(p7, p8, p9);

    const int count = 3;
    std::vector<triangle::triangle_t<long double>> triangles = {t1, t2, t3};

    octree::octree_t<long double> octree(count, triangles.begin(), triangles.end());
    std::set<int> ans = octree.get_set_intersecting_triangles();
    
    ASSERT_EQ(ans.find(0) != ans.end(), false);
    ASSERT_EQ(ans.find(1) != ans.end(), false);
    ASSERT_EQ(ans.find(2) != ans.end(), false);
}

TEST(Octree_main, test_octree_intersect5_points)
{
    point::point_t<long double> p1(0, 0, 0);
    point::point_t<long double> p3(1, 1, 1);
    point::point_t<long double> p2(0, 0, 0);
    triangle::triangle_t<long double> t1(p1, p2, p3);

    const int count = 2;
    std::vector<triangle::triangle_t<long double>> triangles = {t1, t1};

    octree::octree_t<long double> octree(count, triangles.begin(), triangles.end());
    std::set<int> ans = octree.get_set_intersecting_triangles();
    
    ASSERT_EQ(ans.find(0) != ans.end(), true);
    ASSERT_EQ(ans.find(1) != ans.end(), true);
}

TEST(Octree_main, test_octree_intersect6_points)
{
    point::point_t<long double> p1(0, 0, 0);
    triangle::triangle_t<long double> t1(p1, p1, p1);

    point::point_t<long double> p2(1, 1, 1);
    triangle::triangle_t<long double> t2(p2, p2, p2);

    const int count = 3;
    std::vector<triangle::triangle_t<long double>> triangles = {t1, t1, t2};

    octree::octree_t<long double> octree(count, triangles.begin(), triangles.end());
    std::set<int> ans = octree.get_set_intersecting_triangles();
    
    ASSERT_EQ(ans.find(0) != ans.end(), true);
    ASSERT_EQ(ans.find(1) != ans.end(), true);
    ASSERT_EQ(ans.find(2) != ans.end(), false);
}

TEST(Octree_main, test_octree_intersect5_points_lines1)
{
    point::point_t<long double> p1(0, 0, 0);
    point::point_t<long double> p2(1, 1, 1);
    triangle::triangle_t<long double> t1(p1, p1, p2);

    point::point_t<long double> p3(2,   2,   2);
    point::point_t<long double> p4(2.5, 2.5, 2.5);
    triangle::triangle_t<long double> t2(p3, p4, p4);

    point::point_t<long double> p5(1.5, 1.5, 1.5);
    triangle::triangle_t<long double> t3(p5, p5, p5);

    point::point_t<long double> p6(3, 3, 3);
    triangle::triangle_t<long double> t4(p6, p6, p6);

    const int count = 4;
    std::vector<triangle::triangle_t<long double>> triangles = {t1, t2, t3, t4};

    octree::octree_t<long double> octree(count, triangles.begin(), triangles.end());
    std::set<int> ans = octree.get_set_intersecting_triangles();
    
    ASSERT_EQ(ans.find(0) != ans.end(), false);
    ASSERT_EQ(ans.find(1) != ans.end(), false);
    ASSERT_EQ(ans.find(2) != ans.end(), false);
    ASSERT_EQ(ans.find(3) != ans.end(), false);
}

TEST(Octree_main, test_octree_intersect5_points_lines2)
{
    point::point_t<long double> p1(0, 0, 0);
    point::point_t<long double> p2(1, 1, 1);
    triangle::triangle_t<long double> t1(p1, p1, p2);

    point::point_t<long double> p3(2,   2,   2);
    point::point_t<long double> p4(2.5, 2.5, 2.5);
    triangle::triangle_t<long double> t2(p3, p4, p4);

    point::point_t<long double> p5(1, 1, 1);
    triangle::triangle_t<long double> t3(p5, p5, p5);

    point::point_t<long double> p6(2.25, 2.25, 2.25);
    triangle::triangle_t<long double> t4(p6, p6, p6);

    const int count = 4;
    std::vector<triangle::triangle_t<long double>> triangles = {t1, t2, t3, t4};

    octree::octree_t<long double> octree(count, triangles.begin(), triangles.end());
    std::set<int> ans = octree.get_set_intersecting_triangles();
    
    ASSERT_EQ(ans.find(0) != ans.end(), true);
    ASSERT_EQ(ans.find(1) != ans.end(), true);
    ASSERT_EQ(ans.find(2) != ans.end(), true);
    ASSERT_EQ(ans.find(3) != ans.end(), true);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}