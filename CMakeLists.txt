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


# Add the "common" directory to the build.
#
# CMake will enter the common directory and process
# the CMakeLists.txt file located there.
#
# This allows the hello_library target defined in
# common/CMakeLists.txt to be used by this project.
add_subdirectory(common)


# Add the Components directory to the build.
#
# CMake will enter the component directories and process
# the CMakeLists.txt file located there.
#
# This makes the componentX_library targets available
# to the rest of the project.
add_subdirectory(components)


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
# This allows main.cpp to use functions implemented in libraries.
#
# PRIVATE means:
# - hello uses hello_library and componentX_librar(ies)
# - Other targets that use hello do not inherit this dependency
#
target_link_libraries(hello PRIVATE
    hello_library
    component1_library
    component2_library
    component3_library
)
