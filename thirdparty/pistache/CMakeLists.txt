cmake_minimum_required(VERSION 3.25.0)

include(FetchContent)

function(guarantee_Pistache_availability)
    set(GIT_REPOSITORY https://github.com/pistacheio/pistache.git)
    set(GIT_TAG 494e1bca9d435fbc6a81a56b365b953a2b63ac71)

    set(PROJECT_NAME Pistache)
    set(PROJECT_PREFIX PISTACHE)
    set(PROJECT_EXPORT pistache::static)
    set(PROJECT_EXPORT2 pistache::shared)

    if (BUILD_THIRDPARTY_TEST)
        option(BUILD_${PROJECT_NAME}_AVAILABILITY_TEST "Build ${PROJECT_NAME} sample project for testing" ON)
    endif()
    cmake_parse_arguments("${PROJECT_NAME}" "REQUIRED" "" ""  ${ARGN})
    find_package(${PROJECT_NAME} QUIET)
    Set(FETCHCONTENT_QUIET FALSE)
    option(MOHSES_FETCH_THIRDPARTY "This option will try to fetch third party dependencies for building" ON)
    if ( NOT ${PROJECT_NAME}_FOUND )
        if (MOHSES_FETCH_THIRDPARTY)

            set(PISTACHE_BUILD_TESTS OFF CACHE INTERNAL "DO not build PISTACHE TEST" )
            set(CMAKE_FOLDER "${CMAKE_FOLDER}/${PROJECT_NAME}")
            FetchContent_Declare(
                ${PROJECT_NAME}
                GIT_REPOSITORY ${GIT_REPOSITORY} 
                GIT_TAG ${GIT_TAG}
                GIT_PROGRESS TRUE
                OVERRIDE_FIND_PACKAGE  TRUE            
            )
            message(STATUS "${PROJECT_NAME} not found Fetching ${GIT_TAG}")          
    
            FetchContent_MakeAvailable(${PROJECT_NAME})

            if(NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PROJECT_NAME}-extra.cmake AND
            NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PROJECT_NAME}Extra.cmake)
               get_target_property(${PROJECT_PREFIX}_INCLUDE_DIR  pistache INCLUDE_DIRECTORIES)

               file(WRITE ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PROJECT_NAME}-extra.cmake                                
               "
                  if(\"\${${PROJECT_PREFIX}_INCLUDE_DIR}\" STREQUAL \"\" AND TARGET  ${PROJECT_EXPORT})
                    set(${PROJECT_PREFIX}_INCLUDE_DIR ${${PROJECT_PREFIX}_INCLUDE_DIR})
                  endif()
                  if(\"\${${PROJECT_PREFIX}_INCLUDE_DIRS}\" STREQUAL \"\" AND TARGET  ${PROJECT_EXPORT})
                    set(${PROJECT_PREFIX}_INCLUDE_DIRS ${${PROJECT_PREFIX}_INCLUDE_DIR})
                  endif()
                  if(\"\${${PROJECT_PREFIX}_LIBRARY}\" STREQUAL \"\" AND TARGET  ${PROJECT_EXPORT})
                    set(${PROJECT_PREFIX}_LIBRARY ${PROJECT_EXPORT})
                  endif()
                  if(\"\${${PROJECT_PREFIX}_LIBRARIES}\" STREQUAL \"\" AND TARGET  ${PROJECT_EXPORT})
                    set(${PROJECT_PREFIX}_LIBRARIES  ${PROJECT_EXPORT})
                  endif()
               ")
            endif()
             install(TARGETS pistache EXPORT ${PROJECT_NAME})  
             export(TARGETS pistache FILE ${PROJECT_NAME}-targets.cmake)

            if (BUILD_${PROJECT_NAME}_AVAILABILITY_TEST AND BUILD_THIRDPARTY_TEST)
                add_executable(${PROJECT_NAME}_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/${PROJECT_NAME}.cpp )
                set_target_properties(${PROJECT_NAME}_test PROPERTIES FOLDER "${CMAKE_FOLDER}/Tests" CXX_STANDARD 20)
                target_link_libraries(${PROJECT_NAME}_test PRIVATE ${PROJECT_EXPORT2} )            
            endif()
        endif()
    endif()

    if (${PROJECT_NAME}_REQUIRED AND NOT ${PROJECT_NAME}_FOUND)
        message(FATAL_ERROR "Unable to find ${PROJECT_NAME} or fetch it from ${GIT_REPOSITROY}. 
        Check your network connection or install the ${PROJECT_NAME} package and configure your CMAKE_PREFIX_PATH to ensure visibility
        https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
        https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
    endif()

    if (TARGET pistache AND NOT TARGET ${PROJECT_EXPORT})
      add_library(${PROJECT_EXPORT} ALIAS pistache)
    endif()

    if (TARGET pistache_shared AND NOT TARGET ${PROJECT_EXPORT2})
      add_library(${PROJECT_EXPORT2} ALIAS pistache_shared)
    endif()

endfunction()

guarantee_Pistache_availability()
