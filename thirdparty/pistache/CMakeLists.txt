cmake_minimum_required(VERSION 3.25.0)

include(FetchContent)

function(guarantee_Pistache_availability)
    message(STATUS "Looking for Pistache")
    set(GIT_REPOSITORY https://github.com/pistacheio/pistache.git)
    set(GIT_TAG 494e1bca9d435fbc6a81a56b365b953a2b63ac71)

    set(PACKAGE_NAME Pistache)
    set(PKG_CONFIG_NAME libpistache)
    set(PACKAGE_PREFIX PISTACHE)
    set(PACKAGE_EXPORT pistache::lib)

    if (BUILD_THIRDPARTY_TEST)
        option(BUILD_${PACKAGE_NAME}_AVAILABILITY_TEST "Build ${PACKAGE_NAME} sample project for testing" ON)
    endif()
    cmake_parse_arguments("${PACKAGE_NAME}" "REQUIRED" "" ""  ${ARGN})
    find_package(${PACKAGE_NAME} QUIET GLOBAL)
    Set(FETCHCONTENT_QUIET FALSE)
    option(MOHSES_FETCH_THIRDPARTY "This option will try to fetch third party dependencies for building" ON)
    if ( NOT ${PACKAGE_NAME}_FOUND )
        find_package(PkgConfig QUIET)
        if ( PkgConfig_FOUND )
         set(PKG_CONFIG_USE_CMAKE_PREFIX_PATH ON)
         pkg_search_module(${PACKAGE_NAME} IMPORTED_TARGET GLOBAL libpistache)
         if (${PACKAGE_NAME}_FOUND AND NOT TARGET pistache_shared)
           add_library(${PACKAGE_EXPORT} ALIAS PkgConfig::${PACKAGE_NAME})
         endif()
        elseif ( NOT ${PACKAGE_NAME}_FOUND )
          message(STATUS "${PACKAGE_NAME} not found")
          if (MOHSES_FETCH_THIRDPARTY)

              set(PISTACHE_BUILD_TESTS OFF CACHE INTERNAL "DO not build PISTACHE TEST" )
              set(BUILD_SHARED ON  CACHE INTERNAL "BUILD_SHARED LIBRARIES")
              set(CMAKE_FOLDER "${CMAKE_FOLDER}/${PACKAGE_NAME}")
              FetchContent_Declare(
                  ${PACKAGE_NAME}
                  GIT_REPOSITORY ${GIT_REPOSITORY} 
                  GIT_TAG ${GIT_TAG}
                  GIT_PROGRESS TRUE
                  OVERRIDE_FIND_PACKAGE  TRUE            
              )
              message(STATUS "${PACKAGE_NAME} not found Fetching ${GIT_TAG}")          
    
              FetchContent_MakeAvailable(${PACKAGE_NAME})

              if(NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PACKAGE_NAME}-extra.cmake AND
              NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PACKAGE_NAME}Extra.cmake)
                 get_target_property(${PACKAGE_PREFIX}_INCLUDE_DIR  pistache INCLUDE_DIRECTORIES)

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
               install(TARGETS pistache EXPORT ${PACKAGE_NAME})  
               export(TARGETS pistache FILE ${PACKAGE_NAME}-targets.cmake)

              if (BUILD_${PACKAGE_NAME}_AVAILABILITY_TEST AND BUILD_THIRDPARTY_TEST)
                  add_executable(${PACKAGE_NAME}_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/${PACKAGE_NAME}.cpp )
                  set_target_properties(${PACKAGE_NAME}_test PROPERTIES FOLDER "${CMAKE_FOLDER}/Tests" CXX_STANDARD 20)
                  target_link_libraries(${PACKAGE_NAME}_test PRIVATE ${PACKAGE_EXPORT2} )            
              endif()
          endif()
      endif()
    endif()

    if (NOT ${PACKAGE_NAME}_FOUND)
        message(FATAL_ERROR "Unable to find ${PACKAGE_NAME} or fetch it from ${GIT_REPOSITROY}. 
        Check your network connection or install the ${PACKAGE_NAME} package and configure your CMAKE_PREFIX_PATH to ensure visibility
        https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
        https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
    endif()

    if(TARGET pistache_shared AND NOT TARGET ${PACKAGE_EXPORT})
      message(STATUS "Creating ${PACKAGE_EXPORT} ALIAS of pistache_shared")
      add_library(${PACKAGE_EXPORT} ALIAS pistache_shared)
    endif()
    if (TARGET pistache AND NOT TARGET ${PACKAGE_EXPORT})
      message(STATUS "Creating ${PACKAGE_EXPORT} ALIAS of pistache")
      add_library(${PACKAGE_EXPORT} ALIAS pistache)
    endif()

endfunction()

guarantee_Pistache_availability()
