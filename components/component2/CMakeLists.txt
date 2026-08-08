cmake_minimum_required(VERSION 3.16)


# Create a library target called "component2_library".
#
# This library contains the implementation of Component 2.

add_library(component2_library
    component2.cpp
)


# Specify where component2_library can find its header files.
#
# CMAKE_CURRENT_SOURCE_DIR refers to the directory containing
# this CMakeLists.txt file.
#
# In this case:
#
# components/component2/

target_include_directories(component2_library PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


# Link component2_library with hello_library.
#
# This allows component2.cpp to use functionality provided
# by hello_library, including hello.h.
#
# The PUBLIC keyword means:
#
# - component2_library uses hello_library
# - Any target that links against component2_library also
#   inherits the hello_library dependency

target_link_libraries(component2_library PUBLIC
    hello_library
)
