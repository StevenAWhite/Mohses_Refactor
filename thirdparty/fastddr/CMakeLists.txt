cmake_minimum_required(VERSION 3.18.0)

set( GIT_REPOSITORY  https://github.com/eProsima/Fast-DDS.git)
set( GIT_TAG v2.10.0)
set( PACKAGE_NAME  fastrtps)
set( EXPORT_NAME    eProsima::fastrtps)
set( EXPORT_NAME2   eProsima::fastdds)
set( PACKAGE_PREFIX FASTRTPS)

find_package(${PACKAGE_NAME} REQUIRED GLOBAL)

if (TARGET ${PACKAGE_NAME} AND NOT TARGET ${EXPORT_NAME})
  add_library(${EXPORT_NAME} ALIAS ${PACKAGE_NAME})
endif()
if (TARGET ${PACKAGE_NAME} AND NOT TARGET ${EXPORT_NAME2})
  add_library(${EXPORT_NAME2} ALIAS ${PACKAGE_NAME})
endif()

if (NOT ${PACKAGE_NAME}_FOUND)
    message(FATAL_ERROR "Unable to find ${PACKAGE_NAME} or fetch it from${GIT_REPOSITORY}. 
    Check your network connection or install the ${PACKAGE_NAME} package and configure your CMAKE_PREFIX_PATH to ensure visibility
    https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
    https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
endif()

