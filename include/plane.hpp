#pragma once

#include "segment.hpp"

namespace plane {
    using namespace segment;

    struct plane_t final {
        double A_, B_, C_, D_;

        plane_t() : A_(NAN), B_(NAN), C_(NAN), D_(NAN) {}
        plane_t(double A, double B, double C, double D) : A_(A), B_(B), C_(C), D_(D) {}

        plane_t(point_t a, point_t b, point_t c) {
            if (!is_points_set_plane(a, b, c)) {
                *this = plane_t();
                return;
            }

            point_t normal = cross_product(b - a, c - a);
            A_ = normal.x_;
            B_ = normal.y_;
            C_ = normal.z_;
            D_ = (- A_ * a.x_ - B_ * a.y_ - C_ * a.z_);
        }
        
        plane_t(segment_t ab, segment_t bc, segment_t ca) {
            point_t a = ab.x_;
            point_t b = bc.x_;
            point_t c = ca.x_;

            if (!is_points_set_plane(a, b, c)) {
                *this = plane_t();
                return;
            }

            *this = plane_t(a, b, c);
        }

        plane_t norm() const {
            plane_t norm{*this};

            double factor = 1;
            if (is_double_ne(A_, 0)) {
                factor /= A_;
            } else if (is_double_ne(B_, 0)) {
                factor /= B_;
            } else if (is_double_ne(C_, 0)) {
                factor /= C_;
            } else if (is_double_ne(D_, 0)) {
                factor /= D_;
            }

            norm.A_ *= factor;
            norm.B_ *= factor;
            norm.C_ *= factor;
            norm.D_ *= factor;

            return norm;
        }

        bool is_points_set_plane(const point_t& a, const point_t& b, const point_t& c) const {
            if (is_points_segment(a, b, c) ||
                (a == b && b == c)) {
                return false;
            }
            return true;
        }

        point_t normal() const {
            return point_t(A_, B_, C_);
        }

        double check_point_dot_plane(const point_t& v) const {
            return dot(normal(), v) + D_;
        }

        bool is_valid() const {
            return (!std::isnan(A_) &&
                    !std::isnan(B_) &&
                    !std::isnan(C_) &&
                    !std::isnan(D_));
        }

        bool is_point_in(const point_t& p) const {
            double res = p.x_ * A_ + p.y_ * B_ + p.z_ * C_ + D_;

            if (is_double_eq(res, 0))
                return true;

            return false;
        }

        point_t get_intersect_line(const line_t& line) const {
            double coef = (A_ * line.v_.x_ +
                           B_ * line.v_.y_ +
                           C_ * line.v_.z_);

            if (is_double_eq(coef, 0))
                return line.x_;

            double t = - (D_ + 
                          A_ * line.x_.x_ +
                          B_ * line.x_.y_ + 
                          C_ * line.x_.z_);

            t /= coef;

            double a = line.x_.x_ + line.v_.x_ * t;
            double b = line.x_.y_ + line.v_.y_ * t;
            double c = line.x_.z_ + line.v_.z_ * t;

            return (point_t){a, b, c};
        }
    };

    bool is_planes_parallel(const plane_t& a, const plane_t& b) {
        return (a.norm().normal() == b.norm().normal());
    }

    line_t get_planes_intersection(const plane_t& a, const plane_t& b) {
        if (!a.is_valid() || !b.is_valid() || is_planes_parallel(a, b))
            return line_t();

        point_t line_v = cross_product(a.normal(), b.normal()).norm();
        double x = 0, y = 0, z = 0;

        if (is_double_ne(a.A_, 0)) x = - a.D_ / a.A_;
        if (is_double_ne(b.A_, 0)) x = - b.D_ / b.A_;

        double coef = a.B_ * b.C_ - a.C_ * b.B_;
        if (is_double_ne(coef, 0)) {
            y = (a.C_ * (b.D_ + b.A_ * x)) -
                (b.C_ * (a.D_ + a.A_ * x));

            y /= coef;
        }

        if (is_double_ne(a.C_, 0))
            z = -(a.D_ + a.A_ * x + a.B_ * y) / a.C_;
        else if (is_double_ne(b.C_, 0))
            z = -(b.D_ + b.A_ * x + b.B_ * y) / b.C_;

        point_t line_point(x, y, z);
        return line_t(line_point, line_v);
    }

    bool operator==(const plane_t& a, const plane_t& b) {
        plane_t a_norm = a.norm();
        plane_t b_norm = b.norm();

        return (is_planes_parallel(a, b) &&
                is_double_eq(a_norm.D_, b_norm.D_));
    }

    bool operator!=(const plane_t& a, const plane_t& b) {
        return !(a == b);
    }

    std::istream& operator>>(std::istream& is, plane_t& pl) {
        is >> pl.A_ >> pl.B_ >> pl.C_ >> pl.D_;
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const plane_t& pl) {
        os << print_lgreen("Plane(" << pl.A_ << "," << pl.B_ << "," << pl.C_ <<
                           "," << pl.D_ << ")");
        return os;
    }
}