#pragma once

#include <vector>
#include "plane.hpp"

namespace triangle {
    using namespace plane;

    double triangle_square(const point_t& a, const point_t& b, const point_t& c);

    struct triangle_line_inter_coefs_t final {
        coefs_t k_[3]{};
    };

    struct triangle_t final {
        point_t a_;
        point_t b_;
        point_t c_;

        plane_t triag_plane_;

        triangle_t() : a_(), b_(), c_(), triag_plane_() {}
        triangle_t(segment_t ab, segment_t bc, segment_t ca) : a_(ab.x_), b_(bc.x_),
                                                               c_(ca.x_),
                                                               triag_plane_(ab, bc, ca) {}

        triangle_t(point_t a, point_t b, point_t c) : a_(a), b_(b), c_(c), triag_plane_(a, b, c) {}

        double get_min_x() const { return std::min(a_.x_, std::min(b_.x_, c_.x_)); }
        double get_max_x() const { return std::max(a_.x_, std::max(b_.x_, c_.x_)); }
        double get_min_y() const { return std::min(a_.y_, std::min(b_.y_, c_.y_)); }
        double get_max_y() const { return std::max(a_.y_, std::max(b_.y_, c_.y_)); }
        double get_min_z() const { return std::min(a_.z_, std::min(b_.z_, c_.z_)); }
        double get_max_z() const { return std::max(a_.z_, std::max(b_.z_, c_.z_)); }

        double square() const { 
            return triangle_square(a_, b_, c_); 
        }

        bool is_point_in(const point_t& p) const {
            double S  = triangle_square(a_, b_, c_);

            double S1 = triangle_square(p,  a_, b_);
            if (is_double_gt(S1, S))
                return false;

            double S2 = triangle_square(p,  a_, c_);
            if (is_double_gt(S2, S))
                return false;

            double S3 = triangle_square(p,  b_, c_);
            if (is_double_gt(S3, S))
                return false;
            
            if (is_double_eq(S1 + S2 + S3, S))
                return true;

            return false;
        }

        bool is_valid() const {
            return (a_.is_valid() &&
                    b_.is_valid() &&
                    c_.is_valid() &&
                    triag_plane_.is_valid());
        }

        triangle_line_inter_coefs_t get_line_intersect_edges(const line_t& line) const {
            if (!line.is_valid() || !is_valid())
                return triangle_line_inter_coefs_t{};

            segment_t segs[3] = {{a_, b_}, {b_, c_}, {c_, a_}};
            triangle_line_inter_coefs_t coefs;
            for (int i = 0; i < 3; ++i)
                coefs.k_[i] = segs[i].get_line_intersect(line);

            return coefs;
        }

        bool is_line_intersect_edges(const line_t& line) const {
            triangle_line_inter_coefs_t coefs = get_line_intersect_edges(line);
            for (int i = 0; i < 3; ++i)
                if (coefs.k_[i].is_valid_)
                    return true;

            return false;
        }

        bool is_triangle_vertexes_inside(const triangle_t& t) const {
            if (is_point_in(t.a_) ||
                is_point_in(t.b_) ||
                is_point_in(t.c_))
                return true;

            return false;
        }

        bool is_segment_intersect_edges(const segment_t& s) const {
            segment_t curr[3] = {segment_t(a_, b_),
                                 segment_t(b_, c_),
                                 segment_t(c_, a_)};

            for (int i = 0; i < 3; ++i)
                if (curr[i].is_segment_intersect(s))
                    return true;

            return false;
        }

        bool is_edges_intersect_edges(const triangle_t& tr) const {
            segment_t t[3] = {segment_t(tr.a_, tr.b_),
                              segment_t(tr.b_, tr.c_),
                              segment_t(tr.c_, tr.a_)};

            for (int i = 0; i < 3; ++i)
                if (is_segment_intersect_edges(t[i]))
                    return true;

            return false;
        }

        bool is_segment_intersect_triangle(const segment_t& s) const {
            line_t line = line_t(s.x_, s.y_ - s.x_);

            point_t p = triag_plane_.get_intersect_line(line);
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

        segment_t triangle_to_segment() const {
            if (!is_triangle_is_segment())
                return segment_t();

            return segment_t(std::min(a_, std::min(b_, c_)),
                             std::max(a_, std::max(b_, c_)));
        }
    };

    bool is_line_intersect_triangle(const triangle_t& a, const line_t& line) {
        if (a.triag_plane_.norm().normal() == line.v_.norm()) {
            if (a.triag_plane_.is_point_in(line.x_))
                return true;
            else
                return false;
        }

        point_t p = a.triag_plane_.get_intersect_line(line);
        if (a.is_point_in(p))
            return true;

        return false;
    }

    bool is_triangles_intersect_in_plane(const triangle_t& a, const triangle_t& b) {
        if (a.is_triangle_vertexes_inside(b) ||
            b.is_triangle_vertexes_inside(a))
            return true;

        if (a.is_edges_intersect_edges(b))
            return true;

        return false;
    }

    bool is_segments_coefs_intersect(const triangle_line_inter_coefs_t& coefs_a,
                                     const triangle_line_inter_coefs_t& coefs_b) {

        std::vector<segment_t> coefs_a_range;
        std::vector<segment_t> coefs_b_range;

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 3; ++j) {
                if (coefs_a.k_[i].is_valid_ && coefs_a.k_[j].is_valid_)
                    coefs_a_range.push_back(segment_t{coefs_a.k_[i].k_, coefs_a.k_[j].k_});

                if (coefs_b.k_[i].is_valid_ && coefs_b.k_[j].is_valid_)
                    coefs_b_range.push_back(segment_t{coefs_b.k_[i].k_, coefs_b.k_[j].k_});
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

    bool is_intersect_simple_figure(const triangle_t& a, const triangle_t& b) {
        segment_t segment_a = a.triangle_to_segment();
        segment_t segment_b = b.triangle_to_segment();

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

    bool operator==(const triangle_t& a, const triangle_t& b) {
        return (a.a_ == b.a_ &&
                a.b_ == b.b_ &&
                a.c_ == b.c_);
    }

    bool is_on_one_side(const plane_t& pl, const triangle_t& t) {
        double pl_norm_dot_a = pl.check_point_dot_plane(t.a_);
        double pl_norm_dot_b = pl.check_point_dot_plane(t.b_);
        double pl_norm_dot_c = pl.check_point_dot_plane(t.c_);

        if (is_double_gt(pl_norm_dot_a, 0) &&
            is_double_gt(pl_norm_dot_b, 0) &&
            is_double_gt(pl_norm_dot_c, 0))
            return true;

        if (is_double_lt(pl_norm_dot_a, 0) &&
            is_double_lt(pl_norm_dot_b, 0) &&
            is_double_lt(pl_norm_dot_c, 0))
            return true;

        return false;
    }

    bool is_triangles_intersect(const triangle_t& a, const triangle_t& b) {
        if (a == b)
            return true;

        plane_t plane_a(a.a_, a.b_, a.c_);
        if (is_on_one_side(plane_a, b))
            return false;

        plane_t plane_b(b.a_, b.b_, b.c_);

        if (plane_a == plane_b &&
            plane_a.is_valid() &&
            plane_b.is_valid())
            return is_triangles_intersect_in_plane(a, b);

        if (is_planes_parallel(plane_a, plane_b) &&
            plane_a.is_valid() &&
            plane_b.is_valid())
            return false;

        line_t line_inter = get_planes_intersection(plane_a, plane_b);
        if (!line_inter.v_.is_valid())
            return is_intersect_simple_figure(a, b);


        triangle_line_inter_coefs_t coefs_a = a.get_line_intersect_edges(line_inter);
        triangle_line_inter_coefs_t coefs_b = b.get_line_intersect_edges(line_inter);
        if(is_segments_coefs_intersect(coefs_a, coefs_b))
            return true;

        return false;
    }

    double triangle_square(const point_t& a, const point_t& b, const point_t& c) {
        return cross_product(b - a, c - a).length() / 2;
    }

    std::istream& operator>>(std::istream& is, triangle_t& t) {
        point_t a, b, c;
        is >> a >> b >> c;
        t = (triangle_t){a, b, c};
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const triangle_t& t) {
        os << print_lyellow("Triangle(") << t.a_ << print_lyellow(",") << t.b_ <<
              print_lyellow(",")         << t.c_ << print_lyellow(")");
        return os;
    }
}