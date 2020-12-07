cmake_minimum_required(VERSION 3.16)
project(signal_processing LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_subdirectory(signal_utils)
list(APPEND EXTRA_LIBS signal_utils)
List(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/signal_utils")

add_executable(SignalProcessing src/main.cpp)

target_link_libraries(SignalProcessing PUBLIC ${EXTRA_LIBS})

configure_file(src/SignalProcessingConfig.h.in src/SignalProcessingConfig.h)

target_include_directories(SignalProcessing PUBLIC
        "${PROJECT_BINARY_DIR}"
        ${EXTRA_INCLUDES}
        )
