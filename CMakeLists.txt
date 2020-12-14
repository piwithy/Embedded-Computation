cmake_minimum_required(VERSION 3.16)
project(Embedded-Calculation LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -W")


add_subdirectory(TD1)
add_subdirectory(TD2)
add_subdirectory(TD3)
add_subdirectory(TD4)
add_subdirectory(TD5)
add_subdirectory(TD6)
add_subdirectory(TD7)
add_subdirectory(signal_processing)
