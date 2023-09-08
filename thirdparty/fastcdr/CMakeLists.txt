cmake_minimum_required(VERSION 3.25.0)

set(GIT_REPOSITORY https://github.com/eProsima/Fast-CDR.git)
set(GIT_TAG  v1.0.27)
set(PACKAGE_NAME fastcdr)
set(EXPORT_NAME eProsima::fastcdr)
set(PACKAGE_PREFIX FASTCDR)

find_package(${PACKAGE_NAME} REQUIRED GLOBAL)

if (TARGET ${PACKAGE_NAME} AND NOT TARGET ${EXPORT_NAME})
  add_library(${EXPORT_NAME} ALIAS ${PACKAGE_NAME})
endif()


if (NOT ${PACKAGE_NAME}_FOUND AND NOT depname_POPULATED)
    message(FATAL_ERROR "Unable to find ${PACKAGE_NAME} or fetch it from ${GIT_REPOSITORY}. 
    Check your network connection or install the FastCDR package and configure your CMAKE_PREFIX_PATH to ensure visibility
    https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
    https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
endif()

