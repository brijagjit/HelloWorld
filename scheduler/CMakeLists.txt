# Create a library target called "scheduler_library".
#
# This library contains the implementation of the scheduler.

add_library(scheduler_library
    scheduler.cpp
)


# Specify where scheduler_library can find its header files.
#
# CMAKE_CURRENT_SOURCE_DIR refers to the directory containing
# this CMakeLists.txt file.

target_include_directories(scheduler_library PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


# Link the scheduler with the component libraries.
#
# This allows scheduler.cpp to call the functions provided
# by the components.

target_link_libraries(scheduler_library PUBLIC
    component1_library
    component2_library
    component3_library
)
