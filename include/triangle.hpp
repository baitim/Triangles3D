#pragma once

#include "plane.hpp"

namespace triangle {
    using namespace plane;

    double triangle_square(const point_t& a, const point_t& b, const point_t& c);

    class triangle_t {
        point_t a_;
        point_t b_;
        point_t c_;

        plane_t triag_plane;

    public:
        triangle_t() : a_(), b_(), c_(), triag_plane() {}
        triangle_t(segment_t ab, segment_t bc, segment_t ca) : a_(ab.get_first()), b_(bc.get_first()),
                                                               c_(ca.get_first()),
                                                               triag_plane(ab, bc, ca) {}

        triangle_t(point_t a, point_t b, point_t c) : a_(a), b_(b), c_(c), triag_plane(a, b, c) {}

        point_t& set_a() { return a_; }
        point_t& set_b() { return b_; }
        point_t& set_c() { return c_; }

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
            
            if (doubles::is_double_equal(S1 + S2 + S3, S) &&
                doubles::is_double_less(S1, S) &&
                doubles::is_double_less(S2, S) &&
                doubles::is_double_less(S3, S))
                return true;

            return false;
        }
    };

    double triangle_square(const point_t& a, const point_t& b, const point_t& c) {
        segment_t ba{b, a};
        segment_t ca{c, a};
        return cross_product(ba.get_vector(), ca.get_vector()).length() / 2;
    }

    bool operator==(const triangle_t& a, const triangle_t& b) {
        return (a.get_a() == b.get_a() &&
                a.get_b() == b.get_b() &&
                a.get_c() == b.get_c());
    }

    std::istream& operator>>(std::istream& is, triangle_t& t) {
        is >> t.set_a() >> t.set_b() >> t.set_c();
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const triangle_t& t) {
        os << print_lyellow("Triangle(") << t.get_a() << print_lyellow(",") << t.get_b() <<
              print_lyellow(",")         << t.get_c() << print_lyellow(")");
        return os;
    }
}