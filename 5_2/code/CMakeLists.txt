cmake_minimum_required(VERSION 3.28)
project(code)

set(CMAKE_CXX_STANDARD 17)

add_executable(code
        FileWorker.h
        task_1.cpp
)
add_executable(task_2 BinFileWorker.h task_2.cpp)
