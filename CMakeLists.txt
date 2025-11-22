cmake_minimum_required(VERSION 3.24)
project(2526_TI301_PJT C)

set(CMAKE_C_STANDARD 11)

add_executable(TI_301_PJT
        main.c
        chained.c
        hasse.h
        hasse.c
        chained.h)

add_executable(part2
        part2.c
        hasse.c
        hasse.h
        chained.c
        chained.h
)