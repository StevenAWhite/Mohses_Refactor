cmake_minimum_required(VERSION 3.18.0)

set(GIT_REPOSITORY https://github.com/Tencent/rapidjson.git)
set(GIT_TAG v1.1.0)

set(PACKAGE_NAME RapidJSON)
set(TARGET_NAME rapidjson)
set(FETCH_NAME rapidjson)
set(PACKAGE_PREFIX RAPIDJSON)
set(PACKAGE_EXPORT rapidjson::headers)
    
find_package(${PACKAGE_NAME} REQUIRED GLOBAL)

if (NOT ${PACKAGE_NAME}_FOUND)
    message(STATUS "Unable to find ${PACKAGE_NAME} or fetch it from ${GIT_REPOSITROY}. 
    Check your network connection or install the ${PACKAGE_NAME} package and configure your CMAKE_PREFIX_PATH to ensure visibility
    https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
    https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
endif()

if( ${PACKAGE_PREFIX}_INCLUDE_DIRS AND NOT TARGET rapidjson)
  add_library(rapidjson INTERFACE )
  target_include_directories(rapidjson INTERFACE  
        INTERFACE $<BUILD_INTERFACE:${${PACKAGE_PREFIX}_INCLUDE_DIRS}>
        $<INSTALL_INTERFACE:${${PACKAGE_PREFIX}_INCLUDE_DIRS}>)
endif()
if( TARGET rapidjson AND NOT TARGET ${PACKAGE_EXPORT})
  message(STATUS "Creating target ${PACKAGE_EXPORT}")
  add_library( ${PACKAGE_EXPORT} ALIAS rapidjson)
endif()    

