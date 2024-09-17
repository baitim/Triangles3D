#pragma once

#include "line.hpp"
#include "segment.hpp"

namespace plane {
    using namespace segment; 

    class plane_t {
        double A_, B_, C_, D_;

    public:
        plane_t() : A_(0), B_(0), C_(0), D_(0) {}
        plane_t(double A, double B, double C, double D) : A_(A), B_(B), C_(C), D_(D) {}

        plane_t(point_t a, point_t b, point_t c) {
            float a1 = b.get_x() - a.get_x();
            float b1 = b.get_y() - a.get_y();
            float c1 = b.get_z() - a.get_z();
            float a2 = c.get_x() - a.get_x();
            float b2 = c.get_y() - a.get_y();
            float c2 = c.get_z() - a.get_z();
            A_ = b1 * c2 - b2 * c1;
            B_ = a2 * c1 - a1 * c2;
            C_ = a1 * b2 - b1 * a2;
            D_ = (- A_ * a.get_x() - B_ * a.get_y() - C_ * a.get_z());
        }
        
        plane_t(segment_t ab, segment_t bc, segment_t ca) {
            point_t a = ab.get_first();
            point_t b = bc.get_first();
            point_t c = ca.get_first();

            *this = plane_t(a, b, c);
        }

        plane_t norm() const {
            plane_t a_norm{*this};

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

            a_norm.set_A() *= factor;
            a_norm.set_B() *= factor;
            a_norm.set_C() *= factor;
            a_norm.set_D() *= factor;

            return a_norm;
        }

        double& set_A() { return A_; }
        double& set_B() { return B_; }
        double& set_C() { return C_; }
        double& set_D() { return D_; }

        double get_A() const { return A_; }
        double get_B() const { return B_; }
        double get_C() const { return C_; }
        double get_D() const { return D_; }

        point_t normal() const {
            return point_t(A_, B_, C_);
        }
    };

    bool is_planes_parallel(const plane_t& a, const plane_t& b) {
        plane_t a_norm = a.norm();
        plane_t b_norm = b.norm();

        return (doubles::is_double_equal(a_norm.get_A(), b_norm.get_A()) &&
                doubles::is_double_equal(a_norm.get_B(), b_norm.get_B()) &&
                doubles::is_double_equal(a_norm.get_C(), b_norm.get_C()));
    }

    bool operator==(const plane_t& a, const plane_t& b) {
        plane_t a_norm = a.norm();
        plane_t b_norm = b.norm();

        return (is_planes_parallel(a, b) &&
                doubles::is_double_equal(a_norm.get_D(), b_norm.get_D()));
    }

    std::istream& operator>>(std::istream& is, plane_t& pl) {
        is >> pl.set_A() >> pl.set_B() >> pl.set_C() >> pl.set_D();
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const plane_t& pl) {
        os << print_lgreen("Plane(" << pl.get_A() << "," << pl.get_B() << "," <<
                           pl.get_C() << "," << pl.get_D() << ")");
        return os;
    }
}