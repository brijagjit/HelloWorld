# Specify Minimum CMake Version Required
cmake_minimum_required(VERSION 3.16)

# Create Project with Version and Languages
project(HelloWorld
	VERSION 1.0
	LANGUAGES CXX)

# Set CMake CXX Standard and set as Required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define Executable hello Target from main.cpp Source
add_executable(hello
	src/main.cpp
)
