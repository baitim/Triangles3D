#include <iostream>
#include <set>
#include "triangle.hpp"

int main() {

    int count;
    std::cin >> count;

    triangle::triangle_t* triangles = new triangle::triangle_t[count];
    for (int i = 0; i < count; ++i)
        std::cin >> triangles[i];

    std::set<int> ans = get_set_triangles_in_intersections(count, triangles);
    for (auto it : ans)
        std::cout << it + 1 << "\n";

    delete [] triangles;
    return 0;
}