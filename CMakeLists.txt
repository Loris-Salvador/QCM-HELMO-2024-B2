cmake_minimum_required(VERSION 3.25)
project(projet_qcm C)

set(CMAKE_C_STANDARD 11)

add_executable(projet_qcm main.c lecture/lecture.c)
