# Add the Component 1 directory to the build.
#
# CMake will enter the component1 directory and process
# the CMakeLists.txt file located there.
#
# This creates the component1_library target.

add_subdirectory(component1)


# Add the Component 2 directory to the build.
#
# CMake will enter the component2 directory and process
# the CMakeLists.txt file located there.
#
# This creates the component2_library target.

add_subdirectory(component2)


# Add the Component 3 directory to the build.
#
# CMake will enter the component3 directory and process
# the CMakeLists.txt file located there.
#
# This creates the component3_library target.

add_subdirectory(component3)
