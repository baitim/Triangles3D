#pragma once

#include "segment.hpp"

namespace plane {
    using namespace segment; 

    class plane_t {
        double A_, B_, C_, D_;

    public:
        plane_t() : A_(0), B_(0), C_(0), D_(0) {}
        plane_t(double A, double B, double C, double D) : A_(A), B_(B), C_(C), D_(D) {}

        plane_t(point_t a, point_t b, point_t c) {
            float a1 = b.x() - a.x();
            float b1 = b.y() - a.y();
            float c1 = b.z() - a.z();
            float a2 = c.x() - a.x();
            float b2 = c.y() - a.y();
            float c2 = c.z() - a.z();
            A_ = b1 * c2 - b2 * c1;
            B_ = a2 * c1 - a1 * c2;
            C_ = a1 * b2 - b1 * a2;
            D_ = (- A_ * a.x() - B_ * a.y() - C_ * a.z());
        }
        
        plane_t(segment_t ab, segment_t bc, segment_t ca) {
            point_t a = ab.first();
            point_t b = bc.first();
            point_t c = ca.first();

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

        double A() const { return A_; }
        double B() const { return B_; }
        double C() const { return C_; }
        double D() const { return D_; }
    };

    bool is_planes_parallel(const plane_t& a, const plane_t& b) {
        plane_t a_norm = a.norm();
        plane_t b_norm = b.norm();

        return (doubles::is_double_equal(a_norm.A(), b_norm.A()) &&
                doubles::is_double_equal(a_norm.B(), b_norm.B()) &&
                doubles::is_double_equal(a_norm.C(), b_norm.C()));
    }

    bool operator==(const plane_t& a, const plane_t& b) {
        plane_t a_norm = a.norm();
        plane_t b_norm = b.norm();

        return (is_planes_parallel(a, b) &&
                doubles::is_double_equal(a_norm.D(), b_norm.D()));
    }

    std::istream& operator>>(std::istream& is, plane_t& pl) {
        is >> pl.set_A() >> pl.set_B() >> pl.set_C() >> pl.set_D();
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const plane_t& pl) {
        os << print_lgreen("Plane(" << pl.A() << "," << pl.B() << "," << pl.C() << "," << pl.D() << ")");
        return os;
    }
}