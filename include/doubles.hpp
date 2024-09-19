#pragma once

#include <cmath>

namespace doubles {
    const double EPSILON = 1e-8;

    bool is_double_eq(double a, double b) noexcept {
        return (std::fabs(a - b) < EPSILON);
    }

    bool is_double_ne(double a, double b) noexcept {
        return (std::fabs(a - b) > EPSILON);
    }

    bool is_double_lt(double a, double b) noexcept {
        return ((a - b) < -EPSILON);
    }

    bool is_double_le(double a, double b) noexcept {
        return ((a - b) < EPSILON);
    }

    bool is_double_gt(double a, double b) noexcept {
        return ((a - b) > EPSILON);
    }

    bool is_double_ge(double a, double b) noexcept {
        return ((a - b) > -EPSILON);
    }

    bool is_double_in_range(double a, double b, double c) noexcept {
        if (is_double_le(a, b) && is_double_ge(a, c))
            return true;

        if (is_double_le(a, c) && is_double_ge(a, b))
            return true;

        return false;
    }
}