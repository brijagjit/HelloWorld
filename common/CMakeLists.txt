# Specify the minimum version of CMake required to build this project.

cmake_minimum_required(VERSION 3.16)


# Create a library target called "hello_library".
#
# A target is something CMake knows how to build.
#
# This library contains the implementation of our hello functionality.
#
# Source:
#
# hello.cpp

add_library(hello_library
    hello.cpp
)


# Specify where hello_library can find its header files.
#
# The PUBLIC keyword means:
#
# - hello_library can include files from this directory
# - Any target that links against hello_library also gets this include path
#
# CMAKE_CURRENT_SOURCE_DIR refers to the directory containing
# this CMakeLists.txt file.
#
# In this case:
#
# common/

target_include_directories(hello_library PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
