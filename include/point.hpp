#pragma once

#include <iostream>
#include "ANSI_colors.hpp"
#include "doubles.hpp"

namespace point {
    class point_t {
        double x_, y_, z_;

    public:
        point_t()                             : x_(0), y_(0), z_(0) {}
        point_t(double x, double y, double z) : x_(x), y_(y), z_(z) {}

        double& operator[](int n) {
            if (n == 0)
                return x_;
            if (n == 1)
                return y_;
            return z_;
        }

        double operator[](int n) const {
            if (n == 0)
                return x_;
            if (n == 1)
                return y_;
            return z_;
        }
    };

    point_t operator+(const point_t& a, const point_t& b) {
        return point_t(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
    }

    point_t operator-(const point_t& a, const point_t& b) {
        return point_t(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
    }

    const point_t& operator+=(point_t& a, const point_t& b) {
        return a = a + b;
    }

    const point_t& operator-=(point_t& a, const point_t& b) {
        return a = a - b;
    }

    bool operator==(const point_t& a, const point_t& b) {
        return (doubles::is_double_equal(a[0], b[0]) &&
                doubles::is_double_equal(a[1], b[1]) &&
                doubles::is_double_equal(a[2], b[2]));
    }

    std::istream& operator>>(std::istream& is, point_t& p) {
        is >> p[0] >> p[1] >> p[2];
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const point_t& p) {
        os << print_lcyan("\nPoint:\t(" << p[0] << ", " << p[1] << ", " << p[2] << ")\n");
        return os;
    }
}