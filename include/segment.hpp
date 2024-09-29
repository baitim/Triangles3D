#pragma once

#include "line.hpp"

namespace segment {
    using namespace line;

    template <typename T = double>
    struct coefs_t final {
        bool is_valid_;
        T k_;
        coefs_t() : is_valid_(false), k_(NAN) {}
        coefs_t(bool is_valid) : is_valid_(is_valid), k_(NAN) {}
        coefs_t(bool is_valid, T k) : is_valid_(is_valid), k_(k) {}
    };

    template <typename T = double>
    struct segment_t final {
        point_t<T> x_;
        point_t<T> y_;

        segment_t() : x_(), y_() {}
        segment_t(point_t<T> x, point_t<T> y) : x_(x), y_(y) {}
        segment_t(const segment_t<T>& segment) : x_(segment.x_), y_(segment.y_) {}

        bool is_valid() const {
            return (x_.is_valid() && y_.is_valid());
        }

        coefs_t<T> get_lines_intersect_parallel(const line_t<T>& line, const line_t<T>& seg_line) const {
            T line_xx = line.x_.x_;
            T line_vx = line.v_.x_;
            T seg_xx  = seg_line.x_.x_;
            T seg_vx  = seg_line.v_.x_;

            T k[4] = {};
            k[0] = (seg_xx - line_xx) / line_vx;
            k[1] = (seg_xx + seg_vx - line_xx) / line_vx;
            k[2] = (line_xx - seg_xx + seg_vx) / line_vx;
            k[3] = (line_xx - seg_xx + seg_vx) / line_vx;

            segment_t<T> valid_diap(0, 1);
            for (int i = 0; i < 4; ++i)
                if (valid_diap.is_point_in(k[i]))
                    return coefs_t<T>(true, k[i]);

            return coefs_t<T>{true, 0};
        }

        coefs_t<T> get_line_intersect(const line_t<T>& line) const { // a * (V1 x V2) = (P2 - P1) x V2
            if (!line.is_valid() || !is_valid())
                return coefs_t<T>(false);

            line_t<T> seg_line = line_t<T>(x_, y_ - x_);

            if (seg_line == line)
                return get_lines_intersect_parallel(line, seg_line);

            if (is_lines_parallel(seg_line, line))
                return coefs_t<T>{false};

            point_t<T> V1xV2 = cross_product(line.v_, seg_line.v_);
            point_t<T> dP    = x_ - line.x_;
            point_t<T> dPxV2 = cross_product(dP, seg_line.v_);

            point_t<T> V1xV2_norm = V1xV2.norm();
            point_t<T> dPxV2_norm = dPxV2.norm();

            if (V1xV2_norm   ==  dPxV2_norm ||
                V1xV2_norm   == -dPxV2_norm ||
                dPxV2.length() == 0) {

                T k = dPxV2.length() / V1xV2.length();
                if (V1xV2_norm == -dPxV2_norm)
                    k *= -1;

                if (!is_point_in(line.x_ + line.v_ * point_t<T>{k}))
                    return coefs_t<T>{false};

                return coefs_t<T>(true, k);
            }

            return coefs_t<T>{false};
        }

        bool is_segment_intersect(const segment_t<T>& segment) const {
            if (!segment.is_valid() || !is_valid())
                return false;

            point_t<T> segment_v(segment.y_ - segment.x_);
            line_t<T>  line(segment.x_, segment_v);

            coefs_t<T> coefs = get_line_intersect(line);
            segment_t<T> valid_diap(0, 1);

            if (!coefs.is_valid_ ||
                !valid_diap.is_point_in(coefs.k_))
                return false;

            T line_x = coefs.k_ * line.v_.x_ + line.x_.x_;
            if (is_reals_in_range(line_x, x_.x_, y_.x_))
                return true;

            return false;
        }

        bool is_point_in(const point_t<T>& p) const {
            if (!p.is_valid())
                return false;

            if (is_reals_eq((y_ - x_).length(), (p - x_).length() + (p - y_).length()))
                return true;
            
            return false;
        }
    };        

    template <typename T>
    bool is_points_segment(const point_t<T>& a, const point_t<T>& b, const point_t<T>& c) {
        if (!a.is_valid() ||
            !b.is_valid() ||
            !c.is_valid() ||
            (a == b && b == c))
            return false;

        line_t<T> ab(a, b - a);
        line_t<T> bc(b, c - b);

        return (is_lines_parallel(ab, bc) ||
                a == b ||
                b == c);
    }

    template <typename T>
    bool operator==(const segment_t<T>& a, const segment_t<T>& b) {
        return (a.x_ == b.x_ &&
                a.y_ == b.y_);
    }

    template <typename T>
    std::istream& operator>>(std::istream& is, segment_t<T>& s) {
        is >> s.x_ >> s.y_;
        return is;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const segment_t<T>& s) {
        os << print_lmagenta("Segment(") << s.x_ << print_lmagenta(",") << s.y_ <<
              print_lmagenta(")");
        return os;
    }
}