cmake_minimum_required(VERSION 3.29)
project(code)

set(CMAKE_CXX_STANDARD 20)
add_executable(task_1 task_1.cpp
        task_1.h
)


include_directories(../../5_2/code/)
add_executable(task_2
        task_2.cpp
        ../../5_2/code/BinFileWorker.h
        task_1.h
        Worker.h
)
