cmake_minimum_required(VERSION 3.10)
project(2DPlane)

set(CMAKE_CXX_STANDARD 17)

add_library(pointmanager_lib src/point_manager.cpp)
add_library(point_lib src/point.cpp)

# Add executable
add_executable(server src/main.cpp)
target_link_libraries(server PRIVATE pointmanager_lib point_lib)
# Set any additional compilation options if needed
target_compile_options(server PRIVATE -Wall -Wextra)


