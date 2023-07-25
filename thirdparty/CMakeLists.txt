cmake_minimum_required(VERSION 3.25.0)

option(BUILD_THIRDPARTY_TEST "Enables Sample Projects for ThirdParty Packages" ON)

set(_CMAKE_FOLDER ${CMAKE_FOLDER})
set(CMAKE_FOLDER "Thirdparty")

add_subdirectory(boost)
add_subdirectory(tinyxml2)
add_subdirectory(foonathan_memory)
add_subdirectory(sqlite3)
add_subdirectory(fastcdr)
add_subdirectory(fastddr)
#
add_subdirectory(eigen3)
add_subdirectory(xercesc)
add_subdirectory(xsd)
add_subdirectory(biogears)
#
if (NOT WIN32)
   add_subdirectory(pistache)
   add_subdirectory(rapidJSON)
endif()

set(CMAKE_FOLDER ${_CMAKE_FOLDER})
