#pragma once

#include <cmath>

namespace doubles {
    const double EPSILON = 1e-8;

    bool is_double_equal(double a, double b) noexcept {
        return (std::fabs(a - b) < EPSILON);
    }

    bool is_double_greater(double a, double b) noexcept {
        return ((a - b) > EPSILON);
    }

    bool is_double_less(double a, double b) noexcept {
        return ((a - b) < EPSILON);
    }

    bool is_double_in_range(double a, double b, double c) noexcept {
        if (is_double_equal(a, b) || is_double_equal(a, c))
            return true;

        if (is_double_less(a, b) && is_double_greater(a, c))
            return true;

        if (is_double_less(a, c) && is_double_greater(a, b))
            return true;

        return false;
    }
}