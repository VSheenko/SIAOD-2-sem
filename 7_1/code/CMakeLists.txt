cmake_minimum_required(VERSION 3.29)
project(code)

set(CMAKE_CXX_STANDARD 23)

add_executable(code
        Z1/main.cpp
        Z1/BinarySearchTree.cpp
        Z1/BinarySearchTree.h
        Z1/BinFileWorker.cpp
        Z1/BinFileWorker.h
        Z1/ViolationRecord.h
)

add_executable(Z2
        Z2/main.cpp
        Z2/SplayTree.h
        Z2/SplayTree.cpp
        Z2/Node.h
        Z2/BinFileWorker.h
        Z2/BinFileWorker.cpp
)

add_executable(Z3
        Z3/main.cpp
        Z3/HashTable.h
        Z3/BinarySearchTree.cpp
        Z3/BinarySearchTree.h
        Z3/Node.h
        Z3/SplayTree.cpp
        Z3/SplayTree.h
)
