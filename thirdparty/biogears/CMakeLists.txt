cmake_minimum_required(VERSION 3.25.0)

include(FetchContent)

function(guarantee_BioGears_availability)
    set(GIT_REPOSITORY https://github.com/BioGearsEngine/core.git)
    set(GIT_TAG trunk)

    set(PACKAGE_NAME Biogears)
    set(PACKAGE_PREFIX BioGears)
    set(PACKAGE_EXPORT Biogears::libbiogears
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
            set(Biogears_BUILD_TOOLS OFF CACHE INTERNAL "Build tools for Biogears command line" FORCE)
            set(Biogears_BUILD_TESTS OFF CACHE INTERNAL "Build test suite for Biogears" FORCE)
            set(Biogears_BUILD_HOWTOS OFF CACHE  INTERNAL "Build samples for biogears" FORCE)
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
               get_target_property(${PACKAGE_PREFIX}_INCLUDE_DIR  ${PACKAGE_EXPORT} INCLUDE_DIRECTORIES)

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
             install(TARGETS ${EXPORT_NAME} EXPORT ${PACKAGE_NAME})  
             export(TARGETS ${EXPORT_NAME} FILE ${PACKAGE_NAME}-targets.cmake)

            if (BUILD_${PACKAGE_NAME}_AVAILABILITY_TEST AND BUILD_THIRDPARTY_TEST)
                add_executable(${PACKAGE_NAME}_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/${PACKAGE_NAME}.cpp )
                set_target_properties(${PACKAGE_NAME}_test PROPERTIES FOLDER "${CMAKE_FOLDER}/Tests")
                target_link_libraries(${PACKAGE_NAME}_test PRIVATE ${PACKAGE_EXPORT} )            
            endif()
        endif()
    endif()

    find_package(${PACKAGE_NAME} REQUIRED GLOBAL)
    if (NOT ${PACKAGE_NAME}_FOUND)
        message(FATAL_ERROR "Unable to find ${PACKAGE_NAME} or fetch it from ${GIT_REPOSITROY}. 
        Check your network connection or install the ${PACKAGE_NAME} package and configure your CMAKE_PREFIX_PATH to ensure visibility
        https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
        https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
    endif()


endfunction()

guarantee_BioGears_availability()
