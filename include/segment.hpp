#pragma once

#include "line.hpp"

namespace segment {
    using namespace line;

    struct coefs_t final {
        bool is_valid_;
        double k1_, k2_;
        coefs_t(bool is_valid) : is_valid_(is_valid), k1_(NAN), k2_(NAN) {}
        coefs_t(bool is_valid, double k) : is_valid_(is_valid), k1_(k), k2_(NAN) {}
        coefs_t(bool is_valid, double k1, double k2) : is_valid_(is_valid), k1_(k1), k2_(k2) {}
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

        coefs_t get_line_intersect(const line_t& line) const { // a * (V1 x V2) = (P2 - P1) x V2
            if (!line.is_valid() || !is_valid())
                return coefs_t(false);

            line_t seg_line = line_t(x_, y_ - x_);

            double line_xx = line.get_x().get_x();
            double line_vx = line.get_v().get_x();
            double seg_xx  = seg_line.get_x().get_x();
            double seg_vx  = seg_line.get_v().get_x();

            if (seg_line == line) {
                double k1 = (line_xx - seg_xx) / seg_vx;
                double k2 = (seg_xx - line_xx + line_vx) / seg_vx;
                return coefs_t(true, k1, k2);
            }

            if (is_lines_parallel(seg_line, line))
                return coefs_t{false};

            point_t V1xV2 = cross_product(line.get_v(), seg_line.get_v());
            point_t dP    = x_ - line.get_x();
            point_t dPxV2 = cross_product(dP, seg_line.get_v());

            if (V1xV2.norm()   ==  dPxV2.norm() ||
                V1xV2.norm()   == -dPxV2.norm() ||
                dPxV2.length() == 0) {

                double k = dPxV2.length() / V1xV2.length();
                if (V1xV2.norm() == -dPxV2.norm())
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

            line_t line = line_t(segment.get_x(), segment.get_y() - segment.get_x());

            coefs_t coefs = get_line_intersect(line);
            if (!coefs.is_valid_)
                return false;

            double x = x_.get_x();
            double y = y_.get_x();

            coefs.k1_ = std::max((double)0, std::min((double)1, coefs.k1_));
            double line_x = coefs.k1_ * line.get_v().get_x() + line.get_x().get_x();
            if (is_double_in_range(line_x, x, y))
                return true;

            if (!std::isnan(coefs.k2_)) {
                coefs.k2_ = std::max((double)0, std::min((double)1, coefs.k2_));
                line_x = coefs.k2_ * line.get_v().get_x() + line.get_x().get_x();
                if (is_double_in_range(line_x, x, y))
                    return true;
            }

            return false;
        }

        bool is_point_in(const point_t& p) const {
            if (is_double_equal((y_ - x_).length(), (p - x_).length() + (p - y_).length()))
                return true;
            
            return false;
        }
    };

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