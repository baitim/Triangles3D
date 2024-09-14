#pragma once

#include "plane.hpp"

namespace triangle {
    using namespace segment;

    class triangle_t {
        segment_t ab_;
        segment_t bc_;
        segment_t ca_;

        plane::plane_t triag_plane;

    public:
        triangle_t() : ab_(), bc_(), ca_(), triag_plane() {}
        triangle_t(segment_t ab, segment_t bc, segment_t ca) : ab_(ab), bc_(bc), ca_(ca),
                                                               triag_plane(ab, bc, ca) {}
        triangle_t(point_t x, point_t y, point_t z) : triag_plane(x, y, z) {
            ab_ = segment_t(x, y);
            bc_ = segment_t(y, z);
            ca_ = segment_t(z, x);
        }

        segment_t& set_ab() { return ab_; }
        segment_t& set_bc() { return bc_; }
        segment_t& set_ca() { return ca_; }

        segment_t ab() const { return ab_; }
        segment_t bc() const { return bc_; }
        segment_t ca() const { return ca_; }

        point_t a() const { return ab_.first(); }
        point_t b() const { return bc_.first(); }
        point_t c() const { return ca_.first(); }

        plane::plane_t plane() const { return triag_plane; }
    };

    bool operator==(const triangle_t& a, const triangle_t& b) {
        return (a.ab() == b.ab() &&
                a.bc() == b.bc() &&
                a.ca() == b.ca());
    }

    std::istream& operator>>(std::istream& is, triangle_t& t) {
        is >> t.set_ab() >> t.set_bc() >> t.set_ca();
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const triangle_t& t) {
        os << print_lyellow("Triangle(") << t.ab() << print_lyellow(",") << t.bc() <<
              print_lyellow(",")         << t.ca() << print_lyellow(")");
        return os;
    }
}