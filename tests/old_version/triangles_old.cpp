#include <iostream>
#include <set>
#include "triangle_old.hpp"

int main() {

    std::cout.sync_with_stdio(0);
    std::cin.tie(0);

    int count;
    std::cin >> count;

    triangle_old::triangle_t* triangles = new triangle_old::triangle_t[count];
    for (int i = 0; i < count; ++i)
        std::cin >> triangles[i];

    std::set<int> ans = triangle_old::get_set_triangles_in_intersections_old(count, triangles);
    for (auto it : ans)
        std::cout << it << "\n";

    delete [] triangles;
    return 0;
}