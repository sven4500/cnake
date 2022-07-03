cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(xnake VERSION 1.0)

# add the executable
add_executable(xnake src/xnake.cpp)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
