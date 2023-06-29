cmake_minimum_required(VERSION 3.20.0)

include(gaurentee_fastcdr)
include(gaurentee_TinyXML2)
include(gaurentee_foonathan_memory)
include (gaurentee_openssl)
function(guarantee_fastddr_availability)
    set( GIT_REPOSITORY  https://github.com/eProsima/Fast-DDS.git)
    set( GIT_TAG v2.10.0)
    if (BUILD_THIRDPARTY_TEST)
        option(BUILD_fastddr_AVAILABILITY_TEST "Build fastddr sample project for testing" ON)
    endif()
    cmake_parse_arguments("fastddr" "REQUIRED" "" ""  ${ARGN})
    guarantee_fastcdr_availability()
    guarantee_TinyXML2_availability()
    gaurentee_foonathan_memory_availability()
    guarantee_openssl_availability()
    find_package(fastddr QUIET)
    Set(FETCHCONTENT_QUIET FALSE)
    option(MOHSES_FETCH_THIRDPARTY "This option will try to fetch third party dependencies for building" ON)
    if ( NOT fastddr_FOUND )
        if (MOHSES_FETCH_THIRDPARTY)
            set(CMAKE_FOLDER "${CMAKE_FOLDER}/fastddr")
            FetchContent_Declare(
                fastddr
                GIT_REPOSITORY ${GIT_REPOSITORY}
                GIT_TAG ${GIT_TAG}
                GIT_PROGRESS TRUE
                OVERRIDE_FIND_PACKAGE  TRUE
                CMAKE_ARGS -D THIRDPARTY_Asio="ON"
                           "-Wno-dev"
            )

            set(TINYXML2_INCLUDE_DIRS $<)
            message(STATUS "fastddr not found Fetching 2.10")
            FetchContent_MakeAvailable(fastddr)

            if (BUILD_fastddr_AVAILABILITY_TEST AND BUILD_THIRDPARTY_TEST)
                add_executable(fastddr_test ${PROJECT_SOURCE_DIR}/cmake/tests/fastddr.cpp)
                set_target_properties(fastddr_test PROPERTIES FOLDER "${CMAKE_FOLDER}/Tests")
                target_link_libraries(fastddr_test PRIVATE fastddr fastcdr foonathan tinyxml2::tinyxml2)            
            endif()
        endif()
    endif()

    if (fastddr_REQUIRED AND NOT fastddr_FOUND)
        message(FATAL_ERROR "Unable to find fastddr or fetch it from${GIT_REPOSITORY}. 
        Check your network connection or install the fastddr package and configure your CMAKE_PREFIX_PATH to ensure visibility
        https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
        https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
    endif()


endfunction()
