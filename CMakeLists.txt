cmake_minimum_required(VERSION 2.8)
project(CSE310_P2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_STANDARD 14)

add_executable(CSE310_P2 Code/main.cpp Code/util.cc Code/bst.cc Code/heap.cc Code/hash.cc Code/prime.cc)