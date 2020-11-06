cmake_minimum_required(VERSION 3.17)
project(calculation_td4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O -Wall")

include_directories(includes)

add_executable(TD4 src/main.cpp)