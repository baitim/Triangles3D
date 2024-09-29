#include <iostream>
#include <set>
#include "octree.hpp"

int main() {

    std::cout.sync_with_stdio(0);
    std::cin.tie(0);

    int count;
    std::cin >> count;

    triangle::triangle_t<>* triangles = new triangle::triangle_t<>[count];
    for (int i = 0; i < count; ++i)
        std::cin >> triangles[i];

    octree::octree_t<> octree(count, triangles);
    std::set<int> ans = octree.get_set_intersecting_triangles();
    for (auto it : ans)
        std::cout << it << "\n";

    delete [] triangles;
    return 0;
}