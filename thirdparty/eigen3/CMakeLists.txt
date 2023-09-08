cmake_minimum_required(VERSION 3.18.0)

set(GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git)
set(GIT_TAG 3.4)

set(PACKAGE_NAME Eigen3)
set(PACKAGE_PREFIX Eigen3)
set(PACKAGE_EXPORT Eigen3::Eigen3    )
find_package(${PACKAGE_NAME} REQUIRED GLOBAL)

if (NOT ${PACKAGE_NAME}_FOUND)
    message(FATAL_ERROR "Unable to find ${PACKAGE_NAME} or fetch it from ${GIT_REPOSITROY}. 
    Check your network connection or install the ${PACKAGE_NAME} package and configure your CMAKE_PREFIX_PATH to ensure visibility
    https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
    https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
endif()

