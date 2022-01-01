cmake_minimum_required(VERSION 3.22.1)
project(learn_opengl_tests)

enable_testing()

set(
    SOURCES
        ShadersTests.cpp
)

add_executable(all_tests ${SOURCES})

target_link_libraries(
    all_tests
        PUBLIC
            learn_opengl
            gtest_main
)

add_test(
    NAME all_tests
    COMMAND all_tests
)