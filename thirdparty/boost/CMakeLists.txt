cmake_minimum_required(VERSION 3.25.0)

include(FetchContent)

function(guarantee_boost_availability)
    set(GIT_REPOSITORY https://github.com/boostorg/boost.git)
    set(GIT_TAG boost-1.82.0)
    set(PACKAGE_NAME Boost)
    set(FETCH_NAME boost)
    set(PACKAGE_PREFIX BOOST)

if (BUILD_THIRDPARTY_TEST)
    option(BUILD_${PACKAGE_PREFIX}_AVAILABILITY_TEST "Build Boost sample project for testing" ON)
endif()
cmake_parse_arguments("Boost" "REQUIRED" "" ""  ${ARGN})
find_package(${PACKAGE_NAME} QUIET GLOBAL)
    Set(FETCHCONTENT_QUIET FALSE)
    option(MOHSES_FETCH_THIRDPARTY "This option will try to fetch third party dependencies for building" ON)
    if ( NOT ${PACKAGE_NAME}_FOUND)
        if (MOHSES_FETCH_THIRDPARTY)
            set(${PACKAGE_PREFIX}_INCLUDE_LIBRARIES algorithm assign filesystem foreach lambda math program_options process serialization system uuid)
            set(${PACKAGE_PREFIX}_ENABLE_CMAKE ON)
            set(CMAKE_FOLDER "${CMAKE_FOLDER}/${PACKAGE_NAME}")
            FetchContent_Declare(
                ${PACKAGE_NAME}
                GIT_REPOSITORY ${GIT_REPOSITORY}
                GIT_TAG ${GIT_TAG}
                GIT_PROGRESS TRUE
                OVERRIDE_FIND_PACKAGE TRUE
            )
            message(STATUS "${PACKAGE_NAME} not found Fetching 1.82")
            FetchContent_MakeAvailable(${PACKAGE_NAME})

            if (BUILD_${PACKAGE_PREFIX}_AVAILABILITY_TEST AND BUILD_THIRDPARTY_TEST)
                add_executable(${PACKAGE_NAME}_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/${PACKAGE_NAME}.cpp)
                set_target_properties(${PACKAGE_NAME}_test PROPERTIES FOLDER "${CMAKE_FOLDER}/Tests")
                target_link_libraries(${PACKAGE_NAME}_test PRIVATE ${PACKAGE_NAME}::lambda ${PACKAGE_NAME}::headers)            
            endif()
        endif()
    endif()

    find_package(${PACKAGE_NAME} REQUIRED COMPONENTS algorithm assign filesystem foreach lambda math program_options process serialization system uuid GLOBAL)
    
    if (NOT ${PACKAGE_NAME}_FOUND)
        message(FATAL_ERROR "Unable to find ${PACKAGE_NAME} or fetch it from ${GIT_REPOSITORY}. 
        Check your network connection or install the ${PACKAGE_NAME} package and configure your CMAKE_PREFIX_PATH to ensure visibility
        https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
        https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
    endif()

endfunction()

guarantee_boost_availability()
