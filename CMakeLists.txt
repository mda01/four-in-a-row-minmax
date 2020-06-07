cmake_minimum_required(VERSION 3.16)
project(4InARow)

set(CMAKE_CXX_STANDARD 14)

add_executable(4InARow main.cpp MinMax.h MinMax.cpp Board.cpp Board.h)