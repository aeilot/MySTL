cmake_minimum_required(VERSION 4.0)
project(ds)

set(CMAKE_CXX_STANDARD 20)

add_executable(ds main.cpp
        LinkedList.cpp
        LinkedList.h
        vector.cpp
        vector.h)
