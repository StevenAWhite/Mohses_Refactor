cmake_minimum_required(VERSION 3.20.0)

include (FetchContent)

function(guarantee_fastddr_availability)
    set( GIT_REPOSITORY  https://github.com/eProsima/Fast-DDS.git)
    set( GIT_TAG v2.10.0)
    set( PACKAGE_NAME  fastrtps)
    set( EXPORT_NAME    eProsima::fastrtps)
    set( EXPORT_NAME2   eProsima::fastdds)
    set( PACKAGE_PREFIX FASTRTPS)

    if (BUILD_THIRDPARTY_TEST)
        option(BUILD_${PACKAGE_NAME}_AVAILABILITY_TEST "Build ${PACKAGE_NAME} sample project for testing" ON)
    endif()
    cmake_parse_arguments("${PACKAGE_NAME}" "REQUIRED" "" ""  ${ARGN})
    find_package(fastcdr REQUIRED )
    find_package(TinyXML2 REQUIRED )
    find_package(foonathan_memory REQUIRED )
    find_package(OpenSSL REQUIRED )
    find_package(${PACKAGE_NAME} QUIET GLOBAL)
    Set(FETCHCONTENT_QUIET FALSE)
    option(MOHSES_FETCH_THIRDPARTY "This option will try to fetch third party dependencies for building" ON)
    if ( NOT ${PACKAGE_NAME}_FOUND )
        if (MOHSES_FETCH_THIRDPARTY)
            set(CMAKE_FOLDER "${CMAKE_FOLDER}/${PACKAGE_NAME}")
            set(THIRDPARTY_Asio "ON"  CACHE STRING "Controls ASIO being built by FASTRTPS")
            FetchContent_Declare(
                ${PACKAGE_NAME}
                GIT_REPOSITORY ${GIT_REPOSITORY}
                GIT_TAG ${GIT_TAG}
                GIT_PROGRESS TRUE
                OVERRIDE_FIND_PACKAGE  TRUE
                CMAKE_ARGS -D THIRDPARTY_Asio=ON
                           "-Wno-dev"
            )

            set(TINYXML2_INCLUDE_DIRS $<)
            message(STATUS "${PACKAGE_NAME} not found Fetching 2.10")
            FetchContent_MakeAvailable(${PACKAGE_NAME})
            if(NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PACKAGE_NAME}-extra.cmake AND
            NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PACKAGE_NAME}Extra.cmake)
               file(WRITE ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PACKAGE_NAME}-extra.cmake                                
               "
                  if(\"\${${PACKAGE_PREFIX}_INCLUDE_DIR}\" STREQUAL \"\" AND TARGET  ${PACKAGE_NAME})
                    set(${PACKAGE_PREFIX}_INCLUDE_DIR ${${PACKAGE_PREFIX}_INCLUDE_DIR})
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_INCLUDE_DIRS}\" STREQUAL \"\" AND TARGET  ${PACKAGE_NAME})
                    set(${PACKAGE_PREFIX}_INCLUDE_DIRS ${${PACKAGE_PREFIX}_INCLUDE_DIR})
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_LIBRARY_DEBUG}\" STREQUAL \"\" AND TARGET  ${PACKAGE_NAME})
                    set(${PACKAGE_PREFIX}_LIBRARY ${${PACKAGE_PREFIX}_LIBRARY_DEBUG})
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_LIBRARY_RELEASE}\" STREQUAL \"\" AND TARGET  ${PACKAGE_NAME})
                    set(${PACKAGE_PREFIX}_LIBRARY_RELEASE  ${${PACKAGE_PREFIX}_LIBRARY_RELEASE})
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_LIBRARIES}\" STREQUAL \"\" AND TARGET  ${PACKAGE_NAME})
                    set(${PACKAGE_PREFIX}_LIBRARIES  optimized ${${PACKAGE_PREFIX}_LIBRARY_RELEASE} debug ${${PACKAGE_PREFIX}_LIBRARY_DEBUG})
                  endif()
               ")
            endif()
#            install(TARGETS fastrtps EXPORT fastrtps)  
 #           export(TARGETS fastrtps FILE fastrtps-targets.cmake)
            if (BUILD_${PACKAGE_NAME}_AVAILABILITY_TEST AND BUILD_THIRDPARTY_TEST)
                add_executable(${PACKAGE_NAME}_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/${PACKAGE_NAME}.cpp)
                set_target_properties(${PACKAGE_NAME}_test PROPERTIES FOLDER "${CMAKE_FOLDER}/Tests")
                target_link_libraries(${PACKAGE_NAME}_test PRIVATE fastrtps fastcdr foonathan_memory tinyxml2::tinyxml2)            
            endif()
        endif()
    else()
       find_package(${PACKAGE_NAME} REQUIRED GLOBAL)
    endif()

    if (NOT ${PACKAGE_NAME}_FOUND)
        message(FATAL_ERROR "Unable to find ${PACKAGE_NAME} or fetch it from${GIT_REPOSITORY}. 
        Check your network connection or install the ${PACKAGE_NAME} package and configure your CMAKE_PREFIX_PATH to ensure visibility
        https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
        https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
    endif()

    if (TARGET ${PACKAGE_NAME} AND NOT TARGET ${EXPORT_NAME})
      add_library(${EXPORT_NAME} ALIAS ${PACKAGE_NAME})
    endif()
    if (TARGET ${PACKAGE_NAME} AND NOT TARGET ${EXPORT_NAME2})
      add_library(${EXPORT_NAME2} ALIAS ${PACKAGE_NAME})
    endif()

endfunction()

guarantee_fastddr_availability()
