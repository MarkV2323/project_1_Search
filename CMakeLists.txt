cmake_minimum_required(VERSION 3.21)
project(exampleProject)
ADD_SUBDIRECTORY(googletest)
set(CMAKE_CXX_STANDARD 14)

# primary exe
add_executable(startingProject
        src/main.cpp
        src/printUI.cpp
        src/Problem.cpp
        )

# unit tests exe
add_executable(test
        tests/test.cpp
        )

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON NO_GRAPHICS)
