cmake_minimum_required(VERSION 3.0)
project(ParallelLab C)

find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})

add_executable(ParallelLab5 main.c)

target_link_libraries(ParallelLab5 PRIVATE ${MPI_C_LIBRARIES})
