#pragma once

#include <iostream>
#include "ANSI_colors.hpp"
#include "doubles.hpp"

namespace line {
    class line_t {
        double a_, b_, c_, d_;

    public:
        line_t() : a_(), b_(), c_(), d_() {}
        line_t(double a, double b, double c, double d) : a_(a), b_(b), c_(c), d_(d) {}

        double& set_a() { return a_; }
        double& set_b() { return b_; }
        double& set_c() { return c_; }
        double& set_d() { return d_; }

        double get_a() const { return a_; }
        double get_b() const { return b_; }
        double get_c() const { return c_; }
        double get_d() const { return d_; }
    };

    bool operator==(const line_t& a, const line_t& b) {
        return (doubles::is_double_equal(a.get_a(), b.get_a()) &&
                doubles::is_double_equal(a.get_b(), b.get_b()) &&
                doubles::is_double_equal(a.get_c(), b.get_c()) &&
                doubles::is_double_equal(a.get_d(), b.get_d()));
    }

    std::istream& operator>>(std::istream& is, line_t& l) {
        is >> l.set_a() >> l.set_b() >> l.set_c() >> l.set_d();
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const line_t& l) {
        os << print_lblue("Line(" << l.get_a() << "," << l.get_b() << "," << l.get_c() <<
                          "," << l.get_d() << ")");
        return os;
    }
}