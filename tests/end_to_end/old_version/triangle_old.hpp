#pragma once

#include <set>
#include "triangle.hpp"

namespace triangle_old {
    using namespace triangle;
    
    std::set<int> get_set_triangles_in_intersections_old(int count, const triangle_t* tr) {
        std::set<int> ans;
        for (int i = 0; i < count; ++i) {
            for (int j = i + 1; j < count; ++j) {
                if (is_triangles_intersect(tr[i], tr[j]) ||
                    is_triangles_intersect(tr[j], tr[i])) {
                    ans.insert(i);
                    ans.insert(j);
                }
            }
        }
        return ans;
    }
}