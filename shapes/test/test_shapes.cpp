#include "gtest/gtest.h"

#include "shapes.hpp"

TEST(SquareTest, area) {
    Square square(0.0, 0.0, 1.0);
    EXPECT_EQ(square.area(), 1.0);

    Shape& shape = square;
    EXPECT_EQ(shape.area(), 1.0);
}

TEST(CircleTest, area) {
    Circle circle(0.0, 0.0, 1.0);
    EXPECT_EQ(circle.area(), PI);

    Shape& shape = circle;
    EXPECT_EQ(shape.area(), PI);
}

TEST(ShapesAuxTest, totalAreaOfShapeCollection) {
    std::vector<std::unique_ptr<Shape>> cont;
    cont.push_back(std::make_unique<Circle>(0.0, 0.0, 2.0));
    cont.push_back(std::make_unique<Square>(0.0, 0.0, 2.0));

    std::vector<Shape*> cont_raw;
    std::transform(cont.begin(), cont.end(), std::back_inserter(cont_raw),
                   [] (const std::unique_ptr<Shape>& elem) { return elem.get(); });

    double total_area = calculate_total_area(cont_raw);

    EXPECT_EQ(total_area, cont[0] -> area() + cont[1] -> area());
}
