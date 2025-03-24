cmake_minimum_required(VERSION 3.13)

set(PROJECT_ID complex_1)

set(SOURCE_FILES
        src/complex.cpp
        include/complex.hpp
        )

set(SOURCES_FILES_TESTS
        test/test_complex.cpp
        )

include(../SetCommonConfig.cmake)
