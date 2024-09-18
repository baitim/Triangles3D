#pragma once

#include <set>
#include "plane.hpp"

namespace triangle {
    using namespace plane;

    double triangle_square(const point_t& a, const point_t& b, const point_t& c);

    class triangle_t final {
        point_t a_;
        point_t b_;
        point_t c_;

        plane_t triag_plane;

    public:
        triangle_t() : a_(), b_(), c_(), triag_plane() {}
        triangle_t(segment_t ab, segment_t bc, segment_t ca) : a_(ab.get_x()), b_(bc.get_x()),
                                                               c_(ca.get_x()),
                                                               triag_plane(ab, bc, ca) {}

        triangle_t(point_t a, point_t b, point_t c) : a_(a), b_(b), c_(c), triag_plane(a, b, c) {}

        point_t& set_a() { return a_; }
        point_t& set_b() { return b_; }
        point_t& set_c() { return c_; }
        plane_t& set_plane() { return triag_plane; }

        point_t get_a() const { return a_; }
        point_t get_b() const { return b_; }
        point_t get_c() const { return c_; }
        plane_t get_plane() const { return triag_plane; }

        double square() const { 
            return triangle_square(a_, b_, c_); 
        }

        bool is_point_in(const point_t& p) const {

            double S  = triangle_square(a_, b_, c_);
            double S1 = triangle_square(p,  a_, b_);
            double S2 = triangle_square(p,  a_, c_);
            double S3 = triangle_square(p,  b_, c_);
            
            if (is_double_equal(S1 + S2 + S3, S) &&
                is_double_less(S1, S) &&
                is_double_less(S2, S) &&
                is_double_less(S3, S))
                return true;

            return false;
        }

        bool is_valid() const {
            return (a_.is_valid() &&
                    b_.is_valid() &&
                    c_.is_valid() &&
                    triag_plane.is_valid());
        }

        coefs_t* get_line_intersect_edges(const line_t& line) const {
            if (!line.is_valid() || !is_valid())
                return new coefs_t[3]{false, NAN, NAN};

            segment_t segs[3] = {{a_, b_}, {b_, c_}, {c_, a_}};
            coefs_t* coefs = new coefs_t[3]{false, NAN, NAN};

            for (int i = 0; i < 3; ++i)
                coefs[i] = segs[i].get_line_intersect(line);

            return coefs;
        }

        bool is_line_intersect_edges(const line_t& line) const {
            coefs_t* coefs = get_line_intersect_edges(line);
            for (int i = 0; i < 3; ++i) {
                if (coefs[i].is_valid_) {
                    delete [] coefs;
                    return true;
                }
            }

            delete [] coefs;
            return false;
        }

        bool is_triangle_vertexes_inside(const triangle_t& t) const {
            if (is_point_in(t.get_a()) ||
                is_point_in(t.get_b()) ||
                is_point_in(t.get_c()))
                return true;

            return false;
        }

        bool is_edges_intersect_edges(const triangle_t& tr) const {
            segment_t t[3] = {segment_t(tr.get_a(), tr.get_b()),
                              segment_t(tr.get_b(), tr.get_c()),
                              segment_t(tr.get_c(), tr.get_a())};

            segment_t curr[3] = {segment_t(get_a(), get_b()),
                                 segment_t(get_b(), get_c()),
                                 segment_t(get_c(), get_a())};

            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    if (t[i].is_segment_intersect(curr[j]))
                        return true;

            return false;
        }

        bool is_triangle_is_point() const {
            return ((a_ == b_) && (b_ == c_));
        }

        bool is_triangle_is_line() const {
            line_t ab(a_, b_ - a_);
            line_t bc(b_, c_ - b_);
            line_t ca(c_, a_ - c_);

            return (is_lines_parallel(ab, bc) ||
                    is_lines_parallel(bc, ca) ||
                    is_lines_parallel(ab, ca));
        }

        line_t triangle_to_line() const {
            if (!is_triangle_is_line())
                return line_t();

            line_t ab(a_, b_ - a_);
            line_t bc(b_, c_ - b_);
            line_t ca(c_, a_ - c_);

            if (is_lines_parallel(ab, bc))
                return line_t(a_, b_ - a_);

            if (is_lines_parallel(bc, ca))
                return line_t(b_, c_ - b_);

            if (is_lines_parallel(ab, ca))
                return line_t(a_, b_ - a_);

            return line_t();
        }
    };

        bool is_line_intersect_triangle(const triangle_t& a, const line_t& line) {
            if (a.get_plane().norm().normal() == line.get_v().norm()) {
                if (a.get_plane().is_point_in(line.get_x()))
                    return true;
                else
                    return false;
            }

            point_t p = a.get_plane().get_intersect_line(line);

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

    bool is_segments_coefs_intersect(coefs_t* coefs_a, coefs_t* coefs_b) {
        coefs_t coefs_a1(false), coefs_a2(false), coefs_b1(false), coefs_b2(false);
        for (int i = 0; i < 3; ++i) {
            if (coefs_a[i].is_valid_) {
                if (!coefs_a1.is_valid_)
                    coefs_a1 = coefs_a[i];
                else    
                    coefs_a2 = coefs_a[i];
            }

            if (coefs_b[i].is_valid_) {
                if (!coefs_b1.is_valid_)
                    coefs_b1 = coefs_b[i];
                else    
                    coefs_b2 = coefs_b[i];
            }
        }

        segment_t coefs_a_range{coefs_a1.k1_, coefs_a2.k1_};
        segment_t coefs_b_range{coefs_b1.k1_, coefs_b2.k1_};

        if (coefs_a_range.is_point_in(coefs_b1.k1_) || coefs_a_range.is_point_in(coefs_b2.k1_) ||
            coefs_b_range.is_point_in(coefs_a1.k1_) || coefs_b_range.is_point_in(coefs_a2.k1_))
            return true;
        
        return false;
    }

    bool is_intersect_simple_figure(const triangle_t& a, const triangle_t& b) {
        if (a.is_triangle_is_point())
            return b.is_point_in(a.get_a());

        if (b.is_triangle_is_point())
            return a.is_point_in(b.get_a());

        line_t line_a = a.triangle_to_line();
        line_t line_b = b.triangle_to_line();

        if (a.is_triangle_is_line() &&
            b.is_triangle_is_line())
            return is_lines_intersect(line_a, line_b);

        if (a.is_triangle_is_line())
            return is_line_intersect_triangle(b, line_a);

        if (b.is_triangle_is_line())
            return is_line_intersect_triangle(a, line_b);

        return false;
    }

    bool is_triangles_intersect(const triangle_t& a, const triangle_t& b) {
        plane_t plane_a(a.get_a(), a.get_b(), a.get_c());
        plane_t plane_b(b.get_a(), b.get_b(), b.get_c());

        if (plane_a == plane_b)
            return is_triangles_intersect_in_plane(a, b);

        if (is_planes_parallel(plane_a, plane_b))
            return false;

        line_t line_inter = get_planes_intersection(plane_a, plane_b);

        if (!line_inter.get_v().is_valid())
            return is_intersect_simple_figure(a, b);
            

        coefs_t* coefs_a = a.get_line_intersect_edges(line_inter);
        coefs_t* coefs_b = b.get_line_intersect_edges(line_inter);

        for (int i = 0; i < 3; i++) {
            std::cerr << coefs_a[i].is_valid_ << " " << coefs_a[i].k1_ << " " << coefs_a[i].k2_ << "\n";
        }

        for (int i = 0; i < 3; i++) {
            std::cerr << coefs_b[i].is_valid_ << " " << coefs_b[i].k1_ << " " << coefs_b[i].k2_ << "\n";
        }

        bool is_coefs_intersection = is_segments_coefs_intersect(coefs_a, coefs_b);
        delete [] coefs_a;
        delete [] coefs_b;

        if(is_coefs_intersection)
            return true;

        return false;
    }

    std::set<int> get_set_triangles_in_intersections(int count, const triangle_t* b) {
        std::set<int> ans;
        for (int i = 0; i < count; ++i) {
            for (int j = i + 1; j < count; ++j) {
                if (is_triangles_intersect(b[i], b[j])) {
                    ans.insert(i);
                    ans.insert(j);
                }
            }
        }
        return ans;
    }

    double triangle_square(const point_t& a, const point_t& b, const point_t& c) {
        return cross_product(b - a, c - a).length() / 2;
    }

    bool operator==(const triangle_t& a, const triangle_t& b) {
        return (a.get_a() == b.get_a() &&
                a.get_b() == b.get_b() &&
                a.get_c() == b.get_c());
    }

    std::istream& operator>>(std::istream& is, triangle_t& t) {
        point_t a, b, c;
        is >> a >> b >> c;
        t = (triangle_t){a, b, c};
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const triangle_t& t) {
        os << print_lyellow("Triangle(") << t.get_a() << print_lyellow(",") << t.get_b() <<
              print_lyellow(",")         << t.get_c() << print_lyellow(")");
        return os;
    }
}