cmake_minimum_required(VERSION 3.0)
project(ParallelLab C)

find_package(MPI REQUIRED)

include_directories(include ${MPI_INCLUDE_PATH})

add_executable(ParallelLab2 main.c src/Bonus.c)

target_link_libraries(ParallelLab2 PRIVATE ${MPI_C_LIBRARIES})
