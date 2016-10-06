cmake_minimum_required(VERSION 3.6)
project(quantus_playground)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(blink)
include_directories(led_pulse)

add_subdirectory(blink)
add_subdirectory(led_pulse)
