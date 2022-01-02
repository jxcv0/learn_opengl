cmake_minimum_required(VERSION 3.18.4)
project(exe)

set(LIBS learn_opengl glad)

add_executable(hellotriangle HelloTriangle.cpp)
add_executable(hellorectangle HelloRectangle.cpp)

target_link_libraries(hellotriangle PUBLIC ${LIBS})
target_link_libraries(hellorectangle PUBLIC ${LIBS})