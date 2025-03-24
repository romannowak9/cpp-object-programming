#include "TSP.hpp"

#include <algorithm>
#include <stack>
#include <optional>
#include <vector>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const CostMatrix& cm) {
    for (std::size_t r = 0; r < cm.size(); ++r) {
        for (std::size_t c = 0; c < cm.size(); ++c) {
            const auto& elem = cm[r][c];
            os << (is_inf(elem) ? "INF" : (elem >= 10 ? std::to_string(elem) + " " : std::to_string(elem) + "  "))
               << " ";
        }
        os << "\n";
    }
    os << std::endl;

    return os;
}

unsorted_path_t sort_path(const unsorted_path_t& unsorted_path) {
    unsorted_path_t path = unsorted_path;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        for (size_t j = 0; j < path.size(); ++j) {
            if (path[i].row != unsorted_path[j].row and path[i].col == unsorted_path[j].row) {
                path[i + 1] = unsorted_path[j];
                break;
            }
        }
    }
    return path;
}

/* PART 1 */

/**
 * Create path from unsorted path and last 2x2 cost matrix.
 * @return The vector of consecutive vertex.
 */
path_t StageState::get_path() {
    reduce_cost_matrix();
    vertex_t new_vertex = choose_new_vertex().coordinates;
    append_to_path(new_vertex);

//    for (const auto& el : unsorted_path_)
//        std::cout << el.row + 1 << ' ' << el.col + 1 << ", ";
//    std::cout << '\n';

//    std::cout << "Reduce\n" << matrix_;
    //update_cost_matrix(new_vertex);
    for (std::size_t i = 0; i != matrix_.size(); ++i) {
        matrix_[new_vertex.row][i] = INF;
        matrix_[i][new_vertex.col] = INF;
    }
//    std::cout << "Update\n" << matrix_;

    for (std::size_t i = 0; i != matrix_.size(); ++i) {
        for (std::size_t j = 0; j != matrix_[0].size(); ++j) {
            if (matrix_[i][j] != INF) {
                vertex_t last_vertex(i, j);
                append_to_path(last_vertex);
                break;
            }
        }
    }

//    for (const auto& el : unsorted_path_)
//        std::cout << el.row + 1 << ' ' << el.col + 1 << ", ";
//    std::cout << '\n';

    unsorted_path_t path = sort_path(get_unsorted_path());

//    for (const auto& el : path)
//        std::cout << el.row + 1 << ' ' << el.col + 1 << ", ";
//    std::cout << '\n';

    path_t sorted_path;

    for (auto& el: path)
        sorted_path.push_back(el.col);

//    for (const auto& el : sorted_path)
//        std::cout << el << ", ";
//    std::cout << '\n';

    return sorted_path;
}

/**
 * Get minimum values from each row and returns them.
 * @return Vector of minimum values in row.
 */
std::vector<cost_t> CostMatrix::get_min_values_in_rows() const {
    std::vector<cost_t> min_values;
    cost_t min_el;
    for (auto& row: matrix_) {
        min_el = *std::min_element(row.begin(), row.end());
        if (not is_inf(min_el))
            min_values.push_back(*std::min_element(row.begin(), row.end()));
        else
            min_values.push_back(0);
    }
    return min_values;
}

/**
 * Reduce rows so that in each row at least one zero value is present.
 * @return Sum of values reduced in rows.
 */
cost_t CostMatrix::reduce_rows() {
    const std::vector<cost_t> min_values = get_min_values_in_rows();
    for (std::size_t i = 0; i < matrix_.size(); ++i) {
        for (std::size_t j = 0; j < matrix_.size(); ++j) {
            if (matrix_[i][j] != INF)
                matrix_[i][j] -= min_values[i];
        }
    }
    return std::accumulate(min_values.begin(), min_values.end(), 0);
}

cost_matrix_t transpose_matrix(const cost_matrix_t& matrix) {
    cost_matrix_t t_matrix(matrix[0].size(), std::vector<cost_t>(matrix.size(), 0));
    for (std::size_t i = 0; i < matrix.size(); ++i) {
        for (std::size_t j = 0; j < matrix.size(); ++j)
            t_matrix[i][j] = matrix[j][i];
    }
    return t_matrix;
}

/**
 * Get minimum values from each column and returns them.
 * @return Vector of minimum values in columns.
 */
std::vector<cost_t> CostMatrix::get_min_values_in_cols() const {
    const cost_matrix_t t_matrix = transpose_matrix(matrix_);
    std::vector<cost_t> min_values;
    cost_t min_el;
    for (auto& row: t_matrix) {
        min_el = *std::min_element(row.begin(), row.end());
        if (not is_inf(min_el))
            min_values.push_back(*std::min_element(row.begin(), row.end()));
        else
            min_values.push_back(0);
    }
    return min_values;
}

/**
 * Reduces rows so that in each column at least one zero value is present.
 * @return Sum of values reduced in columns.
 */
cost_t CostMatrix::reduce_cols() {
    const std::vector<cost_t> min_values = get_min_values_in_cols();
    for (std::size_t i = 0; i < matrix_.size(); ++i) {
        for (std::size_t j = 0; j < matrix_[0].size(); ++j) {
            if (matrix_[j][i] != INF)
                matrix_[j][i] -= min_values[i];
        }
    }
    return std::accumulate(min_values.begin(), min_values.end(), 0);
}

/**
 * Get the cost of not visiting the vertex_t (@see: get_new_vertex())
 * @param row
 * @param col
 * @return The sum of minimal values in row and col, excluding the intersection value.
 */
cost_t CostMatrix::get_vertex_cost(std::size_t row, std::size_t col) const {
    std::vector<cost_t> col_values;
    for (std::size_t i = 0; i < matrix_[0].size(); ++i) {
        if (i == row)
            continue;
        col_values.push_back(matrix_[i][col]);
    }

    cost_t min_col_value = *std::min_element(col_values.begin(), col_values.end());

    std::vector<cost_t> row_values = matrix_[row];
    row_values[col] = INF;

    cost_t min_row_value = *std::min_element(row_values.begin(), row_values.end());

    if (is_inf(min_col_value))
        min_col_value = 0;

    if (is_inf(min_row_value))
        min_row_value = 0;

    return min_col_value + min_row_value;
}

/* PART 2 */

/**
 * Choose next vertex to visit:
 * - Look for vertex_t (pair row and column) with value 0 in the current cost matrix.
 * - Get the vertex_t cost (calls get_vertex_cost()).
 * - Choose the vertex_t with maximum cost and returns it.
 * @param cm
 * @return The coordinates of the next vertex.
 */
NewVertex StageState::choose_new_vertex() {
    cost_t max_vertex_cost = -1;
    vertex_t vertex_cord(0, 0);
    cost_t vertex_cost;
    for (std::size_t i = 0; i != matrix_.size(); ++i) {
        for (std::size_t j = 0; j != matrix_[0].size(); ++j) {
            if (matrix_[i][j] == 0) {
                vertex_cost = matrix_.get_vertex_cost(i, j);

//                std::cout << vertex_cost << ';';

                if (vertex_cost > max_vertex_cost) {
                    max_vertex_cost = vertex_cost;
                    vertex_cord.row = i;
                    vertex_cord.col = j;
                }
            }
        }
    }
    return {vertex_cord, max_vertex_cost};
}

/**
 * Update the cost matrix with the new vertex.
 * @param new_vertex
 */
void StageState::update_cost_matrix(vertex_t new_vertex) {
    const size_t v_row = new_vertex.row;
    const size_t v_col = new_vertex.col;
    for (std::size_t i = 0; i != matrix_.size(); ++i) {
        matrix_[v_row][i] = INF;
        matrix_[i][v_col] = INF;
    }
    matrix_[v_col][v_row] = INF;
    //  Kolejne cykle (?)
    //  Czyli sprawdzić czy dodana krawędź (new_vertex), nie powoduje
    //  możliwości powstania cyklu (nie obejmującego jeszcze wszystkich wierzchołków) po dodaniu jednej
    //  z dostępnych krawędzi i jeżeli by powodowała, to dać INF tej krawędzi po której dodaniu powstawałby cykl
    //  get_level(), unsorted_path_, nieposortowana ścieżka to wektor krawędzi (vertex_t), posortowana - wierzchołków

    unsorted_path_t unsort_path;
    unsorted_path_t path;
    vertex_t vertex(0, 0);
    bool is_cycle = true;

    for (std::size_t i = 0; i != matrix_.size(); ++i) {
        for (std::size_t j = 0; j != matrix_[0].size(); ++j) {
            if (not is_inf(matrix_[i][j])) {
                vertex.row = i;
                vertex.col = j;
                unsort_path = get_unsorted_path();
                unsort_path.push_back(vertex);
                path = sort_path(unsort_path);
                for (std::size_t k = 0; k != path.size() - 1; ++k) {
                    if (path[k].col != path[k + 1].row) {
                        is_cycle = false;
                        break;
                    }
                }
                if ((path.end() - 1)->col != path[0].row)
                    is_cycle = false;

                if (is_cycle)
                    matrix_[i][j] = INF;

                is_cycle = true;
            }
        }
    }
}

/**
 * Reduce the cost matrix.
 * @return The sum of reduced values.
 */
cost_t StageState::reduce_cost_matrix() {
    cost_t reduced_rows = matrix_.reduce_rows();
    cost_t reduced_cols = matrix_.reduce_cols();

    return reduced_cols + reduced_rows;
}

/**
 * Given the optimal path, return the optimal cost.
 * @param optimal_path
 * @param m
 * @return Cost of the path.
 */
cost_t get_optimal_cost(const path_t& optimal_path, const cost_matrix_t& m) {
    cost_t cost = 0;

    for (std::size_t idx = 1; idx < optimal_path.size(); ++idx) {
        cost += m[optimal_path[idx - 1]][optimal_path[idx]];
    }

    // Add the cost of returning from the last city to the initial one.
    cost += m[optimal_path[optimal_path.size() - 1]][optimal_path[0]];

    return cost;
}

/**
 * Create the right branch matrix with the chosen vertex forbidden and the new lower bound.
 * @param m
 * @param v
 * @param lb
 * @return New branch.
 */
StageState create_right_branch_matrix(cost_matrix_t m, vertex_t v, cost_t lb) {
    CostMatrix cm(m);
    cm[v.row][v.col] = INF;
    return StageState(cm, {}, lb);
}

/**
 * Retain only optimal ones (from all possible ones).
 * @param solutions
 * @return Vector of optimal solutions.
 */
tsp_solutions_t filter_solutions(tsp_solutions_t solutions) {
    cost_t optimal_cost = INF;
    for (const auto& s: solutions) {
        optimal_cost = (s.lower_bound < optimal_cost) ? s.lower_bound : optimal_cost;
    }

    tsp_solutions_t optimal_solutions;
    std::copy_if(solutions.begin(), solutions.end(),
                 std::back_inserter(optimal_solutions),
                 [&optimal_cost](const tsp_solution_t& s) { return s.lower_bound == optimal_cost; }
    );

    return optimal_solutions;
}

/**
 * Solve the TSP.
 * @param cm The cost matrix.
 * @return A list of optimal solutions.
 */
tsp_solutions_t solve_tsp(const cost_matrix_t& cm) {

    StageState left_branch(cm);

    // The branch & bound tree.
    std::stack<StageState> tree_lifo;

    // The number of levels determines the number of steps before obtaining
    // a 2x2 matrix.
    std::size_t n_levels = cm.size() - 2;

    tree_lifo.push(left_branch);   // Use the first cost matrix as the root.

    cost_t best_lb = INF;
    tsp_solutions_t solutions;

    while (!tree_lifo.empty()) {
        left_branch = tree_lifo.top();
        tree_lifo.pop();

//        std::cout << "lb";
        while (left_branch.get_level() != n_levels && left_branch.get_lower_bound() <= best_lb) {
            // Repeat until a 2x2 matrix is obtained or the lower bound is too high...

            if (left_branch.get_level() == 0) {
                left_branch.reset_lower_bound();
            }

            // 1. Reduce the matrix in rows and columns.
            cost_t new_cost = left_branch.reduce_cost_matrix();

            // 2. Update the lower bound and check the break condition.
            left_branch.update_lower_bound(new_cost);
//            std::cout << new_cost << '+';
            if (left_branch.get_lower_bound() > best_lb) {
                break;
            }

            // 3. Get new vertex and the cost of not choosing it.
            NewVertex new_vertex = left_branch.choose_new_vertex();

            left_branch.append_to_path(new_vertex.coordinates);

            left_branch.update_cost_matrix(new_vertex.coordinates);

            // 6. Update the right branch and push it to the LIFO.
            cost_t new_lower_bound = left_branch.get_lower_bound() + new_vertex.cost;
            tree_lifo.push(create_right_branch_matrix(cm, new_vertex.coordinates,
                                                      new_lower_bound));
        }
//        std::cout << "\n";

//        best_lb = left_branch.get_lower_bound();
//        path_t new_path = left_branch.get_path();
//        solutions.push_back({get_optimal_cost(new_path, cm), new_path});

//        std::cout << left_branch.get_lower_bound() << '-' << best_lb << '\n';
        if (left_branch.get_lower_bound() <= best_lb) {
            // If the new solution is at least as good as the previous one,
            // save its lower bound and its path.
            best_lb = left_branch.get_lower_bound();
            path_t new_path = left_branch.get_path();
            //std::cout << get_optimal_cost(new_path, cm) << ';';
            solutions.push_back({get_optimal_cost(new_path, cm), new_path});
        }
    }


    return filter_solutions(solutions); // Filter solutions to find only optimal ones.
}
