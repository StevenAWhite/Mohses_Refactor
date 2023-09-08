cmake_minimum_required(VERSION 3.18.0)

set(GIT_REPOSITORY https://github.com/viaduck/openssl-cmake.git )
set(GIT_TAG 3.0)
set(PACKAGE_NAME openssl)
set(PACKAGE_PREFIX OPENSSL)

if(NOT ${PACKAGE_NAME}_FOUND AND MSVC)
   message(STATUS "OpenSSL binaries are required for this build. Downloads are avaliable for Windows at Shining Light Productions.
                   https://slproweb.com/products/Win32OpenSSL.html . The full development installation of OpenSSL v3.1.1 140MBs.
                   Adjust CMAKE_PREFIX_PATH with the folder containing the instllation.")
endif()

find_package(OpenSSL REQUIRED GLOBAL)

if (AND NOT ${PACKAGE_NAME}_FOUND)
   message(FATAL_ERROR "Unable to find ${PACKAGE_NAME} or fetch it from ${GIT_REPOSITROY}. 
   Check your network connection or install the ${PACKAGE_NAME} package and configure your CMAKE_PREFIX_PATH to ensure visibility
   https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
   https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
endif()

