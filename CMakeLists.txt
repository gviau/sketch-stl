cmake_minimum_required (VERSION 2.8)

if (WIN32)
else (WIN32)
    add_definitions(-std=c++11)
endif (WIN32)

add_subdirectory (src)