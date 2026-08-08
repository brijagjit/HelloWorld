cmake_minimum_required(VERSION 3.16)


# Create a library target called "component1_library".
#
# This library contains the implementation of Component 1.

add_library(component1_library
    component1.cpp
)


# Specify where component1_library can find its header files.
#
# CMAKE_CURRENT_SOURCE_DIR refers to the directory containing
# this CMakeLists.txt file.
#
# In this case:
#
# components/component1/

target_include_directories(component1_library PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


# Link component1_library with hello_library.
#
# This allows component1.cpp to use functionality provided
# by hello_library, including hello.h.
#
# The PUBLIC keyword means:
#
# - component1_library uses hello_library
# - Any target that links against component1_library also
#   inherits the hello_library dependency

target_link_libraries(component1_library PUBLIC
    hello_library
)
