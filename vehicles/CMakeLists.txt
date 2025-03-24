cmake_minimum_required(VERSION 3.13)

set(PROJECT_ID vehicles_2)

set(SOURCE_FILES
        src/vehicles.cpp
        )

set(SOURCES_FILES_TESTS
        test/test_vehicles.cpp
        test/test_driver.cpp
        test/main_gtest.cpp
        )

include(../SetCommonConfig.cmake)
