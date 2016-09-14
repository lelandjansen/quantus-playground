cmake_minimum_required(VERSION 3.6)
project(quantus_playground)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    blink/CMakeLists.txt
    blink/main.cc)

add_executable(quantus_playground ${SOURCE_FILES})