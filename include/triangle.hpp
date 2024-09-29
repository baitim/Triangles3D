#pragma once

#include <vector>
#include "plane.hpp"

namespace triangle {
    using namespace plane;

    template <typename T>
    T triangle_square(const point_t<T>& a, const point_t<T>& b, const point_t<T>& c);

    template <typename T = double>
    struct triangle_line_inter_coefs_t final {
        coefs_t<T> k_[3]{};
    };

    template <typename T = double>
    struct triangle_t final {
        point_t<T> a_;
        point_t<T> b_;
        point_t<T> c_;

        plane_t<T> triag_plane_;

        triangle_t() : a_(), b_(), c_(), triag_plane_() {}
        triangle_t(segment_t<T> ab, segment_t<T> bc, segment_t<T> ca) : a_(ab.x_), b_(bc.x_),
                                                                        c_(ca.x_),
                                                                        triag_plane_(ab, bc, ca) {}

        triangle_t(point_t<T> a, point_t<T> b, point_t<T> c) : a_(a), b_(b), c_(c), triag_plane_(a, b, c) {}
        triangle_t(const triangle_t& triangle) : a_(triangle.a_), b_(triangle.b_), c_(triangle.c_),
                                                 triag_plane_(a_, b_, c_) {}

        T get_min_x() const { return std::min(a_.x_, std::min(b_.x_, c_.x_)); }
        T get_max_x() const { return std::max(a_.x_, std::max(b_.x_, c_.x_)); }
        T get_min_y() const { return std::min(a_.y_, std::min(b_.y_, c_.y_)); }
        T get_max_y() const { return std::max(a_.y_, std::max(b_.y_, c_.y_)); }
        T get_min_z() const { return std::min(a_.z_, std::min(b_.z_, c_.z_)); }
        T get_max_z() const { return std::max(a_.z_, std::max(b_.z_, c_.z_)); }

        T square() const { 
            return triangle_square(a_, b_, c_); 
        }

        bool is_point_in(const point_t<T>& p) const {
            T S  = triangle_square(a_, b_, c_);

            T S1 = triangle_square(p,  a_, b_);
            if (is_reals_gt(S1, S))
                return false;

            T S2 = triangle_square(p,  a_, c_);
            if (is_reals_gt(S2, S))
                return false;

            T S3 = triangle_square(p,  b_, c_);
            if (is_reals_gt(S3, S))
                return false;
            
            if (is_reals_eq(S1 + S2 + S3, S))
                return true;

            return false;
        }

        bool is_valid() const {
            return (a_.is_valid() &&
                    b_.is_valid() &&
                    c_.is_valid() &&
                    triag_plane_.is_valid());
        }

        triangle_line_inter_coefs_t<T> get_line_intersect_edges(const line_t<T>& line) const {
            if (!line.is_valid() || !is_valid())
                return triangle_line_inter_coefs_t<T>{};

            segment_t<T> segs[3] = {{a_, b_}, {b_, c_}, {c_, a_}};
            triangle_line_inter_coefs_t<T> coefs;
            for (int i = 0; i < 3; ++i)
                coefs.k_[i] = segs[i].get_line_intersect(line);

            return coefs;
        }

        bool is_line_intersect_edges(const line_t<T>& line) const {
            triangle_line_inter_coefs_t<T> coefs = get_line_intersect_edges(line);
            for (int i = 0; i < 3; ++i)
                if (coefs.k_[i].is_valid_)
                    return true;

            return false;
        }

        bool is_triangle_vertexes_inside(const triangle_t<T>& t) const {
            if (is_point_in(t.a_) ||
                is_point_in(t.b_) ||
                is_point_in(t.c_))
                return true;

            return false;
        }

        bool is_segment_intersect_edges(const segment_t<T>& s) const {
            segment_t<T> curr[3] = {segment_t<T>(a_, b_),
                                    segment_t<T>(b_, c_),
                                    segment_t<T>(c_, a_)};

            for (int i = 0; i < 3; ++i)
                if (curr[i].is_segment_intersect(s))
                    return true;

            return false;
        }

        bool is_edges_intersect_edges(const triangle_t<T>& tr) const {
            segment_t<T> t[3] = {segment_t<T>(tr.a_, tr.b_),
                                 segment_t<T>(tr.b_, tr.c_),
                                 segment_t<T>(tr.c_, tr.a_)};

            for (int i = 0; i < 3; ++i)
                if (is_segment_intersect_edges(t[i]))
                    return true;

            return false;
        }

        bool is_segment_intersect_triangle(const segment_t<T>& s) const {
            line_t<T> line = line_t<T>(s.x_, s.y_ - s.x_);

            point_t<T> p = triag_plane_.get_intersect_line(line);
            if (is_point_in(p))
                return true;

            return false;
        }

        bool is_triangle_is_point() const {
            return ((a_ == b_) && (b_ == c_));
        }

        bool is_triangle_is_segment() const {
            return is_points_segment(a_, b_, c_);
        }

        segment_t<T> triangle_to_segment() const {
            if (!is_triangle_is_segment())
                return segment_t<T>();

            return segment_t<T>(std::min(a_, std::min(b_, c_)),
                                std::max(a_, std::max(b_, c_)));
        }
    };

    template <typename T>
    bool is_line_intersect_triangle(const triangle_t<T>& a, const line_t<T>& line) {
        if (a.triag_plane_.norm().normal() == line.v_.norm()) {
            if (a.triag_plane_.is_point_in(line.x_))
                return true;
            else
                return false;
        }

        point_t<T> p = a.triag_plane_.get_intersect_line(line);
        if (a.is_point_in(p))
            return true;

        return false;
    }

    template <typename T>
    bool is_triangles_intersect_in_plane(const triangle_t<T>& a, const triangle_t<T>& b) {
        if (a.is_triangle_vertexes_inside(b) ||
            b.is_triangle_vertexes_inside(a))
            return true;

        if (a.is_edges_intersect_edges(b))
            return true;

        return false;
    }

    template <typename T>
    bool is_segments_coefs_intersect(const triangle_line_inter_coefs_t<T>& coefs_a,
                                     const triangle_line_inter_coefs_t<T>& coefs_b) {

        std::vector<segment_t<T>> coefs_a_range;
        std::vector<segment_t<T>> coefs_b_range;

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 3; ++j) {
                if (coefs_a.k_[i].is_valid_ && coefs_a.k_[j].is_valid_)
                    coefs_a_range.push_back(segment_t<T>{coefs_a.k_[i].k_, coefs_a.k_[j].k_});

                if (coefs_b.k_[i].is_valid_ && coefs_b.k_[j].is_valid_)
                    coefs_b_range.push_back(segment_t<T>{coefs_b.k_[i].k_, coefs_b.k_[j].k_});
            }
        }

        for (int i = 0, end1 = coefs_a_range.size(); i < end1; ++i) {
            for (int j = 0, end2 = coefs_b_range.size(); j < end2; ++j) {
                if (coefs_a_range[i].is_point_in(coefs_b_range[j].x_) ||
                    coefs_a_range[i].is_point_in(coefs_b_range[j].y_) ||
                    coefs_b_range[j].is_point_in(coefs_a_range[i].x_) ||
                    coefs_b_range[j].is_point_in(coefs_a_range[i].y_))
                    return true;
            }
        }
        
        return false;
    }

    template <typename T>
    bool is_intersect_simple_figure(const triangle_t<T>& a, const triangle_t<T>& b) {
        segment_t<T> segment_a = a.triangle_to_segment();
        segment_t<T> segment_b = b.triangle_to_segment();

        if (a.is_triangle_is_point() && b.is_triangle_is_point())   
            return (a.a_ == b.b_);

        if (a.is_triangle_is_point()) {
            if (b.is_triangle_is_segment())
                return segment_b.is_point_in(a.a_);
            else
                return b.is_point_in(a.a_);
        }

        if (b.is_triangle_is_point()) {
            if (a.is_triangle_is_segment())
                return segment_a.is_point_in(b.a_);
            else
                return a.is_point_in(b.a_);
        }

        if (a.is_triangle_is_segment() &&
            b.is_triangle_is_segment())
            return segment_a.is_segment_intersect(segment_b);

        if (a.is_triangle_is_segment())
            return b.is_segment_intersect_triangle(segment_a);

        if (b.is_triangle_is_segment())
            return a.is_segment_intersect_triangle(segment_b);

        return false;
    }

    template <typename T>
    bool operator==(const triangle_t<T>& a, const triangle_t<T>& b) {
        return (a.a_ == b.a_ &&
                a.b_ == b.b_ &&
                a.c_ == b.c_);
    }

    template <typename T>
    bool is_on_one_side(const plane_t<T>& pl, const triangle_t<T>& t) {
        T pl_norm_dot_a = pl.check_point_dot_plane(t.a_);
        T pl_norm_dot_b = pl.check_point_dot_plane(t.b_);
        T pl_norm_dot_c = pl.check_point_dot_plane(t.c_);

        if (is_reals_gt(pl_norm_dot_a, T{0}) &&
            is_reals_gt(pl_norm_dot_b, T{0}) &&
            is_reals_gt(pl_norm_dot_c, T{0}))
            return true;

        if (is_reals_lt(pl_norm_dot_a, T{0}) &&
            is_reals_lt(pl_norm_dot_b, T{0}) &&
            is_reals_lt(pl_norm_dot_c, T{0}))
            return true;

        return false;
    }

    template <typename T>
    bool is_triangles_intersect(const triangle_t<T>& a, const triangle_t<T>& b) {
        if (a == b)
            return true;

        plane_t<T> plane_a(a.a_, a.b_, a.c_);
        if (is_on_one_side(plane_a, b))
            return false;

        plane_t<T> plane_b(b.a_, b.b_, b.c_);

        if (plane_a == plane_b &&
            plane_a.is_valid() &&
            plane_b.is_valid())
            return is_triangles_intersect_in_plane(a, b);

        if (is_planes_parallel(plane_a, plane_b) &&
            plane_a.is_valid() &&
            plane_b.is_valid())
            return false;

        line_t<T> line_inter = get_planes_intersection(plane_a, plane_b);
        if (!line_inter.v_.is_valid())
            return is_intersect_simple_figure(a, b);


        triangle_line_inter_coefs_t<T> coefs_a = a.get_line_intersect_edges(line_inter);
        triangle_line_inter_coefs_t<T> coefs_b = b.get_line_intersect_edges(line_inter);
        if(is_segments_coefs_intersect(coefs_a, coefs_b))
            return true;

        return false;
    }

    template <typename T>
    T triangle_square(const point_t<T>& a, const point_t<T>& b, const point_t<T>& c) {
        return cross_product(b - a, c - a).length() / 2;
    }

    template <typename T>
    std::istream& operator>>(std::istream& is, triangle_t<T>& t) {
        point_t<T> a, b, c;
        is >> a >> b >> c;
        t = (triangle_t<T>){a, b, c};
        return is;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const triangle_t<T>& t) {
        os << print_lyellow("Triangle(") << t.a_ << print_lyellow(",") << t.b_ <<
              print_lyellow(",")         << t.c_ << print_lyellow(")");
        return os;
    }
}