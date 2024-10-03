cmake_minimum_required(VERSION 3.28)
project(code)

set(CMAKE_CXX_STANDARD 17)

add_executable(code main.cpp
        FileWorker.h
        test/FileWorkerTest.cpp
        BinFileWorker.h)
