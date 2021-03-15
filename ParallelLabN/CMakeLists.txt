cmake_minimum_required(VERSION 3.0)
project(ParallelLab C)

find_package(MPI REQUIRED)

include_directories(include ${MPI_INCLUDE_PATH})

add_executable(ParallelLabN main.c src/Helpers.c src/ReadFile.c src/ProcessInfo.c include/ProcessInfo.h)

target_link_libraries(ParallelLabN PRIVATE ${MPI_C_LIBRARIES})
