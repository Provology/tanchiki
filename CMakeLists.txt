cmake_minimum_required(VERSION 3.10)
project(pimg_pong)


add_compile_options(-g -Wall -Wextra)
include_directories(include ../libs/ ./src/libs/)
link_directories(../libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../output)
add_executable(ping_pong src/main.c src/libs/glad.c src/libs/shader_module.c src/texture_module.c src/vertices.c src/create_window.c src/transformations.c src/libs/stb_image.c src/libs/linear_algebra.c src/render.c src/read_map.c src/obstacle.c src/ai_module.c)
target_link_libraries (ping_pong PUBLIC glfw3 PUBLIC GL X11 pthread Xrandr dl m)# Xi dl m)



