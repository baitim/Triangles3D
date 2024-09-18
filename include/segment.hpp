#pragma once

#include "line.hpp"

namespace segment {
    using namespace line;

    class segment_t {
        point_t x_;
        point_t y_;

    public:
        segment_t() : x_(), y_() {}
        segment_t(point_t x, point_t y) : x_(x), y_(y) {}

        point_t& set_first()  { return x_; }
        point_t& set_second() { return y_; }

        point_t get_first()  const { return x_; }
        point_t get_second() const { return y_; }

        bool is_valid() const {
            return (x_.is_valid() && y_.is_valid());
        }

        bool is_line_intersect(const line_t& line) const { // a * (V1 x V2) = (P2 - P1) x V2
            if (!line.is_valid() || !is_valid())
                return false;

            line_t seg_line = line_t(x_, y_ - x_);

            point_t line_point = line.get_x();

            if (x_ == line_point || seg_line == line) 
                return true;

            if (is_lines_parallel(seg_line, line))
                return false;

            point_t V1xV2 = cross_product(seg_line.get_v(), line.get_v());

            point_t dP = x_ - line_point;
            point_t dPxV2 = cross_product(dP, line.get_v());

            if (V1xV2.norm() ==  dPxV2.norm() ||
                V1xV2.norm() == -dPxV2.norm() ||
                dPxV2.length() == 0)
                return true;

            return false;
        }
    };

    bool operator==(const segment_t& a, const segment_t& b) {
        return (a.get_first()  == b.get_first()  &&
                a.get_second() == b.get_second());
    }

    std::istream& operator>>(std::istream& is, segment_t& s) {
        is >> s.set_first() >> s.set_second();
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const segment_t& s) {
        os << print_lmagenta("Segment(") << s.get_first() << print_lmagenta(",") << s.get_second() <<
              print_lmagenta(")");
        return os;
    }
}