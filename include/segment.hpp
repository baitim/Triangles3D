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

        point_t get_first()  const { return x_; }
        point_t get_second() const { return y_; }
        point_t get_vector() const { return v_; }
    };

    bool operator==(const segment_t& a, const segment_t& b) {
        return (a.get_first()  == b.get_first()  &&
                a.get_second() == b.get_second() &&
                a.get_vector() == b.get_vector());
    }

    std::istream& operator>>(std::istream& is, segment_t& s) {
        is >> s.set_first() >> s.set_second();
        s.update_v();
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const segment_t& s) {
        os << print_lmagenta("Segment(") << s.get_first() << print_lmagenta(",") << s.get_second() <<
              print_lmagenta(",") << s.get_vector() << print_lmagenta(")");
        return os;
    }
}