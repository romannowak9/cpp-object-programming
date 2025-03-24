#include "TSP.hpp"

#include <iostream>


int main() {
    cost_matrix_t cm = {{INF, 10, 8,   19, 12},
                      {10, INF, 20,  6,  3},
                      {8,   20, INF, 4,  2},
                      {19,  6,  4, INF,  7},
                      {12,  3,  2,   7, INF}};

    /* Rozwiązania:
     * 32 : 2 3 4 1 0
     * 32 : 1 4 3 2 0
     */

//    cost_matrix_t cm {
//            {INF, 12,   3,  45,   6},
//            {78, INF,  90,  21,   3},
//            { 5,  56, INF,  23,  98},
//            {12,   6,   8, INF,  34},
//            { 3,  98,   3,   2, INF}
//    };

    /* Rozwiązanie:
     * 30 : 4 3 2 0 1
    */

//    cost_matrix_t cm {
//            {INF,  3,  4,  2,  7},
//            {3,  INF,  4,  6,  3},
//            {4,  4,  INF,  5,  8},
//            {2,  6,  5,  INF,  6},
//            {7,  3,  8,  6,  INF},
//    };

    /* Rozwiązania:
     * 19 : 4 3 0 2 1
     * 19 : 1 2 0 3 4
    */

//    StageState left_branch(cm);
//    std::cout << "Start\n" << left_branch.get_matrix() << '\n';
//    const std::vector<cost_t> min_rows = left_branch.get_matrix().get_min_values_in_rows();
//    const std::vector<cost_t> min_cols = left_branch.get_matrix().get_min_values_in_cols();
//    std::cout << "min v in rows: ";
//    for (const auto el : min_rows)
//        std::cout << el << ',';
//    std::cout << '\n';
//    std::cout << "min v in cols: ";
//    for (const auto el : min_cols)
//        std::cout << el << ',';
//    std::cout << '\n';

//    std::cout << "Start\n" << left_branch.get_matrix() << '\n';
//    std::cout << "vertex(2,3) cost: " << left_branch.get_matrix().get_vertex_cost(2,3) << '\n';
//    cost_t bound = left_branch.reduce_cost_matrix();
//    std::cout << "bound: " << bound << '\n';
//
//    std::cout << "Reduced\n" << left_branch.get_matrix() << '\n';
//    bound = left_branch.reduce_cost_matrix();
//    left_branch.update_cost_matrix(left_branch.choose_new_vertex().coordinates);
//    std::cout << "bound: " << bound << '\n';
//
//    std::cout << "Reduced\n" << left_branch.get_matrix() << '\n';
//    bound = left_branch.reduce_cost_matrix();
//    left_branch.update_cost_matrix(left_branch.choose_new_vertex().coordinates);
//    std::cout << "bound: " << bound << '\n';
//
//    std::cout << "Reduced\n" << left_branch.get_matrix() << '\n';
//    const std::vector<cost_t> min_rows = left_branch.get_matrix().get_min_values_in_rows();
//    const std::vector<cost_t> min_cols = left_branch.get_matrix().get_min_values_in_cols();
//    std::cout << "min v in rows: ";
//    for (const auto el : min_rows)
//        std::cout << el << ',';
//    std::cout << '\n';
//    std::cout << "min v in cols: ";
//    for (const auto el : min_cols)
//        std::cout << el << ',';
//    std::cout << '\n';
//    bound = left_branch.reduce_cost_matrix();
//    left_branch.update_cost_matrix(left_branch.choose_new_vertex().coordinates);
//    std::cout << "bound: " << bound << '\n';




//    // The number of levels determines the number of steps before obtaining
//    // a 2x2 matrix.
//    std::size_t n_levels = cm.size() - 2;
//
//    cost_t best_lb = INF;
//
//    while (left_branch.get_level() != n_levels && left_branch.get_lower_bound() <= best_lb) {
//
//        std::cout << "Start\n" << left_branch.get_matrix();
//        // Repeat until a 2x2 matrix is obtained or the lower bound is too high...
//        if (left_branch.get_level() == 0)
//            left_branch.reset_lower_bound();
//        // 1. Reduce the matrix in rows and columns.
//        cost_t new_cost = left_branch.reduce_cost_matrix();
//        std::cout << "Reduce\n" << left_branch.get_matrix();
//        // 2. Update the lower bound and check the break condition.
//        left_branch.update_lower_bound(new_cost);
//        if (left_branch.get_lower_bound() > best_lb)
//            break;
//        // 3. Get new vertex and the cost of not choosing it.
//        NewVertex new_vertex = left_branch.choose_new_vertex();
//        left_branch.append_to_path(new_vertex.coordinates);
//        std::cout << "New cost: " << new_vertex.cost << '\n';
//        for (const auto& el : left_branch.get_unsorted_path()){
//            std::cout << el.row + 1 << ' ' << el.col + 1 << ", ";
//        }
//        std::cout << '\n';
//        left_branch.update_cost_matrix(new_vertex.coordinates);
//        std::cout << "Update\n" << left_branch.get_matrix();
//
//    }
//
//    left_branch.get_path();
//
//    for (const auto& el : left_branch.get_unsorted_path()){
//        std::cout << el.row + 1 << ' ' << el.col + 1 << ", ";
//    }
//    std::cout << '\n';

    tsp_solutions_t solutions = solve_tsp(cm);

    for (auto& elem : solutions) {
        std::cout << elem.lower_bound << " : ";
        for (auto pelem : elem.path) {
            std::cout << pelem << " ";
        }
        std::cout << "\n";
    }

    return EXIT_SUCCESS;
}
