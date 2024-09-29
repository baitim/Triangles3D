#pragma once

#include <cmath>

namespace reals_numbers {
    const double EPSILON = 1e-8;

    template <typename T = double>
    bool is_reals_eq(T a, T b) noexcept {
        return (std::fabs(a - b) < EPSILON);
    }

    template <typename T = double>
    bool is_reals_ne(T a, T b) noexcept {
        return (std::fabs(a - b) > EPSILON);
    }

    template <typename T = double>
    bool is_reals_lt(T a, T b) noexcept {
        return ((a - b) < -EPSILON);
    }

    template <typename T = double>
    bool is_reals_le(T a, T b) noexcept {
        return ((a - b) < EPSILON);
    }

    template <typename T = double>
    bool is_reals_gt(T a, T b) noexcept {
        return ((a - b) > EPSILON);
    }

    template <typename T = double>
    bool is_reals_ge(T a, T b) noexcept {
        return ((a - b) > -EPSILON);
    }

    template <typename T = double>
    bool is_reals_in_range(T a, T b, T c) noexcept {
        if (is_reals_le(a, b) && is_reals_ge(a, c))
            return true;

        if (is_reals_le(a, c) && is_reals_ge(a, b))
            return true;

        return false;
    }
}