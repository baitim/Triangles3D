#include <iostream>
#include <set>
#include "triangle_old.hpp"

int main() {

    std::cout.sync_with_stdio(0);
    std::cin.tie(0);

    int count;
    std::cin >> count;

    std::vector<triangle_old::triangle_t<>> triangles(count);
    for (int i = 0; i < count; ++i)
        std::cin >> triangles[i];

    std::set<int> ans = triangle_old::get_set_triangles_in_intersections_old(count, triangles.begin(),
                                                                                    triangles.end());
    for (auto it : ans)
        std::cout << it << "\n";

    return 0;
}