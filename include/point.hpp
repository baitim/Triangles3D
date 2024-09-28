#pragma once

#include <iostream>
#include "ANSI_colors.hpp"
#include "doubles.hpp"

namespace point {
    using namespace doubles;

    struct point_t final {
        double x_, y_, z_;

        point_t() : x_(NAN), y_(NAN), z_(NAN) {}
        point_t(double val) : x_(val), y_(val), z_(val) {}
        point_t(double x, double y, double z) : x_(x), y_(y), z_(z) {}

        double length() const {
            return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
        }

        point_t norm() const {
            point_t norm{*this};
            double length = norm.length();

            norm.x_ = x_ / length;
            norm.y_ = y_ / length;
            norm.z_ = z_ / length;

            return norm;
        }

        bool is_valid() const {
            return (!std::isnan(x_) &&
                    !std::isnan(y_) &&
                    !std::isnan(z_));
        }
    };

    double dot(const point_t& a, const point_t& b) {
        return (a.x_ * b.x_) + (a.y_ * b.y_) + (a.z_ * b.z_);
    }

    point_t cross_product(const point_t& a, const point_t& b) {
        double new_a = a.y_ * b.z_ - a.z_ * b.y_;
        double new_b = a.z_ * b.x_ - a.x_ * b.z_;
        double new_c = a.x_ * b.y_ - a.y_ * b.x_;

        return point_t{new_a, new_b, new_c};
    }


    double triple_product(const point_t& a, const point_t& b, const point_t& c) {
        double k1 = a.y_ * b.z_ - a.z_ * b.y_;
        double k2 = a.z_ * b.x_ - a.x_ * b.z_;
        double k3 = a.x_ * b.y_ - a.y_ * b.x_;

        return k1 * c.x_ + k2 * c.y_ + k3 * c.z_;
    }

    point_t operator-(const point_t& a) {
        return point_t(-a.x_, -a.y_, -a.z_);
    }

    point_t operator+(const point_t& a, const point_t& b) {
        return point_t(a.x_ + b.x_, a.y_ + b.y_, a.z_ + b.z_);
    }

    point_t operator-(const point_t& a, const point_t& b) {
        return point_t(a.x_ - b.x_, a.y_ - b.y_, a.z_ - b.z_);
    }

    point_t operator*(const point_t& a, const point_t& b) {
        return point_t(a.x_ * b.x_, a.y_ * b.y_, a.z_ * b.z_);
    }

    point_t operator/(const point_t& a, const point_t& b) {
        return point_t(a.x_ / b.x_, a.y_ / b.y_, a.z_ / b.z_);
    }

    const point_t& operator+=(point_t& a, const point_t& b) {
        return a = a + b;
    }

    const point_t& operator-=(point_t& a, const point_t& b) {
        return a = a - b;
    }

    bool operator==(const point_t& a, const point_t& b) {
        return (is_double_eq(a.x_, b.x_) &&
                is_double_eq(a.y_, b.y_) &&
                is_double_eq(a.z_, b.z_));
    }

    bool operator!=(const point_t& a, const point_t& b) {
        return !(a == b);
    }

    bool operator<(const point_t& a, const point_t& b) {

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

    bool operator<=(const point_t& a, const point_t& b) {
        return ((a < b) || (a == b));
    }

    bool operator>(const point_t& a, const point_t& b) {
        return !(a <= b);
    }

    bool operator>=(const point_t& a, const point_t& b) {
        return !(a < b);
    }

    std::istream& operator>>(std::istream& is, point_t& p) {
        is >> p.x_ >> p.y_ >> p.z_;
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const point_t& p) {
        os << print_lcyan("Point(" << p.x_ << "," << p.y_ << "," << p.z_ << ")");
        return os;
    }
}