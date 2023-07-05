cmake_minimum_required(VERSION 3.20.0)

include(FetchContent)

function(guarantee_boost_availability)
    set(GIT_REPOSITORY https://github.com/boostorg/boost.git)
    set(GIT_TAG boost-1.82.0)
    set(PROJECT_NAME boost)
    set(PROJECT_PREFIX ${PROJECT_PREFIX})

if (BUILD_THIRDPARTY_TEST)
    option(BUILD_${PROJECT_PREFIX}_AVAILABILITY_TEST "Build Boost sample project for testing" ON)
endif()
cmake_parse_arguments("Boost" "REQUIRED" "" ""  ${ARGN})
find_package(Boost QUIET)
    Set(FETCHCONTENT_QUIET FALSE)
    option(MOHSES_FETCH_THIRDPARTY "This option will try to fetch third party dependencies for building" ON)
    if ( NOT Boost_FOUND)
        if (MOHSES_FETCH_THIRDPARTY)
            set(${PROJECT_PREFIX}_INCLUDE_LIBRARIES math filesystem serialization system archive program_options lambda)
            set(${PROJECT_PREFIX}_ENABLE_CMAKE ON)
            set(CMAKE_FOLDER "${CMAKE_FOLDER}/Boost")
            FetchContent_Declare(
                Boost
                GIT_REPOSITORY ${GIT_REPOSITORY}
                GIT_TAG ${GIT_TAG}
                GIT_PROGRESS TRUE
                OVERRIDE_FIND_PACKAGE TRUE
            )
            message(STATUS "Boost not found Fetching 1.82")
            FetchContent_MakeAvailable(Boost)

            if (BUILD_${PROJECT_PREFIX}_AVAILABILITY_TEST AND BUILD_THIRDPARTY_TEST)
                add_executable(${PROJECT_NAME}_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/${PROJECT_NAME}.cpp)
                set_target_properties(${PROJECT_NAME}_test PROPERTIES FOLDER "${CMAKE_FOLDER}/Tests")
                target_link_libraries(${PROJECT_NAME}_test PRIVATE Boost::filesystem Boost::headers)            
            endif()
        endif()
    endif()
    
    if (Boost_REQUIRED AND NOT Boost_FOUND)
        message(FATAL_ERROR "Unable to find Boost or fetch it from ${GIT_REPOSITORY}. 
        Check your network connection or install the Boost package and configure your CMAKE_PREFIX_PATH to ensure visibility
        https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
        https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
    endif()

endfunction()

guarantee_boost_availability()
