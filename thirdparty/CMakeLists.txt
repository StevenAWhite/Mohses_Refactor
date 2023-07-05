cmake_minimum_required(VERSION 3.20.0)

option(BUILD_THIRDPARTY_TEST "Enables Sample Projects for ThirdParty Packages" ON)

set(_CMAKE_FOLDER ${CMAKE_FOLDER})
set(CMAKE_FOLDER "Thirdparty")
add_subdirectory(boost)
add_subdirectory(tinyxml2)
add_subdirectory(foonathan_memory)
add_subdirectory(sqlite3)
add_subdirectory(fastcdr)
add_subdirectory(fastddr)
set(CMAKE_FOLDER ${_CMAKE_FOLDER})
