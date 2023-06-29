cmake_minimum_required(VERSION 3.20.0)

function(guarantee_fastcdr_availability)
    set(GIT_REPOSITORY https://github.com/eProsima/Fast-CDR.git)
    set(GIT_TAG  v1.0.27)
    if (BUILD_THIRDPARTY_TEST)
        option(BUILD_fastcdr_AVAILABILITY_TEST "Build fastcdr sample project for testing" ON)
    endif()
    cmake_parse_arguments("fastcdr" "REQUIRED" "" ""  ${ARGN})
    find_package(fastcdr QUIET)
    Set(FETCHCONTENT_QUIET FALSE)
    option(MOHSES_FETCH_THIRDPARTY "This option will try to fetch third party dependencies for building" ON)
    if ( NOT fastcdr_FOUND )
        if (MOHSES_FETCH_THIRDPARTY AND NOT fastcdr_POPULATED)
            set(CMAKE_FOLDER "${CMAKE_FOLDER}/fastcdr")
            FetchContent_Declare(
                fastcdr
                GIT_REPOSITORY ${GIT_REPOSITORY}
                GIT_TAG ${GIT_TAG}
                GIT_PROGRESS TRUE
                OVERRIDE_FIND_PACKAGE TRUE
                CMAKE_ARGS  "-Wno-dev"
            )
            message(STATUS "fastcdr not found Fetching 1.0.27")
            FetchContent_MakeAvailable(fastcdr)

            export(TARGETS fastcdr FILE fastcdr-targets.cmake)
            if (BUILD_fastcdr_AVAILABILITY_TEST AND BUILD_THIRDPARTY_TEST AND NOT TARGET fastcdr_test)
                add_executable(fastcdr_test ${PROJECT_SOURCE_DIR}/cmake/tests/fastcdr.cpp)
                set_target_properties(fastcdr_test PROPERTIES FOLDER "${CMAKE_FOLDER}/Tests")
                target_link_libraries(fastcdr_test PRIVATE fastcdr)            
            endif()
        endif()
    endif()

    if (fastcdr_REQUIRED AND NOT fastcdr_FOUND AND NOT depname_POPULATED)
        message(FATAL_ERROR "Unable to find fastcdr or fetch it from ${GIT_REPOSITORY}. 
        Check your network connection or install the FastCDR package and configure your CMAKE_PREFIX_PATH to ensure visibility
        https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
        https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
    endif()

endfunction()
