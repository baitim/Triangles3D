#pragma once

#include "point.hpp"

namespace segment {
    using namespace point;

    class segment_t {
        point_t x_;
        point_t y_;
        point_t v_;

    public:
        segment_t() : x_(), y_(), v_() {}
        segment_t(point_t x, point_t y) : x_(x), y_(y) {
            v_ = y_ - x_;
        }

        void update_v() {
            v_ = y_ - x_;
        }

        point_t& set_first()  { return x_; }
        point_t& set_second() { return y_; }

        point_t first()  const { return x_; }
        point_t second() const { return y_; }
        point_t vector() const { return v_; }
    };

    bool operator==(const segment_t& a, const segment_t& b) {
        return (a.first()  == b.first()  &&
                a.second() == b.second() &&
                a.vector() == b.vector());
    }

    std::istream& operator>>(std::istream& is, segment_t& s) {
        is >> s.set_first() >> s.set_second();
        s.update_v();
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const segment_t& s) {
        os << print_lmagenta("Segment(") << s.first() << print_lmagenta(",") << s.second() <<
              print_lmagenta(",") << s.vector() << print_lmagenta(")");
        return os;
    }
}