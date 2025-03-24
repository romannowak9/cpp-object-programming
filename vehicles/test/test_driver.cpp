#include "gtest/gtest.h"

#include "vehicles.hpp"

TEST(DriverTest, toStringNoVehicle) {
    Driver owner("Adam Abacki", Gender::Male);

    std::string str = to_string(owner);

    ASSERT_EQ(str, "Adam Abacki : [no vehicle]");
}

TEST(DriverTest, toStringWithVehicle) {
    Driver owner("Adam Abacki", std::make_unique<Car>("C1", "Lexus", 500.0), Gender::Male);

    std::string str = to_string(owner);

    std::string vehicle_str = to_string(*(owner.get_vehicle()));
    ASSERT_EQ(str, "Adam Abacki : [" + vehicle_str + "]");
}

TEST(DriverAuxTest, copying) {
    Driver driver1("Adam Abacki", std::make_unique<Car>("C1", "Lexus", 500.0), Gender::Male);

    Driver driver2(std::move(driver1));

    EXPECT_EQ(driver1.get_vehicle(), nullptr);
    EXPECT_EQ((driver2.get_vehicle())->get_id(), "C1");
}

TEST(DriverAuxTest, assignment) {
    Driver driver1("Adam Abacki", std::make_unique<Car>("C1", "Lexus", 500.0), Gender::Male);
    Driver driver2("Bogdan Babacki", Gender::Male);

    driver2 = std::move(driver1);

    EXPECT_EQ(driver1.get_vehicle(), nullptr);
    EXPECT_EQ((driver2.get_vehicle())->get_id(), "C1");
}

