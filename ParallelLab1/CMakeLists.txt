cmake_minimum_required(VERSION 3.0)
project(ParallelLab1 C)

include_directories(include)

set(CMAKE_CXX_STANDARD_REQUIRED 11)
set(CMAKE_C_STANDARD 11)

find_package(OpenMP REQUIRED)

add_executable(ParallelLab1 main.c src/Utils.c src/Vector.c)

target_link_libraries(ParallelLab1 PRIVATE OpenMP::OpenMP_C)
