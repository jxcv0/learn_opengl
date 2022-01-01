cmake_minimum_required(VERSION 3.22.1)
project(learn_opengl)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

enable_testing()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include(FetchContent)

FetchContent_Declare(
  googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        1a3e2a265f35e604378156cd675b11ef0a184627
)
FetchContent_MakeAvailable(googletest)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

set(
    SOURCES
        src/Shaders.cpp
)

set(
    HEADERS
        include/Shaders.hpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(
    ${PROJECT_NAME}
        PUBLIC
            ${PROJECT_SOURCE_DIR}/include
            ${PROJECT_SOURCE_DIR}/include/glad/include/glad
)

target_link_libraries(
    ${PROJECT_NAME}
        PRIVATE
            glad
            glfw
            OpenGL::GL
)

add_subdirectory(include/glad)
add_subdirectory(exe)
add_subdirectory(test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)