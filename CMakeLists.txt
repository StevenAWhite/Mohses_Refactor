#############################
# CMake - CORE Modules meta-package - root
#############################

cmake_minimum_required(VERSION 3.18.0)

project("MoHSES System")


set(VERSION_TYPE "release" CACHE STRING "version type" FORCE)
set(PROJECT_VERSION_MAJOR, 1)
set(PROJECT_VERSION_MINOR, 2)
set(PROJECT_VERSION_PATCH@, 0)
site_name(VERSION_HOST) # read hostname to VERSION_HOST
set(VERSION_HOST "${VERSION_HOST}" CACHE STRING "host of build" FORCE)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)


find_package(Doxygen QUIET)
option (MOHSES_GENERATE_DOCS "Generate Doxygen based documentation files" ${Doxygen_Found})
if (MOHSES_GENERATE_DOCS)
   message(STATUS "Looking for Doxygen which is required when MOHSES_GENERATE_DOCS=ON")
   find_package(Doxygen REQUIRED)
endif()

set(OUTPUT_PREFIX ${CMAKE_BINARY_DIR}/artifacts)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_PREFIX}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_PREFIX}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PREFIX}/bin)
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
      string(TOUPPER _${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
      set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY${OUTPUTCONFIG_UPPER} ${OUTPUT_PREFIX}/${OUTPUTCONFIG}/lib)
      set(CMAKE_LIBRARY_OUTPUT_DIRECTORY${OUTPUTCONFIG_UPPER} ${OUTPUT_PREFIX}/${OUTPUTCONFIG}/lib)
      set(CMAKE_RUNTIME_OUTPUT_DIRECTORY${OUTPUTCONFIG_UPPER} ${OUTPUT_PREFIX}/${OUTPUTCONFIG}/bin)
endforeach()

include (${CMAKE_SOURCE_DIR}/cmake/common_logic.cmake)
if(NOT TARGET create_distribution_bundles)
  ###############################################################################
  # Stage Code for IDE Testing
  ###############################################################################
  create_stage()
endif()

find_package(Threads)
set(USE_FOLDERS TRUE)

set(CMAKE_MACOSX_RPATH 1)

option(MOHSES_FETCH_THIRDPARTY "This option will try to fetch third party dependencies for building" OFF)
add_subdirectory(thirdparty)

if ( NOT MOHSES_FETCH_THIRDPARTY )
  add_subdirectory(libraries)
  add_subdirectory(modules)
else()
  message(STATUS "MOHSES_FETCH_THIRDPARTY=ON
   After successfully installing ThirdParrty Builds
   Set MOHSES_FETCH_THIRDPARTY=ON and CMAKE_PREFIX_PATH
   to the THIRDPARTY_INSTALL_PATH to build mohses")
endif()

message(STATUS "")
message(STATUS "    == Final overview for ${PROJECT_NAME} ==")
message(STATUS "Version:              ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH} ${VERSION_TYPE} @ ${VERSION_HOST}")
message(STATUS "Arch:                 ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "CMAKE_PREFIX_PATH:    ${CMAKE_PREFIX_PATH}")
if (CMAKE_ROOT_FIND_PATH)
  message(STATUS "CMAKE_ROOT_FIND_PATH: ${CMAKE_ROOT_FIND_PATH}")
endif()
message(STATUS "Install prefix:       ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Output:               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "Compiler:             ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_BUILD_TYPE:     ${CMAKE_BUILD_TYPE}")
message(STATUS "")
