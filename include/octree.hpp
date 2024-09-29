#pragma once

#include <list>
#include <vector>
#include "triangle.hpp"

namespace octree {
    using namespace triangle;

    class octree_t final {
        int count_;
        std::list<std::pair<const triangle_t*, int>> triangles_;

        struct coords_t final {
            double c_[6]; //x1_, x2_, y1_, y2_, z1_, z2_

            coords_t() {}
            coords_t(double x1, double x2, double y1, double y2, double z1, double z2) {
                c_[0] = x1;
                c_[1] = x2;
                c_[2] = y1;
                c_[3] = y2;
                c_[4] = z1;
                c_[5] = z2;
            }
        };

        struct child_coords_t final {
            coords_t coords_[8];
            child_coords_t(const coords_t& coords) {
                double x_av = (coords.c_[0] + coords.c_[1]) / 2;
                double y_av = (coords.c_[2] + coords.c_[3]) / 2;
                double z_av = (coords.c_[4] + coords.c_[5]) / 2;

                for (int i = 0; i < 8; ++i) {
                    coords_[i] = coords;

                    if (i & 1) coords_[i].c_[0] = x_av;
                    else       coords_[i].c_[1] = x_av;
                    if (i & 2) coords_[i].c_[2] = y_av;
                    else       coords_[i].c_[3] = y_av;
                    if (i & 4) coords_[i].c_[4] = z_av;
                    else       coords_[i].c_[5] = z_av;
                }
            }
        };

        struct cube_t final {
            cube_t* parent = nullptr;
            cube_t* childs[8]{nullptr};
            int valid_childs[8]{};
            coords_t coords_;
            std::list<std::pair<const triangle_t*, int>> triangles_;

            cube_t(double x1, double x2, double y1, double y2, double z1, double z2) :
                   coords_(x1, x2, y1, y2, z1, z2) {}
            cube_t(const coords_t& coords) :
                   coords_(coords) {}

            bool is_triangle_in(const triangle_t& t) const {
                if (is_double_lt(t.get_min_x(), coords_.c_[0]) ||
                    is_double_gt(t.get_max_x(), coords_.c_[1]) ||
                    is_double_lt(t.get_min_y(), coords_.c_[2]) ||
                    is_double_gt(t.get_max_y(), coords_.c_[3]) ||
                    is_double_lt(t.get_min_z(), coords_.c_[4]) ||
                    is_double_gt(t.get_max_z(), coords_.c_[5]))
                    return false;

                return true;
            }
        };

        cube_t* root_;

    private:
        coords_t get_borders() const {
            coords_t coords;
            for (auto it : triangles_) {
                const triangle_t& triangle = *it.first;

                if (std::isnan(coords.c_[0]) || is_double_le(triangle.get_min_x(), coords.c_[0]))
                    coords.c_[0] = triangle.get_min_x();

                if (std::isnan(coords.c_[1]) || is_double_ge(triangle.get_max_x(), coords.c_[1]))
                    coords.c_[1] = triangle.get_max_x();

                if (std::isnan(coords.c_[2]) || is_double_le(triangle.get_min_y(), coords.c_[2]))
                    coords.c_[2] = triangle.get_min_y();

                if (std::isnan(coords.c_[3]) || is_double_ge(triangle.get_max_y(), coords.c_[3]))
                    coords.c_[3] = triangle.get_max_y();

                if (std::isnan(coords.c_[4]) || is_double_le(triangle.get_min_z(), coords.c_[4]))
                    coords.c_[4] = triangle.get_min_z();

                if (std::isnan(coords.c_[5]) || is_double_ge(triangle.get_max_z(), coords.c_[5]))
                    coords.c_[5] = triangle.get_max_z();
            }

            return coords;
        }

        int build_tree(cube_t*& cube, const coords_t& coords, int count,
                       const std::list<std::pair<const triangle_t*, int>>& triangles,
                       std::vector<bool>& in_childs_parent, int pp_childs) {

            cube = new cube_t{coords};
            int count_inside = 0;
            int i = 0;

            for (auto triangle : triangles) {
                if (cube->is_triangle_in(*triangle.first)) {
                    cube->triangles_.push_front(triangle);
                    count_inside++;
                    in_childs_parent[i] = true;
                }
                i++;
            }

            if (count_inside == pp_childs)
                return count_inside;

            if (count_inside == 0) {
                delete cube;
                return 0;
            }

            child_coords_t new_coords{coords};
            std::vector<bool> in_childs(count_inside, false);
            for (int i = 0; i < 8; ++i) {
                int count_inside_child = build_tree(cube->childs[i], new_coords.coords_[i],
                                                    count_inside, cube->triangles_, in_childs,
                                                    count);
                if (count_inside_child > 0) {
                    cube->childs[i]->parent = cube;
                    cube->valid_childs[i] = 1;
                }
            }
            
            int shift = 0;
            auto triangles_iter = cube->triangles_.begin();
            for (int j = 0; j < count_inside; ++j) {
                if (in_childs[j]) {
                    std::advance(triangles_iter, j - shift);
                    triangles_iter = cube->triangles_.erase(triangles_iter);
                    shift = j + 1;
                }
            }

            return count_inside;
        }

        void recursive_delete_tree(cube_t* cube) {
            for (int i = 0; i < 8; ++i)
                if (cube->valid_childs[i])
                    recursive_delete_tree(cube->childs[i]);

            delete cube;
        }

        void get_intersecting_triangles_in_cube(std::set<int>& ans, const cube_t* cube) const {
            for (int i = 0; i < 8; ++i)
                if (cube->valid_childs[i])
                    get_intersecting_triangles_in_cube(ans, cube->childs[i]);


            for (auto first_tr : cube->triangles_) {
                for (auto it = cube; it != nullptr; it = it->parent) {
                    for (auto second_tr : it->triangles_) {
                        if (first_tr.second == second_tr.second) 
                            continue;

                        if (is_triangles_intersect(*first_tr.first, *second_tr.first)) {
                            ans.insert(first_tr.second);
                            ans.insert(second_tr.second);
                        }
                    }
                }
            }
        }

    public:
        octree_t() : count_(0) {}
        octree_t(int count, const triangle_t* triangles) : count_(count) {
            for (int i = 0; i < count; ++i)
                triangles_.push_front(std::make_pair(&triangles[i], i));

            coords_t coords = get_borders();
            std::vector<bool> in_childs(count, false);
            build_tree(root_, coords, count_, triangles_, in_childs, -1);
        }

        std::set<int> get_set_intersecting_triangles() const {
            std::set<int> ans;
            get_intersecting_triangles_in_cube(ans, root_);
            return ans;
        }

        ~octree_t() {
            recursive_delete_tree(root_);
        }
    };
}