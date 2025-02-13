#pragma once

#include "segment.hpp"

namespace plane {
    using namespace segment;

    template <typename T = double>
    struct plane_t final {
        T A_, B_, C_, D_;

        plane_t() : A_(NAN), B_(NAN), C_(NAN), D_(NAN) {}
        plane_t(T A, T B, T C, T D) : A_(A), B_(B), C_(C), D_(D) {}
        plane_t(const plane_t<T>& plane) : A_(plane.A_), B_(plane.B_), C_(plane.C_), D_(plane.D_) {}

        template <typename U>
        plane_t(const plane_t<U>& plane) : A_(static_cast<T>(plane.A_)),
                                           B_(static_cast<T>(plane.B_)),
                                           C_(static_cast<T>(plane.C_)),
                                           D_(static_cast<T>(plane.D_)) {}

        plane_t(point_t<T> a, point_t<T> b, point_t<T> c) {
            if (!is_points_set_plane(a, b, c)) {
                *this = plane_t<T>();
                return;
            }

            point_t<T> normal = cross_product(b - a, c - a);
            A_ = normal.x_;
            B_ = normal.y_;
            C_ = normal.z_;
            D_ = (- A_ * a.x_ - B_ * a.y_ - C_ * a.z_);
        }
        
        plane_t(segment_t<T> ab, segment_t<T> bc, segment_t<T> ca) {
            point_t<T> a = ab.x_;
            point_t<T> b = bc.x_;
            point_t<T> c = ca.x_;

            if (!is_points_set_plane(a, b, c)) {
                *this = plane_t<T>();
                return;
            }

            *this = plane_t<T>(a, b, c);
        }

        plane_t<T> norm() const {
            plane_t<T> norm{*this};
            T zero_p{0};

            T factor = 1;
            if (is_real_ne(A_, zero_p)) {
                factor /= A_;
            } else if (is_real_ne(B_, zero_p)) {
                factor /= B_;
            } else if (is_real_ne(C_, zero_p)) {
                factor /= C_;
            } else if (is_real_ne(D_, zero_p)) {
                factor /= D_;
            }

            norm.A_ *= factor;
            norm.B_ *= factor;
            norm.C_ *= factor;
            norm.D_ *= factor;

            return norm;
        }

        bool is_points_set_plane(const point_t<T>& a, const point_t<T>& b, const point_t<T>& c) const {
            if (is_points_segment(a, b, c) ||
                (a == b && b == c)) {
                return false;
            }
            return true;
        }

        point_t<T> normal() const {
            return point_t<T>(A_, B_, C_);
        }

        T check_point_dot_plane(const point_t<T>& v) const {
            return dot(normal(), v) + D_;
        }

        bool is_valid() const {
            return !(A_ != A_ ||
                     B_ != B_ ||
                     C_ != C_ ||
                     D_ != D_);
        }

        bool is_point_in(const point_t<T>& p) const {
            T res = p.x_ * A_ + p.y_ * B_ + p.z_ * C_ + D_;

            if (is_double_eq(res, 0))
                return true;

            return false;
        }

        point_t<T> get_intersect_line(const line_t<T>& line) const {
            T coef = (A_ * line.v_.x_ +
                           B_ * line.v_.y_ +
                           C_ * line.v_.z_);

            if (is_real_eq(coef, T{0}))
                return line.x_;

            T t = - (D_ + 
                     A_ * line.x_.x_ +
                     B_ * line.x_.y_ + 
                     C_ * line.x_.z_);

            t /= coef;

            T a = line.x_.x_ + line.v_.x_ * t;
            T b = line.x_.y_ + line.v_.y_ * t;
            T c = line.x_.z_ + line.v_.z_ * t;

            return (point_t<T>){a, b, c};
        }
    };

    template <typename T>
    bool is_planes_parallel(const plane_t<T>& a, const plane_t<T>& b) {
        return (a.norm().normal() == b.norm().normal());
    }

    template <typename T>
    line_t<T> get_planes_intersection(const plane_t<T>& a, const plane_t<T>& b) {
        if (!a.is_valid() || !b.is_valid() || is_planes_parallel(a, b))
            return line_t<T>();

        point_t<T> line_v = cross_product(a.normal(), b.normal()).norm();
        T x = 0, y = 0, z = 0;
        T zero_p{0};

        if (is_real_ne(a.A_, zero_p)) x = - a.D_ / a.A_;
        if (is_real_ne(b.A_, zero_p)) x = - b.D_ / b.A_;

        T coef = a.B_ * b.C_ - a.C_ * b.B_;
        if (is_real_ne(coef, zero_p)) {
            y = (a.C_ * (b.D_ + b.A_ * x)) -
                (b.C_ * (a.D_ + a.A_ * x));

            y /= coef;
        }

        if (is_real_ne(a.C_, zero_p))
            z = -(a.D_ + a.A_ * x + a.B_ * y) / a.C_;
        else if (is_real_ne(b.C_, zero_p))
            z = -(b.D_ + b.A_ * x + b.B_ * y) / b.C_;

        point_t<T> line_point(x, y, z);
        return line_t<T>(line_point, line_v);
    }

    template <typename T>
    bool operator==(const plane_t<T>& a, const plane_t<T>& b) {
        plane_t<T> a_norm = a.norm();
        plane_t<T> b_norm = b.norm();

        return (is_planes_parallel(a, b) &&
                is_real_eq(a_norm.D_, b_norm.D_));
    }

    template <typename T>
    bool operator!=(const plane_t<T>& a, const plane_t<T>& b) {
        return !(a == b);
    }

    template <typename T>
    std::istream& operator>>(std::istream& is, plane_t<T>& pl) {
        is >> pl.A_ >> pl.B_ >> pl.C_ >> pl.D_;
        return is;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const plane_t<T>& pl) {
        os << print_lgreen("Plane(" << pl.A_ << "," << pl.B_ << "," << pl.C_ <<
                           "," << pl.D_ << ")");
        return os;
    }
}