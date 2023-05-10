cmake_minimum_required(VERSION 3.22)

project(useEigen)
include_directories("/usr/include/eigen3")
add_executable(useEigen ./eigenMatrix.cpp)
