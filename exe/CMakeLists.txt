cmake_minimum_required(VERSION 3.18.4)
project(exe)

add_executable(main main.cpp)

target_link_libraries(
    main
        PUBLIC
            learn_opengl
            glad
)