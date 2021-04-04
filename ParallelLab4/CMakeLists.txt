cmake_minimum_required(VERSION 3.0)
project(ParallelLab C)

find_package(MPI REQUIRED)

include_directories(include ${MPI_INCLUDE_PATH})

add_executable(ParallelLab4 main.c src/WrapperMPI.c src/Matrix.c)

target_link_libraries(ParallelLab4 PRIVATE ${MPI_C_LIBRARIES})