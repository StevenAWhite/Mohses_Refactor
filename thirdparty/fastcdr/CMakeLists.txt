cmake_minimum_required(VERSION 3.25.0)

include(FetchContent)

function(guarantee_fastcdr_availability)
    set(GIT_REPOSITORY https://github.com/eProsima/Fast-CDR.git)
    set(GIT_TAG  v1.0.27)
    set(PACKAGE_NAME fastcdr)
    set(EXPORT_NAME eProsima::fastcdr)
    set(PACKAGE_PREFIX FASTCDR)

    cmake_parse_arguments("${PACKAGE_NAME}" "REQUIRED" "" ""  ${ARGN})
    find_package(${PACKAGE_NAME} QUIET GLOBAL)
    Set(FETCHCONTENT_QUIET FALSE)
    if ( NOT ${PACKAGE_NAME}_FOUND )
        if (MOHSES_FETCH_THIRDPARTY AND NOT ${PACKAGE_NAME}_POPULATED)
            if (BUILD_THIRDPARTY_TEST)
                option(BUILD_${PACKAGE_NAME}_AVAILABILITY_TEST "Build ${PACKAGE_NAME} sample project for testing" ON)
            endif()
            set(CMAKE_FOLDER "${CMAKE_FOLDER}/${PACKAGE_NAME}")
            FetchContent_Declare(
                ${PACKAGE_NAME}
                GIT_REPOSITORY ${GIT_REPOSITORY}
                GIT_TAG ${GIT_TAG}
                GIT_PROGRESS TRUE
                OVERRIDE_FIND_PACKAGE TRUE
                CMAKE_ARGS  "-Wno-dev"
            )
            message(STATUS "${PACKAGE_NAME} not found Fetching 1.0.27")
            FetchContent_MakeAvailable(${PACKAGE_NAME})

            get_target_property(${PACKAGE_PREFIX}_INCLUDE_DIR  ${PACKAGE_NAME} INCLUDE_DIRECTORIES)
            get_target_property(${PACKAGE_PREFIX}_LIBRARY  ${PACKAGE_NAME} LIBRARY_OUTPUT_NAME)

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
                    set(${PACKAGE_PREFIX}_LIBRARY ${${PACKAGE_PREFIX}_LIBRARY})
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_LIBRARY_RELEASE}\" STREQUAL \"\" AND TARGET  ${PACKAGE_NAME})
                    set(${PACKAGE_PREFIX}_LIBRARY_RELEASE  ${${PACKAGE_PREFIX}_LIBRARY})
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_LIBRARIES}\" STREQUAL \"\" AND TARGET  ${PACKAGE_NAME})
                    get_target_property(${PACKAGE_PREFIX}_LIBRARY  ${PACKAGE_NAME} LIBRARY_OUTPUT_NAME) 
                  endif()
               ")
            endif()
            install(TARGETS ${PACKAGE_NAME} EXPORT fastrtps)  
            export(TARGETS ${PACKAGE_NAME} FILE ${PACKAGE_NAME}-targets.cmake)
            if (BUILD_${PACKAGE_NAME}_AVAILABILITY_TEST AND BUILD_THIRDPARTY_TEST AND NOT TARGET ${PACKAGE_NAME}_test)
                add_executable(${PACKAGE_NAME}_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/${PACKAGE_NAME}.cpp)
                set_target_properties(${PACKAGE_NAME}_test PROPERTIES FOLDER "${CMAKE_FOLDER}/Tests")
                target_link_libraries(${PACKAGE_NAME}_test PRIVATE ${PACKAGE_NAME})            
            endif()
        endif()
    endif()

    if (TARGET ${PACKAGE_NAME} AND NOT TARGET ${EXPORT_NAME})
      add_library(${EXPORT_NAME} ALIAS ${PACKAGE_NAME})
    endif()

    find_package(${PACKAGE_NAME} REQUIRED GLOBAL)

    if (NOT ${PACKAGE_NAME}_FOUND AND NOT depname_POPULATED)
        message(FATAL_ERROR "Unable to find ${PACKAGE_NAME} or fetch it from ${GIT_REPOSITORY}. 
        Check your network connection or install the FastCDR package and configure your CMAKE_PREFIX_PATH to ensure visibility
        https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
        https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
    endif()


endfunction()

guarantee_fastcdr_availability()
