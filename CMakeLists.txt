cmake_minimum_required(VERSION 3.6)
project(quantus_playground)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(blink)
include_directories(led_pulse)

add_subdirectory(blink)
add_subdirectory(led_pulse)
