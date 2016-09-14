cmake_minimum_required(VERSION 3.6)
project(blink)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cc)
add_executable(blink ${SOURCE_FILES})