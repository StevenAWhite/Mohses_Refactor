cmake_minimum_required(VERSION 3.25.0)

include(FetchContent)

function(guarantee_Eigen3_availability)
    set(GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git)
    set(GIT_TAG 3.4)

    set(PROJECT_NAME Eigen3)
    set(PROJECT_PREFIX Eigen3)
    set(PROJECT_EXPORT Eigen3::Eigen3
    )
    if (BUILD_THIRDPARTY_TEST)
        option(BUILD_${PROJECT_NAME}_AVAILABILITY_TEST "Build ${PROJECT_NAME} sample project for testing" ON)
    endif()
    cmake_parse_arguments("${PROJECT_NAME}" "REQUIRED" "" ""  ${ARGN})
    find_package(${PROJECT_NAME} QUIET)
    Set(FETCHCONTENT_QUIET FALSE)
    option(MOHSES_FETCH_THIRDPARTY "This option will try to fetch third party dependencies for building" ON)
    if ( NOT ${PROJECT_NAME}_FOUND )
        if (MOHSES_FETCH_THIRDPARTY)

            set(CMAKE_FOLDER "${CMAKE_FOLDER}/${PROJECT_NAME}")
            set(CMAKE_CXX_STANDARD 20)
            set(CMAKE_CXX_STANDARD_REQUIRED ON)
            set(CMAKE_CXX_EXTENSIONS OFF)

            set(BUILD_TESTING OFF CACHE  INTERNAL"Build Eigen Testing Files" FORCE)
            set(EIGEN_BUILD_DOCS OFF CACHE INTERNAL "Build Eigen Documents" FORCE)
            FetchContent_Declare(
                ${PROJECT_NAME}
                GIT_REPOSITORY ${GIT_REPOSITORY} 
                GIT_TAG ${GIT_TAG}
                GIT_PROGRESS
                OVERRIDE_FIND_PACKAGE  TRUE
                CXX_STANDARD 20
            )
        

            FetchContent_MakeAvailable(${PROJECT_NAME})

            if (NOT TARGET Eigen3::Eigen)
                add_library(Eigen3::Eigen INTERFACE IMPORTED GLOBAL)
                
                set_target_properties(Eigen3::Eigen
                PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES
                ${Eigen3_SOURCE_DIR}
                )
              endif()
        endif()
    endif()

    if (${PROJECT_NAME}_REQUIRED AND NOT ${PROJECT_NAME}_FOUND)
        message(FATAL_ERROR "Unable to find ${PROJECT_NAME} or fetch it from ${GIT_REPOSITROY}. 
        Check your network connection or install the ${PROJECT_NAME} package and configure your CMAKE_PREFIX_PATH to ensure visibility
        https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
        https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
    endif()


endfunction()

guarantee_Eigen3_availability()
