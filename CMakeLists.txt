# Specify the minimum version of CMake required to build this project.
cmake_minimum_required(VERSION 3.16)


# Define the project name, version, and programming languages used.
#
# LANGUAGES CXX specifies that this project uses C++.
project(HelloWorld
    VERSION 1.0
    LANGUAGES CXX
)


# Specify the C++ standard required to compile this project.
#
# Equivalent compiler flag:
#     g++ -std=c++17
#
set(CMAKE_CXX_STANDARD 17)

# Require the compiler to support the specified C++ standard.
# CMake will stop if C++17 is unavailable.
set(CMAKE_CXX_STANDARD_REQUIRED ON)



# Create a library target called "hello_library".
#
# A target is something CMake knows how to build.
# This library contains the implementation of our hello functionality.
#
# Source:
#     src/hello.cpp
#
add_library(hello_library
    src/hello.cpp
)


# Specify where hello_library can find its header files.
#
# The PUBLIC keyword means:
# - hello_library can include files from this directory
# - Any target that links against hello_library also gets this include path
#
# Header location:
#     include/hello.h
#
target_include_directories(hello_library PUBLIC
    include
)



# Create an executable target called "hello".
#
# This executable contains the program entry point:
#
#     src/main.cpp
#
add_executable(hello
    src/main.cpp
)



# Link the hello executable with hello_library.
#
# This allows main.cpp to use functions implemented in hello_library.
#
# PRIVATE means:
# - hello uses hello_library
# - Other targets that use hello do not inherit this dependency
#
target_link_libraries(hello PRIVATE
    hello_library
)
