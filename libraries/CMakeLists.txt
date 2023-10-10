cmake_minimum_required(VERSION 3.18.0)

set(_CMAKE_FOLDER ${CMAKE_FOLDER})
set(CMAKE_FOLDER "Mohses")
add_subdirectory(net)
set(CMAKE_FOLDER ${_CMAKE_FOLDER})
