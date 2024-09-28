#pragma once

#include "point.hpp"

namespace line {
    using namespace point;

    struct line_t final {
        point_t x_;
        point_t v_;

        line_t() : x_(), v_() {}
        line_t(point_t x, point_t v) : x_(x), v_(v) {}

        line_t norm() const {
            line_t norm{*this};
            norm.v_.norm();
            return norm;
        }

        bool is_valid() const {
            return (x_.is_valid() && v_.is_valid());
        }
    };

    bool is_lines_parallel(const line_t& a, const line_t& b) {
        point_t av_norm = a.v_.norm();
        point_t bv_norm = b.v_.norm();

        return (av_norm ==  bv_norm ||
                av_norm == -bv_norm);
    }

    bool operator==(const line_t& a, const line_t& b) {
        if ((b.x_ == a.x_) && (b.v_ == a.v_))
            return true;

        line_t dx(a.x_, b.x_ - a.x_);
        return (is_lines_parallel(a, b) &&
                (is_lines_parallel(a, dx) ||
                 (b.x_ == a.x_)));
    }

    bool is_lines_intersect(const line_t& a, const line_t& b) {
        if (a == b)
            return true;

        point_t M1M2 = b.x_ - a.x_;
        if (is_double_eq(triple_product(M1M2, a.v_, b.v_), 0))
            return true;

        return false;
    }

    std::istream& operator>>(std::istream& is, line_t& l) {
        is >> l.x_ >> l.v_;
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const line_t& l) {
        os << print_lblue("Line(") << l.x_ << print_lblue(",") << l.v_ << print_lblue(")");
        return os;
    }
}