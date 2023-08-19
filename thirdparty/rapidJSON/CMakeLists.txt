cmake_minimum_required(VERSION 3.25.0)

include(FetchContent)

function(guarantee_RapidJSON_availability)
set(GIT_REPOSITORY https://github.com/Tencent/rapidjson.git)
set(GIT_TAG v1.1.0)

set(PACKAGE_NAME RapidJSON)
set(TARGET_NAME rapidjson)
set(FETCH_NAME rapidjson)
set(PACKAGE_PREFIX RAPIDJSON)
set(PACKAGE_EXPORT rapidjson::headers
)
cmake_parse_arguments("${PACKAGE_NAME}" "REQUIRED" "" ""  ${ARGN})
find_package(${PACKAGE_NAME} QUIET GLOBAL)
    Set(FETCHCONTENT_QUIET FALSE)
    if ( NOT ${PACKAGE_NAME}_FOUND )
        if (MOHSES_FETCH_THIRDPARTY)
            if (BUILD_THIRDPARTY_TEST)
              option(BUILD_${PACKAGE_NAME}_AVAILABILITY_TEST "Build ${PACKAGE_NAME} sample project for testing" ON)
            endif()
            set(CMAKE_FOLDER "${CMAKE_FOLDER}/${PACKAGE_NAME}")

            set( RAPIDJSON_BUILD_DOC  OFF CACHE BOOL "Toggle the building of RapidJson Docs for ThirdParty Library")
            set( RAPIDJSON_BUILD_EXAMPLES OFF CACHE BOOL "Toggle the building of RapidJson Examples for ThirdParty Library")
            set( RAPIDJSON_BUILD_TESTS OFF CACHE BOOL "Toggle the building of RapidJson Test for ThirdParty Library")
            
            FetchContent_Declare(
                ${PACKAGE_NAME}
                GIT_REPOSITORY ${GIT_REPOSITORY} 
                GIT_TAG ${GIT_TAG}
                GIT_PROGRESS TRUE
                OVERRIDE_FIND_PACKAGE  TRUE
                CMAKE_ARGS -D RAPIDJSON_BUILD_TESTS=OFF -D RAPIDJSON_BUILD_EXAMPLES=OFF -D RAPIDJSON_BUILD_DOCS=OFF
            
            )
            message(STATUS "${PACKAGE_NAME} not found Fetching ${GIT_TAG}")          
    
            FetchContent_MakeAvailable(${PACKAGE_NAME})
 
            find_path(${PACKAGE_PREFIX}_INCLUDE_DIRS 
                      NAMES rapidjson/rapidjson.h 
                      PATHS ${${FETCH_NAME}_SOURCE_DIR}/include 
                      NO_CMAKE_ENVIRONMENT_PATH
                      NO_SYSTEM_ENVIRONMENT_PATH
                      NO_CMAKE_SYSTEM_PATH
                      NO_CMAKE_FIND_ROOT_PATH
                   )


            if(TARGET ${TARGET_NAME})
              message(STATUS "install(TARGETS ${TARGET_NAME} EXPORT ${TARGET_NAME})  ")

              install(TARGETS ${TARGET_NAME} EXPORT ${TARGET_NAME})  
              export(TARGETS ${TARGET_NAME} FILE ${PACKAGE_NAME}-targets.cmake)

              include(FindPackageHandleStandardArgs)
              FIND_PACKAGE_HANDLE_STANDARD_ARGS(${PACKAGE_NAME}
                                    REQUIRED_VARS ${PACKAGE_PREFIX}_INCLUDE_DIRS
               
              )
            endif()

            if (BUILD_${PACKAGE_NAME}_AVAILABILITY_TEST AND BUILD_THIRDPARTY_TEST)
                add_executable(${PACKAGE_NAME}_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/${PACKAGE_NAME}.cpp )
                set_target_properties(${PACKAGE_NAME}_test PROPERTIES FOLDER "${CMAKE_FOLDER}/Tests")
                target_link_libraries(${PACKAGE_NAME}_test PRIVATE ${PACKAGE_EXPORT} )            
            endif()
        endif()
    endif()

    
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

endfunction()

guarantee_RapidJSON_availability()
