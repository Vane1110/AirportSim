cmake_minimum_required(VERSION 3.27)
project(lotnisko)

set(CMAKE_CXX_STANDARD 17)

add_executable(lotnisko main.cpp
        Entities.cpp
        Runway.cpp
        Airport.cpp
        JustDays.cpp
        JustDays.h)
