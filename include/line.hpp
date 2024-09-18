#pragma once

#include <iostream>
#include "ANSI_colors.hpp"
#include "point.hpp"

namespace line {
    using namespace point;

    class line_t final {
        point_t x_;
        point_t v_;

    public:
        line_t() : x_(), v_() {}
        line_t(point_t x, point_t v) : x_(x), v_(v) {}

        point_t& set_x() { return x_; }
        point_t& set_v() { return v_; }

        point_t get_x() const { return x_; }
        point_t get_v() const { return v_; }

        line_t norm() const {
            line_t norm{*this};
            norm.set_v().norm();
            return norm;
        }

        bool is_valid() const {
            return (x_.is_valid() && v_.is_valid());
        }
    };

    bool is_lines_parallel(const line_t& a, const line_t& b) {
        return (a.get_v().norm() ==  b.get_v().norm() ||
                a.get_v().norm() == -b.get_v().norm());
    }

    bool operator==(const line_t& a, const line_t& b) {
        if ((b.get_x() == a.get_x()) && (b.get_v() == a.get_v()))
            return true;

        line_t dx(a.get_x(), b.get_x() - a.get_x());
        return (is_lines_parallel(a, b) &&
                is_lines_parallel(a, dx));
    }

    std::istream& operator>>(std::istream& is, line_t& l) {
        is >> l.set_x() >> l.set_v();
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const line_t& l) {
        os << print_lblue("Line(") << l.get_x() << print_lblue(",") << l.get_v() << print_lblue(")");
        return os;
    }
}