cmake_minimum_required(VERSION 3.18.4)
project(exe)

set(LIBS learn_opengl glad)

link_libraries(${LIBS})

add_executable(hellotriangle HelloTriangle.cpp)
add_executable(hellorectangle HelloRectangle.cpp)
add_executable(hellouniforms HelloUniforms.cpp)
add_executable(helloshaders HelloShaders.cpp)