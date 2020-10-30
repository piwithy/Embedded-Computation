cmake_minimum_required(VERSION 3.13.4)
project(calculation_td1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O -Wall")

include_directories(includes)

add_executable(calculation_td1 src/main.cpp)