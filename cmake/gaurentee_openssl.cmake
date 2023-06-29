cmake_minimum_required(VERSION 3.20.0)

function(guarantee_openssl_availability)
set(GIT_REPOSITORY https://github.com/viaduck/openssl-cmake.git )
set(GIT_TAG 3.0)
    if (BUILD_THIRDPARTY_TEST)
        option(BUILD_openssl_AVAILABILITY_TEST "Build openssl sample project for testing" ON)
    endif()
    cmake_parse_arguments("openssl" "REQUIRED" "" ""  ${ARGN})
    find_package(OpenSSL QUIET)
    Set(FETCHCONTENT_QUIET FALSE)
    option(MOHSES_FETCH_THIRDPARTY "This option will try to fetch third party dependencies for building" ON)
    if ( NOT openssl_FOUND AND NOT MSVC)
        if (MOHSES_FETCH_THIRDPARTY)
            set(CMAKE_FOLDER "${CMAKE_FOLDER}/openssl")
            FetchContent_Declare(
                openssl
                GIT_REPOSITORY ${GIT_REPOSITORY} 
                GIT_TAG ${GIT_TAG}
                GIT_PROGRESS TRUE
                OVERRIDE_FIND_PACKAGE  TRUE
                CMAKE_ARGS -D BUILD_OPENSSL=ON
                           -D OPENSSL_BRANCH=OpenSSL_3.1.0
            )
            export(TARGETS fastcdr )
            message(STATUS "openssl not found Fetching 2.10")
          
    
            FetchContent_MakeAvailable(openssl)

            if (BUILD_openssl_AVAILABILITY_TEST AND BUILD_THIRDPARTY_TEST)
                add_executable(openssl_test ${PROJECT_SOURCE_DIR}/cmake/tests/openssl.cpp)
                set_target_properties(openssl_test PROPERTIES FOLDER "${CMAKE_FOLDER}/Tests")
                target_link_libraries(openssl_test PRIVATE openssl)            
            endif()
        endif()
    endif()

    if (openssl_REQUIRED AND NOT openssl_FOUND)
    message(FATAL_ERROR "Unable to find openssl or fetch it from ${GIT_REPOSITROY}. 
    Check your network connection or install the openssl package and configure your CMAKE_PREFIX_PATH to ensure visibility
    https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
    https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
    endif()


endfunction()
