cmake_minimum_required(VERSION 3.29)
project(code)

set(CMAKE_CXX_STANDARD 20)

add_executable(code main.cpp
        Graph.cpp
        Graph.h
)

add_executable(z2
        z2/main.cpp
)
