#############################
# CMake - CORE Modules meta-package - root
#############################

cmake_minimum_required(VERSION 3.20.0)

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

if (MSVC)
   if (CMAKE_SIZEOF_VOID_P MATCHES "8")
      set(CMAKE_INSTALL_PREFIX "C:/Program Files/${CMAKE_PROJECT_NAME}")
   else ()
      set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/${CMAKE_PROJECT_NAME}")
   endif ()
endif ()

find_package(Threads)

set(USE_FOLDERS TRUE)
add_subdirectory(thirdparty)
add_subdirectory(libraries)
add_subdirectory(modules)

# message(STATUS "")
# message(STATUS "    == Final overview for ${PROJECT_NAME} ==")
# message(STATUS "Version:              ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH} ${VERSION_TYPE} @ ${VERSION_HOST}")
# message(STATUS "Install prefix:       ${CMAKE_INSTALL_PREFIX}")
# message(STATUS "Output:               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
# message(STATUS "Compiler:             ${CMAKE_CXX_COMPILER}")
# message(STATUS "CMAKE_BUILD_TYPE:     ${CMAKE_BUILD_TYPE}")
# message(STATUS "")
