cmake_minimum_required(VERSION 3.29)
project(code)

set(CMAKE_CXX_STANDARD 23)

add_executable(code main.cpp
        Z1/BinarySearchTree.cpp
        Z1/BinarySearchTree.h
        Z1/BinFileWorker.cpp
        Z1/BinFileWorker.h)
