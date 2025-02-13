#include "Triangles3D/octree.hpp"
#include <iostream>
#include <vector>

int main() {

    std::cout.sync_with_stdio(0);
    std::cin.tie(0);

    int count;
    std::cin >> count;

    std::vector<triangle::triangle_t<>> triangles(count);
    for (int i = 0; i < count; ++i)
        std::cin >> triangles[i];

    octree::octree_t<> octree(count, triangles.begin(), triangles.end());
    std::set<int> ans = octree.get_set_intersecting_triangles();
    for (auto it : ans)
        std::cout << it << "\n";

    return 0;
}