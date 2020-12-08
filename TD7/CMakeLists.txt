cmake_minimum_required(VERSION 3.16)
project(TD7)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O -Wall")

add_executable(TD7 src/main.cpp src/common.cpp)
