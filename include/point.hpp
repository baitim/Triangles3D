#pragma once

#include <iostream>
#include "ANSI_colors.hpp"
#include "doubles.hpp"

namespace point {
    using namespace doubles;

    class point_t final {
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
        return (a.get_x() * b.get_x()) + (a.get_y() * b.get_y()) + (a.get_z() * b.get_z());
    }

    point_t cross_product(const point_t& a, const point_t& b) {
        double new_a = a.get_y() * b.get_z() - a.get_z() * b.get_y();
        double new_b = a.get_z() * b.get_x() - a.get_x() * b.get_z();
        double new_c = a.get_x() * b.get_y() - a.get_y() * b.get_x();

        return point_t{new_a, new_b, new_c};
    }


    double triple_product(const point_t& a, const point_t& b, const point_t& c) {
        double k1 = a.get_y() * b.get_z() - a.get_z() * b.get_y();
        double k2 = a.get_z() * b.get_x() - a.get_x() * b.get_z();
        double k3 = a.get_x() * b.get_y() - a.get_y() * b.get_x();

        return k1 * c.get_x() + k2 * c.get_y() + k3 * c.get_z();
    }

    point_t operator-(const point_t& a) {
        return point_t(-a.get_x(), -a.get_y(), -a.get_z());
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

    bool operator==(const point_t& a, const point_t& b) {
        return (is_double_eq(a.get_x(), b.get_x()) &&
                is_double_eq(a.get_y(), b.get_y()) &&
                is_double_eq(a.get_z(), b.get_z()));
    }

    bool operator!=(const point_t& a, const point_t& b) {
        return !(a == b);
    }

    bool operator<(const point_t& a, const point_t& b) {

        if (is_double_lt(a.get_x(), b.get_x()))
            return true;
        else if (is_double_gt(a.get_x(), b.get_x()))
            return false;

        if (is_double_lt(a.get_y(), b.get_y()))
            return true;
        else if (is_double_gt(a.get_y(), b.get_y()))
            return false;

        if (is_double_lt(a.get_z(), b.get_z()))
            return true;
        else if (is_double_gt(a.get_z(), b.get_z()))
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
        is >> p.set_x() >> p.set_y() >> p.set_z();
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const point_t& p) {
        os << print_lcyan("Point(" << p.get_x() << "," << p.get_y() << "," << p.get_z() << ")");
        return os;
    }
}