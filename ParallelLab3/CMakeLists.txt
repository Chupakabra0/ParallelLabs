cmake_minimum_required(VERSION 3.0)
project(ParallelLab C)

find_package(MPI REQUIRED)

include_directories(include ${MPI_INCLUDE_PATH})

add_executable(ParallelLab3 main.c src/WrapperMPI.c src/Utils.c src/RankProcedures.c src/Array.c)

target_link_libraries(ParallelLab3 PRIVATE ${MPI_C_LIBRARIES})
