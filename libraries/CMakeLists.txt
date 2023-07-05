cmake_minimum_required(VERSION 3.20.0)

set(_CMAKE_FOLDER ${CMAKE_FOLDER})
set(CMAKE_FOLDER "Thirdparty")
add_subdirectory(amm)
set(CMAKE_FOLDER ${_CMAKE_FOLDER})
