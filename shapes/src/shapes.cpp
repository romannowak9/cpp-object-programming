#include <vector>
#include <numeric>
#include "shapes.hpp"

double calculate_total_area(const std::vector<Shape*>& shapes){
    return std::accumulate(shapes.begin(), shapes.cend(), 0.0,
                    [] (auto acc, const auto& elem) { return acc + elem -> area(); });
}
