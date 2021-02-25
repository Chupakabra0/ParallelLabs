cmake_minimum_required(VERSION 3.0)
project(ParallelLab1 C)

find_package(OpenMP REQUIRED)

include_directories(include)

add_executable(ParallelLab1 main.c src/Utils.c src/Vector.c)

target_link_libraries(ParallelLab1 PRIVATE OpenMP::OpenMP_C)
