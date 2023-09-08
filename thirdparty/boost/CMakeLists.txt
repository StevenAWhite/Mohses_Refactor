cmake_minimum_required(VERSION 3.18.0)

set(GIT_REPOSITORY https://github.com/boostorg/boost.git)
set(GIT_TAG boost-1.82.0)
set(PACKAGE_NAME Boost)
set(FETCH_NAME boost)
set(PACKAGE_PREFIX BOOST)


find_package(${PACKAGE_NAME} REQUIRED COMPONENTS filesystem program_options serialization system thread GLOBAL)

if (NOT TARGET Boost::asio)
  message(STATUS "EXPORTING Boost::asio") 
  add_library(Boost::asio ALIAS Boost::headers)
elseif(TARGET ${PACKAGE_EXPORT})
  message(STATUS "${PACKAGE_EXPORT} target exists")
endif()

if (NOT TARGET Boost::algorithm)
  message(STATUS "EXPORTING Boost::algorithm") 
  add_library(Boost::algorithm ALIAS Boost::headers)
elseif(TARGET ${PACKAGE_EXPORT})
  message(STATUS "${PACKAGE_EXPORT} target exists")
endif()

if (NOT TARGET Boost::assign)
  message(STATUS "EXPORTING Boost::assign") 
  add_library(Boost::assign ALIAS Boost::headers)
elseif(TARGET ${PACKAGE_EXPORT})
  message(STATUS "${PACKAGE_EXPORT} target exists")
endif()

if (NOT TARGET Boost::foreach)
  message(STATUS "EXPORTING Boost::foreach") 
  add_library(Boost::foreach ALIAS Boost::headers)
elseif(TARGET ${PACKAGE_EXPORT})
  message(STATUS "${PACKAGE_EXPORT} target exists")
endif()

if (NOT TARGET Boost::process)
  message(STATUS "EXPORTING Boost::process") 
  add_library(Boost::process ALIAS Boost::headers)
elseif(TARGET ${PACKAGE_EXPORT})
  message(STATUS "${PACKAGE_EXPORT} target exists")
endif()

if (NOT TARGET Boost::uuid)
  message(STATUS "EXPORTING Boost::uuid") 
  add_library(Boost::uuid ALIAS Boost::headers)
elseif(TARGET ${PACKAGE_EXPORT})
  message(STATUS "${PACKAGE_EXPORT} target exists")
endif()


if (NOT ${PACKAGE_NAME}_FOUND)
    message(FATAL_ERROR "Unable to find ${PACKAGE_NAME} or fetch it from ${GIT_REPOSITORY}. 
    Check your network connection or install the ${PACKAGE_NAME} package and configure your CMAKE_PREFIX_PATH to ensure visibility
    https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
    https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
endif()

