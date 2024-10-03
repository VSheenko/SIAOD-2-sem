cmake_minimum_required(VERSION 3.28)
project(code)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(code
        z1.cpp
        z2.cpp
        z2.cpp
        z3.cpp
        z4.cpp
        z5.cpp
        Sort.cpp)
target_link_libraries(code gtest gtest_main)