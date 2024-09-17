#pragma once

#include <iostream>
#include "ANSI_colors.hpp"
#include "doubles.hpp"

namespace line {
    class line_t {
        double A_, B_, C_, D_;

    public:
        line_t() : A_(NAN), B_(NAN), C_(NAN), D_(NAN) {}
        line_t(double A, double B, double C, double D) : A_(A), B_(B), C_(C), D_(D) {}

        double& set_A() { return A_; }
        double& set_B() { return B_; }
        double& set_C() { return C_; }
        double& set_D() { return D_; }

        double get_A() const { return A_; }
        double get_B() const { return B_; }
        double get_C() const { return C_; }
        double get_D() const { return D_; }

        line_t norm() const {
            line_t norm{*this};

            double factor = 1;
            if (!doubles::is_double_equal(A_, 0)) {
                factor /= A_;
            } else if (!doubles::is_double_equal(B_, 0)) {
                factor /= B_;
            } else if (!doubles::is_double_equal(C_, 0)) {
                factor /= C_;
            } else if (!doubles::is_double_equal(D_, 0)) {
                factor /= D_;
            }

            norm.set_A() *= factor;
            norm.set_B() *= factor;
            norm.set_C() *= factor;
            norm.set_D() *= factor;

            return norm;
        }

        bool is_valid() const {
            return (!std::isnan(A_) &&
                    !std::isnan(B_) &&
                    !std::isnan(C_) &&
                    !std::isnan(D_));
        }
    };

    bool operator==(const line_t& a, const line_t& b) {
        return (doubles::is_double_equal(a.get_A(), b.get_A()) &&
                doubles::is_double_equal(a.get_B(), b.get_B()) &&
                doubles::is_double_equal(a.get_C(), b.get_C()) &&
                doubles::is_double_equal(a.get_D(), b.get_D()));
    }

    std::istream& operator>>(std::istream& is, line_t& l) {
        is >> l.set_A() >> l.set_B() >> l.set_C() >> l.set_D();
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const line_t& l) {
        os << print_lblue("Line(" << l.get_A() << "," << l.get_B() << "," << l.get_C() <<
                          "," << l.get_D() << ")");
        return os;
    }
}