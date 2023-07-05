cmake_minimum_required(VERSION 3.20.0)

include(FetchContent)

function(guarantee_fastcdr_availability)
    set(GIT_REPOSITORY https://github.com/eProsima/Fast-CDR.git)
    set(GIT_TAG  v1.0.27)
    set(PROJECT_NAME fastcdr)
    set(PROJECT_PREFIX FASTCDR)

    if (BUILD_THIRDPARTY_TEST)
        option(BUILD_${PROJECT_NAME}_AVAILABILITY_TEST "Build ${PROJECT_NAME} sample project for testing" ON)
    endif()
    cmake_parse_arguments("${PROJECT_NAME}" "REQUIRED" "" ""  ${ARGN})
    find_package(${PROJECT_NAME} QUIET)
    Set(FETCHCONTENT_QUIET FALSE)
    option(MOHSES_FETCH_THIRDPARTY "This option will try to fetch third party dependencies for building" ON)
    if ( NOT ${PROJECT_NAME}_FOUND )
        if (MOHSES_FETCH_THIRDPARTY AND NOT ${PROJECT_NAME}_POPULATED)
            set(CMAKE_FOLDER "${CMAKE_FOLDER}/${PROJECT_NAME}")
            FetchContent_Declare(
                ${PROJECT_NAME}
                GIT_REPOSITORY ${GIT_REPOSITORY}
                GIT_TAG ${GIT_TAG}
                GIT_PROGRESS TRUE
                OVERRIDE_FIND_PACKAGE TRUE
                CMAKE_ARGS  "-Wno-dev"
            )
            message(STATUS "${PROJECT_NAME} not found Fetching 1.0.27")
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
            install(TARGETS ${PROJECT_NAME} EXPORT fastrtps)  
            export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}-targets.cmake)
            if (BUILD_${PROJECT_NAME}_AVAILABILITY_TEST AND BUILD_THIRDPARTY_TEST AND NOT TARGET ${PROJECT_NAME}_test)
                add_executable(${PROJECT_NAME}_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/${PROJECT_NAME}.cpp)
                set_target_properties(${PROJECT_NAME}_test PROPERTIES FOLDER "${CMAKE_FOLDER}/Tests")
                target_link_libraries(${PROJECT_NAME}_test PRIVATE ${PROJECT_NAME})            
            endif()
        endif()
    endif()

    if (${PROJECT_NAME}_REQUIRED AND NOT ${PROJECT_NAME}_FOUND AND NOT depname_POPULATED)
        message(FATAL_ERROR "Unable to find ${PROJECT_NAME} or fetch it from ${GIT_REPOSITORY}. 
        Check your network connection or install the FastCDR package and configure your CMAKE_PREFIX_PATH to ensure visibility
        https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
        https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
    endif()

endfunction()

guarantee_fastcdr_availability()
