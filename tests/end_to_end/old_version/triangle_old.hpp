#pragma once

#include <set>
#include "triangle.hpp"

namespace triangle_old {
    using namespace triangle;
    
    template <typename It>
    std::set<int> get_set_triangles_in_intersections_old(int count, It tr_begin, It tr_end) {
        std::set<int> ans;
        int i = 0;
        for (It it1 = tr_begin; it1 != tr_end; ++it1, ++i) {
            int j = i + 1;
            for (It it2 = it1 + 1; it2 != tr_end; ++it2, ++j) {
                if (is_triangles_intersect(*it1, *it2) ||
                    is_triangles_intersect(*it2, *it1)) {
                    ans.insert(i);
                    ans.insert(j);
                }
            }
        }
        return ans;
    }
}