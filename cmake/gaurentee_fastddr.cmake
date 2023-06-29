cmake_minimum_required(VERSION 3.20.0)

include(gaurentee_fastcdr)
include(gaurentee_TinyXML2)
include(gaurentee_foonathan_memory)
include (gaurentee_openssl)
function(guarantee_fastddr_availability)
    set( GIT_REPOSITORY  https://github.com/eProsima/Fast-DDS.git)
    set( GIT_TAG v2.10.0)
    set( PROJECT_NAME  fastddr)
    set( PROJECT_PREFIX FASTDDR)

    if (BUILD_THIRDPARTY_TEST)
        option(BUILD_${PROJECT_NAME}_AVAILABILITY_TEST "Build ${PROJECT_NAME} sample project for testing" ON)
    endif()
    cmake_parse_arguments("${PROJECT_NAME}" "REQUIRED" "" ""  ${ARGN})
    guarantee_fastcdr_availability()
    guarantee_TinyXML2_availability()
    gaurentee_foonathan_memory_availability()
    guarantee_openssl_availability()
    find_package(${PROJECT_NAME} QUIET)
    Set(FETCHCONTENT_QUIET FALSE)
    option(MOHSES_FETCH_THIRDPARTY "This option will try to fetch third party dependencies for building" ON)
    if ( NOT ${PROJECT_NAME}_FOUND )
        if (MOHSES_FETCH_THIRDPARTY)
            set(CMAKE_FOLDER "${CMAKE_FOLDER}/${PROJECT_NAME}")
            FetchContent_Declare(
                ${PROJECT_NAME}
                GIT_REPOSITORY ${GIT_REPOSITORY}
                GIT_TAG ${GIT_TAG}
                GIT_PROGRESS TRUE
                OVERRIDE_FIND_PACKAGE  TRUE
                CMAKE_ARGS -D THIRDPARTY_Asio="ON"
                           "-Wno-dev"
            )

            set(TINYXML2_INCLUDE_DIRS $<)
            message(STATUS "${PROJECT_NAME} not found Fetching 2.10")
            FetchContent_MakeAvailable(${PROJECT_NAME})
            if(NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PROJECT_NAME}-extra.cmake AND
            NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PROJECT_NAME}Extra.cmake)
               file(WRITE ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PROJECT_NAME}-extra.cmake                                
               "
                  if(\"\${${PROJECT_PREFIX}_INCLUDE_DIR}\" STREQUAL \"\" AND TARGET  ${PROJECT_NAME})
                    set(${PROJECT_PREFIX}_INCLUDE_DIR ${${PROJECT_PREFIX}_INCLUDE_DIR})
                  endif()
                  if(\"\${${PROJECT_PREFIX}_INCLUDE_DIRS}\" STREQUAL \"\" AND TARGET  ${PROJECT_NAME})
                    set(${PROJECT_PREFIX}_INCLUDE_DIRS ${${PROJECT_PREFIX}_INCLUDE_DIR})
                  endif()
                  if(\"\${${PROJECT_PREFIX}_LIBRARY_DEBUG}\" STREQUAL \"\" AND TARGET  ${PROJECT_NAME})
                    set(${PROJECT_PREFIX}_LIBRARY ${${PROJECT_PREFIX}_LIBRARY_DEBUG})
                  endif()
                  if(\"\${${PROJECT_PREFIX}_LIBRARY_RELEASE}\" STREQUAL \"\" AND TARGET  ${PROJECT_NAME})
                    set(${PROJECT_PREFIX}_LIBRARY_RELEASE  ${${PROJECT_PREFIX}_LIBRARY_RELEASE})
                  endif()
                  if(\"\${${PROJECT_PREFIX}_LIBRARIES}\" STREQUAL \"\" AND TARGET  ${PROJECT_NAME})
                    set(${PROJECT_PREFIX}_LIBRARIES  optimized ${${PROJECT_PREFIX}_LIBRARY_RELEASE} debug ${${PROJECT_PREFIX}_LIBRARY_DEBUG})
                  endif()
               ")
            endif()
            install(TARGETS fastrtps EXPORT fastrtps)  
            export(TARGETS fastrtps FILE fastrtps-targets.cmake)
            if (BUILD_${PROJECT_NAME}_AVAILABILITY_TEST AND BUILD_THIRDPARTY_TEST)
                add_executable(${PROJECT_NAME}_test ${PROJECT_SOURCE_DIR}/cmake/tests/${PROJECT_NAME}.cpp)
                set_target_properties(${PROJECT_NAME}_test PROPERTIES FOLDER "${CMAKE_FOLDER}/Tests")
                target_link_libraries(${PROJECT_NAME}_test PRIVATE fastrtps fastcdr foonathan_memory tinyxml2::tinyxml2)            
            endif()
        endif()
    endif()

    if (${PROJECT_NAME}_REQUIRED AND NOT ${PROJECT_NAME}_FOUND)
        message(FATAL_ERROR "Unable to find ${PROJECT_NAME} or fetch it from${GIT_REPOSITORY}. 
        Check your network connection or install the ${PROJECT_NAME} package and configure your CMAKE_PREFIX_PATH to ensure visibility
        https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
        https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
    endif()


endfunction()
