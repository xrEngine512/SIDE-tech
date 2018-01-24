cmake_minimum_required(VERSION 3.5)
project(SIDEtech)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(SIDE)
add_subdirectory(TargetIntegration)
add_subdirectory(LLVMIntegration)
