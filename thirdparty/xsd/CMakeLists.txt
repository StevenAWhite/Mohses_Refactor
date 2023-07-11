cmake_minimum_required(VERSION 3.25.0)

include(FetchContent)

function(guarantee_CodeSynthesis_availability)
    set(GIT_REPOSITORY https://github.com/StevenAWhite/CodeSynthesisXSD-Binary.git)
    set(GIT_TAG master)


    set(PACKAGE_NAME CodeSynthesis)
    set(FETCH_NAME   codesynthesis)
    set(PACKAGE_PREFIX XSD)
    set(PACKAGE_EXPORT  CodeSynthesis::XSD)
  
    if (BUILD_THIRDPARTY_TEST)
        option(BUILD_${PACKAGE_NAME}_AVAILABILITY_TEST "Build ${PACKAGE_NAME} sample project for testing" ON)
    endif()
    cmake_parse_arguments("${PACKAGE_NAME}" "REQUIRED" "" ""  ${ARGN})
    find_package(${PACKAGE_NAME} QUIET)
    Set(FETCHCONTENT_QUIET FALSE)
    option(MOHSES_FETCH_THIRDPARTY "This option will try t  o fetch third party dependencies for building" ON)
    if ( NOT ${PACKAGE_NAME}_FOUND )
        if (MOHSES_FETCH_THIRDPARTY)

            set(CMAKE_FOLDER "${CMAKE_FOLDER}/${PACKAGE_NAME}")
            FetchContent_Declare(
                ${PACKAGE_NAME}
                GIT_REPOSITORY ${GIT_REPOSITORY} 
                GIT_TAG ${GIT_TAG}
                GIT_PROGRESS TRUE
                VERRIDE_FIND_PACKAGE  TRUE
                CXX_STANDARD 20
            )
            message(STATUS "${PACKAGE_NAME} not found Fetching ${GIT_TAG}")          
    
            FetchContent_MakeAvailable(${PACKAGE_NAME})

            if (WIN32)
              set(${PACKAGE_NAME}_INCLUDE_DIR  ${${FETCH_NAME}_SOURCE_DIR}/x86_64-windows-msvc/libxsd CACHE PATH "Path to XSD header files" )
              set(${PACKAGE_NAME}_EXECUTABLE  ${${FETCH_NAME}_SOURCE_DIR}/x86_64-windows-msvc/bin/xsd.exe CACHE PATH "XSD Compiler to use for code generation" )
              set(${PACKAGE_NAME}_DIR   ${${FETCH_NAME}_SOURCE_DIR}/x86_64-windows-msvc/ CACHE PATH "DIR which contains cmake files" )
            else()
              set(${PACKAGE_NAME}_INCLUDE_DIR ${${FETCH_NAME}_SOURCE_DIR}/x86_64-linux-gnu/libxsd)
              set(${PACKAGE_NAME}_EXECUTABLE  ${${FETCH_NAME}_SOURCE_DIR}/x86_64-linux-gnu/bin/xsd)
              set(${PACKAGE_NAME}_DIR  ${${FETCH_NAME}_SOURCE_DIR}/x86_64-linux-gnu/)
            endif()
            mark_as_advanced(CodeSynthesis_DIR)
            set(CodeSynthesis_FOUND TRUE CACHE INTERNAL "CodeSynthesis HAS BEN FOUND !"   FORCE)
        endif()
    endif()

    if (${PACKAGE_NAME}_REQUIRED AND NOT ${PACKAGE_NAME}_FOUND)
        message(FATAL_ERROR "Unable to find ${PACKAGE_NAME} or fetch it from ${GIT_REPOSITROY}. 
        Check your network connection or install the ${PACKAGE_NAME} package and configure your CMAKE_PREFIX_PATH to ensure visibility
        https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
        https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
    endif()


endfunction()

guarantee_CodeSynthesis_availability()
