cmake_minimum_required(VERSION 3.25.0)

include(FetchContent)

function(guarantee_RapidJSON_availability)
set(GIT_REPOSITORY https://github.com/Tencent/rapidjson.git)
set(GIT_TAG v1.1.0)

set(PACKAGE_NAME RapidJSON)
set(TARGET_NAME rapidjson)
set(FETCH_NAME rapidjson)
set(PACKAGE_PREFIX RAPIDJSON)
set(PACKAGE_EXPORT rapidjson::lib
)
if (BUILD_THIRDPARTY_TEST)
option(BUILD_${PACKAGE_NAME}_AVAILABILITY_TEST "Build ${PACKAGE_NAME} sample project for testing" ON)
endif()
cmake_parse_arguments("${PACKAGE_NAME}" "REQUIRED" "" ""  ${ARGN})
find_package(${PACKAGE_NAME} QUIET GLOBAL)
    Set(FETCHCONTENT_QUIET FALSE)
    option(MOHSES_FETCH_THIRDPARTY "This option will try to fetch third party dependencies for building" ON)
    if ( NOT ${PACKAGE_NAME}_FOUND )
        if (MOHSES_FETCH_THIRDPARTY)
            set(CMAKE_FOLDER "${CMAKE_FOLDER}/${PACKAGE_NAME}")
            FetchContent_Declare(
                ${PACKAGE_NAME}
                GIT_REPOSITORY ${GIT_REPOSITORY} 
                GIT_TAG ${GIT_TAG}
                GIT_PROGRESS TRUE
                OVERRIDE_FIND_PACKAGE  TRUE
                CMAKE_ARGS -D RAPIDJSON_BUILD_TESTS=OFF RAPIDJSON_BUILD_EXAMPLES=OFF RAPIDJSON_BUILD_DOCS=OFF
            
            )
            message(STATUS "${PACKAGE_NAME} not found Fetching ${GIT_TAG}")          
    
            FetchContent_MakeAvailable(${PACKAGE_NAME})
 
            find_path(${PACKAGE_PREFIX}_INCLUDE_DIR NAMES rapidjson/rapidjson.h PATHS ${${FETCH_NAME}_SOURCE_DIR}/include NO_DEFAULT_PATHS)
            message(FATAL_ERROR "${PACKAGE_PREFIX}_INCLUDE_DIR=${${PACKAGE_PREFIX}_INCUDE_DIR}")
            if(NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PACKAGE_NAME}-extra.cmake AND
            NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PACKAGE_NAME}Extra.cmake)
               get_target_property(${PACKAGE_PREFIX}_INCLUDE_DIR  ${PACKAGE_EXPORT} INCLUDE_DIRECTORIES)
               message(FATAL_ERROR "${PACKAGE_PREFIX}_INCLUDE_DIR=${${PACKAGE_PREFIX}_INCLUDE_DIR}")
               file(WRITE ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PACKAGE_NAME}-extra.cmake                                
               "
                  if(\"\${${PACKAGE_PREFIX}_INCLUDE_DIR}\" STREQUAL \"\" AND TARGET  ${PACKAGE_EXPORT})
                    set(${PACKAGE_PREFIX}_INCLUDE_DIR ${${PACKAGE_PREFIX}_INCLUDE_DIR})
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_INCLUDE_DIRS}\" STREQUAL \"\" AND TARGET  ${PACKAGE_EXPORT})
                    set(${PACKAGE_PREFIX}_INCLUDE_DIRS ${${PACKAGE_PREFIX}_INCLUDE_DIR})
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_LIBRARY}\" STREQUAL \"\" AND TARGET  ${PACKAGE_EXPORT})
                    set(${PACKAGE_PREFIX}_LIBRARY ${PACKAGE_EXPORT})
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_LIBRARIES}\" STREQUAL \"\" AND TARGET  ${PACKAGE_EXPORT})
                    set(${PACKAGE_PREFIX}_LIBRARIES  ${PACKAGE_EXPORT})
                  endif()
               ")
            endif()
            message(STATUS "install(TARGETS ${TARGET_NAME} EXPORT ${TARGET_NAME})  ")
            install(TARGETS ${TARGET_NAME} EXPORT ${TARGET_NAME})  
            export(TARGETS ${TARGET_NAME} FILE ${PACKAGE_NAME}-targets.cmake)

            include(FindPackageHandleStandardArgs)
            FIND_PACKAGE_HANDLE_STANDARD_ARGS(${PACKAGE_NAME}
                                  REQUIRED_VARS ${PACKAGE_PREFIX}_INCLUDE_DIR
#                                                ${PACKAGE_PREFIX}_LIBRARY_RELEASE
#                                                ${PACKAGE_PREFIX}_LIBRARY_DEBUG
             
            )
            if(TINYXML2_FOUND)
               message(STATUS "TinyXML2 Found using FetchContentAdd")
            endif()

            if (BUILD_${PACKAGE_NAME}_AVAILABILITY_TEST AND BUILD_THIRDPARTY_TEST)
                add_executable(${PACKAGE_NAME}_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/${PACKAGE_NAME}.cpp )
                set_target_properties(${PACKAGE_NAME}_test PROPERTIES FOLDER "${CMAKE_FOLDER}/Tests")
                target_link_libraries(${PACKAGE_NAME}_test PRIVATE ${PACKAGE_EXPORT} )            
            endif()
        endif()
    endif()

    if ( NOT TARGET rapidjson AND RapidJSON_SOURCE_DIR=${RapidJSON_SOURCE_DIR})
      message(STATUS "Creating Target rapidjson from RapidJSON_SOURCE_DIR")
      add_library(rapidjson INTERFACE)
      target_include_directories(rapidjson INTERFACE  
            INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${${PACKAGE_PREFIX}_INCLUDE_DIR}>)
      add_library( rapidjson::headers ALIAS rapidjson)
    elseif( ${PACKAGE_PREFIX}_INCLUDE_DIRS )
      message(STATUS "Creating Target rapidjson from RAPIDJSON_INCLUDE_DIR=${RAPIDJSON_INCLUDE_DIR}")
      add_library(rapidjson INTERFACE)
      target_include_directories(rapidjson INTERFACE  
            INTERFACE $<BUILD_INTERFACE:${${PACKAGE_PREFIX}_INCLUDE_DIRS}>
            $<INSTALL_INTERFACE:${${PACKAGE_PREFIX}_INCLUDE_DIRS}>)
      add_library( rapidjson::headers ALIAS rapidjson)
    endif()
    
    find_package(${PACKAGE_NAME} REQUIRED GLOBAL)
    if (NOT ${PACKAGE_NAME}_FOUND)
        message(FATAL_ERROR "Unable to find ${PACKAGE_NAME} or fetch it from ${GIT_REPOSITROY}. 
        Check your network connection or install the ${PACKAGE_NAME} package and configure your CMAKE_PREFIX_PATH to ensure visibility
        https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
        https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
    endif()

endfunction()

guarantee_RapidJSON_availability()
