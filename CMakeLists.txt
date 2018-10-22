cmake_minimum_required(VERSION 2.8)

project(attitude_proj)

set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

find_package(Boost REQUIRED COMPONENTS
    filesystem
    system
    thread
)

add_subdirectory(src)


