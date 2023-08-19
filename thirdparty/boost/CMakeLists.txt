cmake_minimum_required(VERSION 3.25.0)

include(FetchContent)

function(guarantee_boost_availability)
    set(GIT_REPOSITORY https://github.com/boostorg/boost.git)
    set(GIT_TAG boost-1.82.0)
    set(PACKAGE_NAME Boost)
    set(FETCH_NAME boost)
    set(PACKAGE_PREFIX BOOST)

cmake_parse_arguments("Boost" "REQUIRED" "" ""  ${ARGN})
find_package(${PACKAGE_NAME} QUIET GLOBAL)
    Set(FETCHCONTENT_QUIET FALSE)
    if ( NOT ${PACKAGE_NAME}_FOUND)
        message(STATUS "${PACKAGE_NAME} not found! MOHSES_FETCH_THIRDPARTY=${MOHSES_FETCH_THIRDPARTY}")
        if (MOHSES_FETCH_THIRDPARTY)
            message(STATUS "${PACKAGE_NAME} not found!")
            if (BUILD_THIRDPARTY_TEST)
                option(BUILD_${PACKAGE_PREFIX}_AVAILABILITY_TEST "Build Boost sample project for testing" ON)
            endif()
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

    find_package(${PACKAGE_NAME} REQUIRED COMPONENTS filesystem program_options serialization system thread GLOBAL)
    
    if (NOT TARGET Boost::asio)
      message(STATUS "EXPORTING Boost::asio") 
      add_library(Boost::asio ALIAS Boost::headers)
    elseif(TARGET ${PACKAGE_EXPORT})
      message(STATUS "${PACKAGE_EXPORT} target exists")
    endif()

    if (NOT TARGET Boost::algorithm)
      message(STATUS "EXPORTING Boost::algorithm") 
      add_library(Boost::algorithm ALIAS Boost::headers)
    elseif(TARGET ${PACKAGE_EXPORT})
      message(STATUS "${PACKAGE_EXPORT} target exists")
    endif()

    if (NOT TARGET Boost::assign)
      message(STATUS "EXPORTING Boost::assign") 
      add_library(Boost::assign ALIAS Boost::headers)
    elseif(TARGET ${PACKAGE_EXPORT})
      message(STATUS "${PACKAGE_EXPORT} target exists")
    endif()

    if (NOT TARGET Boost::foreach)
      message(STATUS "EXPORTING Boost::foreach") 
      add_library(Boost::foreach ALIAS Boost::headers)
    elseif(TARGET ${PACKAGE_EXPORT})
      message(STATUS "${PACKAGE_EXPORT} target exists")
    endif()

    if (NOT TARGET Boost::process)
      message(STATUS "EXPORTING Boost::process") 
      add_library(Boost::process ALIAS Boost::headers)
    elseif(TARGET ${PACKAGE_EXPORT})
      message(STATUS "${PACKAGE_EXPORT} target exists")
    endif()

    if (NOT TARGET Boost::uuid)
      message(STATUS "EXPORTING Boost::uuid") 
      add_library(Boost::uuid ALIAS Boost::headers)
    elseif(TARGET ${PACKAGE_EXPORT})
      message(STATUS "${PACKAGE_EXPORT} target exists")
    endif()


    if (NOT ${PACKAGE_NAME}_FOUND)
        message(FATAL_ERROR "Unable to find ${PACKAGE_NAME} or fetch it from ${GIT_REPOSITORY}. 
        Check your network connection or install the ${PACKAGE_NAME} package and configure your CMAKE_PREFIX_PATH to ensure visibility
        https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
        https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
    endif()

endfunction()

guarantee_boost_availability()
