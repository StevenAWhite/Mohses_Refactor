#############################
# CMake Standard Library root/
#############################

cmake_minimum_required (VERSION 3.5.1)

project ("AMM_Standard_Library")
set(VERSION_TYPE "beta" CACHE STRING "version type" FORCE)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 2)
set(PROJECT_VERSION_PATCH 0)

include(CMakePrintHelpers)

option(GENERATE_DOC "Run Doxygen to generate docs" OFF)

find_package(Boost REQUIRED)

if (DEFINED ENV{FASTRTPS_HOME})
    list(APPEND CMAKE_PREFIX_PATH $ENV{FASTRTPS_HOME})
endif ()

if (DEFINED ENV{FASTRTPSHOME})
    list(APPEND CMAKE_PREFIX_PATH $ENV{FASTRTPSHOME})
endif ()

find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)


add_subdirectory(IDL)
add_subdirectory(src)

if(MOHSES_GENERATE_DOC)
    add_subdirectory(doc)
endif(MOHSES_GENERATE_DOC)

include(Packing)
