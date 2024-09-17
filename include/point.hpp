#pragma once

#include <iostream>
#include "ANSI_colors.hpp"
#include "doubles.hpp"

namespace point {
    class point_t {
        double x_, y_, z_;

    public:
        point_t() : x_(NAN), y_(NAN), z_(NAN) {}
        point_t(double val) : x_(val), y_(val), z_(val) {}
        point_t(double x, double y, double z) : x_(x), y_(y), z_(z) {}

        double& set_x() { return x_; }
        double& set_y() { return y_; }
        double& set_z() { return z_; }

        double get_x() const { return x_; }
        double get_y() const { return y_; }
        double get_z() const { return z_; }

        double length() const {
            return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
        }

        bool is_valid() const {
            return (!std::isnan(x_) &&
                    !std::isnan(y_) &&
                    !std::isnan(z_));
        }
    };

    point_t cross_product(const point_t& a, const point_t& b) {
        double new_a = a.get_y() * b.get_z() - a.get_z() * b.get_y();
        double new_b = a.get_z() * b.get_x() - a.get_x() * b.get_z();
        double new_c = a.get_x() * b.get_y() - a.get_y() * b.get_x();

        return point_t{new_a, new_b, new_c};
    }

    point_t operator+(const point_t& a, const point_t& b) {
        return point_t(a.get_x() + b.get_x(), a.get_y() + b.get_y(), a.get_z() + b.get_z());
    }

    point_t operator-(const point_t& a, const point_t& b) {
        return point_t(a.get_x() - b.get_x(), a.get_y() - b.get_y(), a.get_z() - b.get_z());
    }

    point_t operator*(const point_t& a, const point_t& b) {
        return point_t(a.get_x() * b.get_x(), a.get_y() * b.get_y(), a.get_z() * b.get_z());
    }

    point_t operator/(const point_t& a, const point_t& b) {
        return point_t(a.get_x() / b.get_x(), a.get_y() / b.get_y(), a.get_z() / b.get_z());
    }

    const point_t& operator+=(point_t& a, const point_t& b) {
        return a = a + b;
    }

    const point_t& operator-=(point_t& a, const point_t& b) {
        return a = a - b;
    }

    bool operator<(const point_t& a, const point_t& b) {
        return (doubles::is_double_equal(a.get_x(), b.get_x()) &&
                doubles::is_double_equal(a.get_y(), b.get_y()) &&
                doubles::is_double_equal(a.get_z(), b.get_z()));
    }

    bool operator==(const point_t& a, const point_t& b) {
        return (doubles::is_double_equal(a.get_x(), b.get_x()) &&
                doubles::is_double_equal(a.get_y(), b.get_y()) &&
                doubles::is_double_equal(a.get_z(), b.get_z()));
    }

    std::istream& operator>>(std::istream& is, point_t& p) {
        is >> p.set_x() >> p.set_y() >> p.set_z();
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const point_t& p) {
        os << print_lcyan("Point(" << p.get_x() << "," << p.get_y() << "," << p.get_z() << ")");
        return os;
    }
}