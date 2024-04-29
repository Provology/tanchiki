cmake_minimum_required(VERSION 3.10)
project(pimg_pong)


add_compile_options(-g -Wall -Wextra)
include_directories(include ../libs/)
link_directories(../libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../output)
add_executable(ping_pong src/main.c src/glad.c src/shader_module.c src/texture_module.c src/stb_image.c)
target_link_libraries (ping_pong PUBLIC glfw3 PUBLIC GL X11 pthread Xrandr dl m)# Xi dl m)


# set(CMAKE_C_COMPILER /bin/x86_64-redhat-linux-gcc-12)

# add_library(glfw3 STATIC IMPORTED)
# set_property(TARGET glfw3 PROPERTY
# 		IMPORTED_LOCATION ../libs/libglfw3.a)

# include_directories(include 
# 					../libs/
# 					)
# set(SOURCE 
# 	src/glad.c
# 	src/main.c
# 	)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../output)

# add_executable(${PROJECT} ${SOURCE})
# target_link_libraries (${PROJECT} INTERFACE glfw3 GL X11 pthread Xrandr Xi dl)

	
# # install(output)
# # add_executable(ping_pong src/*)

# # include(cmake/Logging.cmake)

# # include(cmake/CheckCompiler.cmake)
# # include(cmake/CompileOptions.cmake)
# # include(cmake/Sanitize.cmake)
# # include(cmake/PrintDiagnostics.cmake)

# # option(AWAIT_TESTS "Build Await tests" OFF)
# # option(AWAIT_EXAMPLES "Build Await examples" OFF)
# # option(AWAIT_WORKLOADS "Build Await workloads" OFF)
# # option(AWAIT_DEVELOPER "Await development mode" OFF)
# # option(AWAIT_MIMALLOC "Use mimalloc memory allocator" OFF)

# # add_subdirectory(third_party)

# # add_subdirectory(await)

# # if(AWAIT_TESTS OR AWAIT_DEVELOPER)
# #     add_subdirectory(tests)
# # endif()

# # if(AWAIT_WORKLOADS OR AWAIT_DEVELOPER)
# #     add_subdirectory(workloads)
# # endif()

# # if(AWAIT_EXAMPLES OR AWAIT_DEVELOPER)
# #     add_subdirectory(examples)
# #     add_subdirectory(tutorial)
# # endif()

# # if(AWAIT_DEVELOPER)
# #     add_subdirectory(dev)
# # endif()

# # add_subdirectory(src)

# cmake_minimum_required(VERSION 3.0)

# project("runtest")
# set(CMAKE_VERBOSE_MAKEFILE TRUE)

# file(GLOB_RECURSE C_SRCS LIST_DIRECTORIES true "${CMAKE_SOURCE_DIR}/project/lib_smthng/*.c")

# add_library(module STATIC ${C_SRCS})
# target_include_directories(module PUBLIC ${CMAKE_SOURCE_DIR} project project/lib_smthng)

# add_executable(runtests hello_test.c)


# target_link_libraries(runtests ${CMAKE_SOURCE_DIR}/libcunit.a module)
# target_include_directories(runtests PUBLIC CUnit)
