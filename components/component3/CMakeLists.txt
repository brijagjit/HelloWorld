cmake_minimum_required(VERSION 3.16)


# Create a library target called "component3_library".
#
# This library contains the implementation of Component 3.

add_library(component3_library
    component3.cpp
)


# Specify where component3_library can find its header files.
#
# CMAKE_CURRENT_SOURCE_DIR refers to the directory containing
# this CMakeLists.txt file.
#
# In this case:
#
# components/component3/

target_include_directories(component3_library PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


# Link component3_library with hello_library.
#
# This allows component3.cpp to use functionality provided
# by hello_library, including hello.h.
#
# The PUBLIC keyword means:
#
# - component3_library uses hello_library
# - Any target that links against component3_library also
#   inherits the hello_library dependency

target_link_libraries(component3_library PUBLIC
    hello_library
)
