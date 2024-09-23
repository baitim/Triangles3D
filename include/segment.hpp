#pragma once

#include "line.hpp"

namespace segment {
    using namespace line;

    struct coefs_t final {
        bool is_valid_;
        double k_;
        coefs_t() : is_valid_(false), k_(NAN) {}
        coefs_t(bool is_valid) : is_valid_(is_valid), k_(NAN) {}
        coefs_t(bool is_valid, double k) : is_valid_(is_valid), k_(k) {}
    };

    class segment_t final {
        point_t x_;
        point_t y_;

    public:
        segment_t() : x_(), y_() {}
        segment_t(point_t x, point_t y) : x_(x), y_(y) {}

        point_t& set_x() { return x_; }
        point_t& set_y() { return y_; }

        point_t get_x() const { return x_; }
        point_t get_y() const { return y_; }

        bool is_valid() const {
            return (x_.is_valid() && y_.is_valid());
        }

        coefs_t get_lines_intersect_parallel(const line_t& line, const line_t& seg_line) const {
            double line_xx = line.get_x().get_x();
            double line_vx = line.get_v().get_x();
            double seg_xx  = seg_line.get_x().get_x();
            double seg_vx  = seg_line.get_v().get_x();

            double k[4] = {};
            k[0] = (seg_xx - line_xx) / line_vx;
            k[1] = (seg_xx + seg_vx - line_xx) / line_vx;
            k[2] = (line_xx - seg_xx + seg_vx) / line_vx;
            k[3] = (line_xx - seg_xx + seg_vx) / line_vx;

            segment_t valid_diap(0, 1);
            for (int i = 0; i < 4; ++i)
                if (valid_diap.is_point_in(k[i]))
                    return coefs_t(true, k[i]);

            return coefs_t{true, 0};
        }

        coefs_t get_line_intersect(const line_t& line) const { // a * (V1 x V2) = (P2 - P1) x V2
            if (!line.is_valid() || !is_valid())
                return coefs_t(false);

            line_t seg_line = line_t(x_, y_ - x_);

            if (seg_line == line)
                return get_lines_intersect_parallel(line, seg_line);

            if (is_lines_parallel(seg_line, line))
                return coefs_t{false};

            point_t V1xV2 = cross_product(line.get_v(), seg_line.get_v());
            point_t dP    = x_ - line.get_x();
            point_t dPxV2 = cross_product(dP, seg_line.get_v());

            point_t V1xV2_norm = V1xV2.norm();
            point_t dPxV2_norm = dPxV2.norm();

            if (V1xV2_norm   ==  dPxV2_norm ||
                V1xV2_norm   == -dPxV2_norm ||
                dPxV2.length() == 0) {

                double k = dPxV2.length() / V1xV2.length();
                if (V1xV2_norm == -dPxV2_norm)
                    k *= -1;

                if (!is_point_in(line.get_x() + line.get_v() * k))
                    return coefs_t{false};

                return coefs_t(true, k);
            }

            return coefs_t{false};
        }

        bool is_segment_intersect(const segment_t& segment) const {
            if (!segment.is_valid() || !is_valid())
                return false;

            point_t segment_v(segment.get_y() - segment.get_x());
            line_t  line(segment.get_x(), segment_v);

            coefs_t coefs = get_line_intersect(line);
            segment_t valid_diap(0, 1);

            if (!coefs.is_valid_ ||
                !valid_diap.is_point_in(coefs.k_))
                return false;

            double line_x = coefs.k_ * line.get_v().get_x() + line.get_x().get_x();
            if (is_double_in_range(line_x, x_.get_x(), y_.get_x()))
                return true;

            return false;
        }

        bool is_point_in(const point_t& p) const {
            if (!p.is_valid())
                return false;

            if (is_double_eq((y_ - x_).length(), (p - x_).length() + (p - y_).length()))
                return true;
            
            return false;
        }
    };        

    bool is_points_segment(const point_t& a, const point_t& b, const point_t& c) {
        if (!a.is_valid() ||
            !b.is_valid() ||
            !c.is_valid() ||
            (a == b && b == c))
            return false;

        line_t ab(a, b - a);
        line_t bc(b, c - b);

        return (is_lines_parallel(ab, bc) ||
                a == b ||
                b == c);
    }

    bool operator==(const segment_t& a, const segment_t& b) {
        return (a.get_x() == b.get_x() &&
                a.get_y() == b.get_y());
    }

    std::istream& operator>>(std::istream& is, segment_t& s) {
        is >> s.set_x() >> s.set_y();
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const segment_t& s) {
        os << print_lmagenta("Segment(") << s.get_x() << print_lmagenta(",") << s.get_y() <<
              print_lmagenta(")");
        return os;
    }
}