cmake_minimum_required(VERSION 3.18.4)
project(learn_opengl VERSION 0.1.0)

include(CTest)
enable_testing()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

set(
    SOURCES
        src/somesource.cpp
)

set(
    HEADERS
        include/someheader.hpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_link_libraries(
    ${PROJECT_NAME}
        PRIVATE
            glad
            glfw
            OpenGL::GL
)

add_subdirectory(include/glad)
add_subdirectory(exe)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)