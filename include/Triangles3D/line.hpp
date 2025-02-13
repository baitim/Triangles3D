#pragma once

#include "point.hpp"

namespace line {
    using namespace point;

    template <typename T = double>
    struct line_t final {
        point_t<T> x_;
        point_t<T> v_;

        line_t() : x_(), v_() {}
        line_t(point_t<T> x, point_t<T> v) : x_(x), v_(v) {}

        line_t<T> norm() const {
            line_t<T> norm{*this};
            norm.v_.norm();
            return norm;
        }

        bool is_valid() const {
            return (x_.is_valid() && v_.is_valid());
        }
    };

    template <typename T>
    bool is_lines_parallel(const line_t<T>& a, const line_t<T>& b) {
        point_t<T> av_norm = a.v_.norm();
        point_t<T> bv_norm = b.v_.norm();

        return (av_norm ==  bv_norm ||
                av_norm == -bv_norm);
    }

    template <typename T>
    bool operator==(const line_t<T>& a, const line_t<T>& b) {
        if ((b.x_ == a.x_) && (b.v_ == a.v_))
            return true;

        line_t<T> dx(a.x_, b.x_ - a.x_);
        return (is_lines_parallel(a, b) &&
                (is_lines_parallel(a, dx) ||
                 (b.x_ == a.x_)));
    }

    template <typename T>
    bool is_lines_intersect(const line_t<T>& a, const line_t<T>& b) {
        if (a == b)
            return true;

        point_t<T> M1M2 = b.x_ - a.x_;
        if (is_real_eq(triple_product(M1M2, a.v_, b.v_), T{0}))
            return true;

        return false;
    }

    template <typename T>
    std::istream& operator>>(std::istream& is, line_t<T>& l) {
        is >> l.x_ >> l.v_;
        return is;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const line_t<T>& l) {
        os << print_lblue("Line(") << l.x_ << print_lblue(",") << l.v_ << print_lblue(")");
        return os;
    }
}