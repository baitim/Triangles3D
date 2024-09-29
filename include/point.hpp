#pragma once

#include <iostream>
#include "ANSI_colors.hpp"
#include "doubles.hpp"

namespace point {
    using namespace doubles;

    template <typename T = double>
    struct point_t final {
        T x_, y_, z_;

        point_t() : x_(NAN), y_(NAN), z_(NAN) {}
        point_t(T val) : x_(val), y_(val), z_(val) {}
        point_t(T x, T y, T z) : x_(x), y_(y), z_(z) {}
        point_t(const point_t<T>& p) : x_(p.x_), y_(p.y_), z_(p.z_) {}

        T length() const {
            return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
        }

        point_t<T> norm() const {
            point_t<T> norm{*this};
            T length = norm.length();

            norm.x_ = x_ / length;
            norm.y_ = y_ / length;
            norm.z_ = z_ / length;

            return norm;
        }

        bool is_valid() const {
            return !(x_ != x_ ||
                     y_ != y_ ||
                     z_ != z_);
        }
    };

    template <typename T>
    T dot(const point_t<T>& a, const point_t<T>& b) {
        return (a.x_ * b.x_) + (a.y_ * b.y_) + (a.z_ * b.z_);
    }

    template <typename T>
    point_t<T> cross_product(const point_t<T>& a, const point_t<T>& b) {
        T new_a = a.y_ * b.z_ - a.z_ * b.y_;
        T new_b = a.z_ * b.x_ - a.x_ * b.z_;
        T new_c = a.x_ * b.y_ - a.y_ * b.x_;

        return point_t<T>{new_a, new_b, new_c};
    }

    template <typename T>
    T triple_product(const point_t<T>& a, const point_t<T>& b, const point_t<T>& c) {
        T k1 = a.y_ * b.z_ - a.z_ * b.y_;
        T k2 = a.z_ * b.x_ - a.x_ * b.z_;
        T k3 = a.x_ * b.y_ - a.y_ * b.x_;

        return k1 * c.x_ + k2 * c.y_ + k3 * c.z_;
    }

    template <typename T>
    point_t<T> operator-(const point_t<T>& a) {
        return point_t<T>(-a.x_, -a.y_, -a.z_);
    }

    template <typename T>
    point_t<T> operator+(const point_t<T>& a, const point_t<T>& b) {
        return point_t<T>(a.x_ + b.x_, a.y_ + b.y_, a.z_ + b.z_);
    }

    template <typename T>
    point_t<T> operator-(const point_t<T>& a, const point_t<T>& b) {
        return point_t<T>(a.x_ - b.x_, a.y_ - b.y_, a.z_ - b.z_);
    }

    template <typename T>
    point_t<T> operator*(const point_t<T>& a, const point_t<T>& b) {
        return point_t<T>(a.x_ * b.x_, a.y_ * b.y_, a.z_ * b.z_);
    }

    template <typename T>
    point_t<T> operator/(const point_t<T>& a, const point_t<T>& b) {
        return point_t<T>(a.x_ / b.x_, a.y_ / b.y_, a.z_ / b.z_);
    }

    template <typename T>
    const point_t<T>& operator+=(point_t<T>& a, const point_t<T>& b) {
        return a = a + b;
    }

    template <typename T>
    const point_t<T>& operator-=(point_t<T>& a, const point_t<T>& b) {
        return a = a - b;
    }

    template <typename T>
    bool operator==(const point_t<T>& a, const point_t<T>& b) {
        return (is_double_eq(a.x_, b.x_) &&
                is_double_eq(a.y_, b.y_) &&
                is_double_eq(a.z_, b.z_));
    }

    template <typename T>
    bool operator!=(const point_t<T>& a, const point_t<T>& b) {
        return !(a == b);
    }

    template <typename T>
    bool operator<(const point_t<T>& a, const point_t<T>& b) {

        if (is_double_lt(a.x_, b.x_))
            return true;
        else if (is_double_gt(a.x_, b.x_))
            return false;

        if (is_double_lt(a.y_, b.y_))
            return true;
        else if (is_double_gt(a.y_, b.y_))
            return false;

        if (is_double_lt(a.z_, b.z_))
            return true;
        else if (is_double_gt(a.z_, b.z_))
            return false;

        return false;
    }

    template <typename T>
    bool operator<=(const point_t<T>& a, const point_t<T>& b) {
        return ((a < b) || (a == b));
    }

    template <typename T>
    bool operator>(const point_t<T>& a, const point_t<T>& b) {
        return !(a <= b);
    }

    template <typename T>
    bool operator>=(const point_t<T>& a, const point_t<T>& b) {
        return !(a < b);
    }

    template <typename T>
    std::istream& operator>>(std::istream& is, point_t<T>& p) {
        is >> p.x_ >> p.y_ >> p.z_;
        return is;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const point_t<T>& p) {
        os << print_lcyan("Point(" << p.x_ << "," << p.y_ << "," << p.z_ << ")");
        return os;
    }
}