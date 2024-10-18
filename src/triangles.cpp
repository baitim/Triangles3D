#include <iostream>
#include <set>
#include <vector>
#include "octree.hpp"

int main() {

    std::cout.sync_with_stdio(0);
    std::cin.tie(0);

    int count;
    std::cin >> count;

    std::vector<triangle::triangle_t<>> triangles(count);
    for (int i = 0; i < count; ++i)
        std::cin >> triangles[i];

    std::set<int> ans = octree::get_set_intersecting_triangles(count, triangles.begin(), triangles.end());
    for (auto it : ans)
        std::cout << it << "\n";

    return 0;
}