#pragma once

#include <cmath>

namespace real_numbers {
    const double EPSILON = 1e-8;

    template <typename T = double>
    bool is_real_eq(T a, T b) noexcept {
        return (std::fabs(a - b) < EPSILON);
    }

    template <typename T = double>
    bool is_real_ne(T a, T b) noexcept {
        return (std::fabs(a - b) > EPSILON);
    }

    template <typename T = double>
    bool is_real_lt(T a, T b) noexcept {
        return ((a - b) < -EPSILON);
    }

    template <typename T = double>
    bool is_real_le(T a, T b) noexcept {
        return ((a - b) < EPSILON);
    }

    template <typename T = double>
    bool is_real_gt(T a, T b) noexcept {
        return ((a - b) > EPSILON);
    }

    template <typename T = double>
    bool is_real_ge(T a, T b) noexcept {
        return ((a - b) > -EPSILON);
    }

    template <typename T = double>
    bool is_real_in_range(T a, T b, T c) noexcept {
        if (is_real_le(a, b) && is_real_ge(a, c))
            return true;

        if (is_real_le(a, c) && is_real_ge(a, b))
            return true;

        return false;
    }
}