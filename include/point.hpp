#pragma once

#include <iostream>
#include "ANSI_colors.hpp"
#include "doubles.hpp"

namespace point {
    class point_t {
        double x_, y_, z_;

    public:
        point_t() : x_(), y_(), z_() {}
        point_t(double x, double y, double z) : x_(x), y_(y), z_(z) {}

        double& set_x() { return x_; }
        double& set_y() { return y_; }
        double& set_z() { return z_; }

        double x() const { return x_; }
        double y() const { return y_; }
        double z() const { return z_; }
    };

    point_t operator+(const point_t& a, const point_t& b) {
        return point_t(a.x() + b.x(), a.y() + b.y(), a.z() + b.z());
    }

    point_t operator-(const point_t& a, const point_t& b) {
        return point_t(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
    }

    const point_t& operator+=(point_t& a, const point_t& b) {
        return a = a + b;
    }

    const point_t& operator-=(point_t& a, const point_t& b) {
        return a = a - b;
    }

    bool operator==(const point_t& a, const point_t& b) {
        return (doubles::is_double_equal(a.x(), b.x()) &&
                doubles::is_double_equal(a.y(), b.y()) &&
                doubles::is_double_equal(a.z(), b.z()));
    }

    std::istream& operator>>(std::istream& is, point_t& p) {
        is >> p.set_x() >> p.set_y() >> p.set_z();
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const point_t& p) {
        os << print_lcyan("Point(" << p.x() << "," << p.y() << "," << p.z() << ")");
        return os;
    }
}