cmake_minimum_required(VERSION 2.8)
project(main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lcurl -O2")

set(SOURCE_FILES main.cpp cpp/board.cpp cpp/board.h cpp/configure.cpp cpp/network.h cpp/network.cpp cpp/autoPlay.cpp cpp/autoPlay.h cpp/evaluation.h cpp/evaluation.cpp)
add_executable(main ${SOURCE_FILES})