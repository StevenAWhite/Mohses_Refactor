cmake_minimum_required(VERSION 3.25.0)

include(FetchContent)

function(guarantee_Xerces_availability)
    set(GIT_REPOSITORY https://github.com/apache/xerces-c.git)
    set(GIT_TAG v3.2.4)

    set(FETCH_NAME xerces-c)
    set(PACKAGE_NAME Xerces-c)
    set(PACKAGE_PREFIX XERCES)
    set(PACKAGE_EXPORT Xerces::xerces
    )
    if (BUILD_THIRDPARTY_TEST)
        option(BUILD_${PACKAGE_NAME}_AVAILABILITY_TEST "Build ${PACKAGE_NAME} sample project for testing" ON)
    endif()
    cmake_parse_arguments("${PACKAGE_NAME}" "REQUIRED" "" ""  ${ARGN})
    find_package(${PACKAGE_NAME} QUIET)
    Set(FETCHCONTENT_QUIET FALSE)
    option(MOHSES_FETCH_THIRDPARTY "This option will try to fetch third party dependencies for building" ON)
    if ( NOT ${PACKAGE_NAME}_FOUND )
        if (MOHSES_FETCH_THIRDPARTY)

            set(CMAKE_FOLDER "${CMAKE_FOLDER}/${PACKAGE_NAME}")
            set(CMAKE_CXX_STANDARD 20)
            set(CMAKE_CXX_STANDARD_REQUIRED ON)
            set(CMAKE_CXX_EXTENSIONS OFF)

            FetchContent_Declare(
                ${PACKAGE_NAME}
                GIT_REPOSITORY ${GIT_REPOSITORY} 
                GIT_TAG ${GIT_TAG}
                GIT_PROGRESS
                OVERRIDE_FIND_PACKAGE  TRUE
                CXX_STANDARD 20
            )
            message(STATUS "[${PACKAGE_NAME}] not found -- Fetching ${GIT_TAG}")

            FetchContent_MakeAvailable(${PACKAGE_NAME})

            if(NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${FETCH_NAME}-extra.cmake AND
               NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${FETCH_NAMEME}Extra.cmake)

            set(${PACKAGE_PREFIX}_INCLUDE_DIR $<INSTALL_INTERFACE:include>$<BUILD_INTERFACE:${${FETCH_NAME}_SOURCE_DIR}>)
            set(${PACKAGE_PREFIX}_INCLUDE_DIRS $<INSTALL_INTERFACE:include>$<BUILD_INTERFACE:${${FETCH_NAME}_SOURCE_DIR}>)
           
               file(WRITE ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${FETCH_NAME}-extra.cmake                                
               "
                  if(\"\${${PACKAGE_PREFIX}_INCLUDE_DIR}\" STREQUAL \"\" AND TARGET  ${EXPORT_NAME})
                    set(${PACKAGE_PREFIX}_INCLUDE_DIR ${${PACKAGE_PREFIX}_INCLUDE_DIR})
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_INCLUDE_DIRS}\" STREQUAL \"\" AND TARGET  ${EXPORT_NAME})
                    set(${PACKAGE_PREFIX}_INCLUDE_DIRS ${${PACKAGE_PREFIX}_INCLUDE_DIRS})
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_LIBRARY_DEBUG}\" STREQUAL \"\" AND TARGET  ${EXPORT_NAME})
                    set(${PACKAGE_PREFIX}_LIBRARY $<LIBRARY_OUTPUT_NAME_DEBUG,${PACKAGE_NAME}>)
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_LIBRARY_RELEASE}\" STREQUAL \"\" AND TARGET  ${EXPORT_NAME})
                    set(${PACKAGE_PREFIX}_LIBRARY_RELEASE  $<LIBRARY_OUTPUT_NAME_RELEASE,${PACKAGE_NAME}>)
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_LIBRARY_DEBUG_DYNAMIC}\" STREQUAL \"\" AND TARGET  ${EXPORT_NAME})
                    set(${PACKAGE_PREFIX}_LIBRARY $<LIBRARY_OUTPUT_NAME_DEBUG,${PACKAGE_NAME}>)
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_LIBRARY_RELEASE_DYNAMIC}\" STREQUAL \"\" AND TARGET  ${EXPORT_NAME})
                    set(${PACKAGE_PREFIX}_LIBRARY_RELEASE  $<LIBRARY_OUTPUT_NAME_RELEASE,${PACKAGE_NAME}>)
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_LIBRARIES}\" STREQUAL \"\" AND TARGET  ${EXPORT_NAME})
                    set(${PACKAGE_PREFIX}_LIBRARIES  optimized \${${PACKAGE_PREFIX}_LIBRARY_RELEASE} debug \${${PACKAGE_PREFIX}_LIBRARY_RELEASE} )
                  endif()
               ")
            endif()


            if (NOT TARGET ${PACKAGE_EXPORT})
                add_library(${PACKAGE_EXPORT} INTERFACE IMPORTED GLOBAL)
                
                set_target_properties(${PACKAGE_EXPORT}
                PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES
                ${${FETCH_NAME}_SOURCE_DIR}
                )
                target_include_directories(${PACKAGE_EXPORT} INTERFACE $<INSTALL_INTERFACE:include> $<BUILD_INTERFACE:${${FETCH_NAME}_SOURCE_DIR}/src> $<BUILD_INTERFACE:${${FETCH_NAME}_BINARY_DIR}/src>) 
                target_link_libraries(${PACKAGE_EXPORT} INTERFACE xerces-c)
              endif()
        endif()
    endif()

    if (${PACKAGE_NAME}_REQUIRED AND NOT ${PACKAGE_NAME}_FOUND)
        message(FATAL_ERROR "Unable to find ${PACKAGE_NAME} or fetch it from ${GIT_REPOSITROY}. 
        Check your network connection or install the ${PACKAGE_NAME} package and configure your CMAKE_PREFIX_PATH to ensure visibility
        https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
        https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
    endif()


endfunction()

guarantee_Xerces_availability()
