cmake_minimum_required(VERSION 3.25.0)

include(FetchContent)

function(guarantee_CodeSynthesis_availability)
    set(GIT_REPOSITORY https://github.com/StevenAWhite/CodeSynthesisXSD-Binary.git)
    set(GIT_TAG 39f8501)


    set(PACKAGE_NAME CodeSynthesis)
    set(FETCH_NAME   codesynthesis)
    set(PACKAGE_PREFIX XSD)
    set(PACKAGE_EXPORT  CodeSynthesis::XSD)
  
    cmake_parse_arguments("${PACKAGE_NAME}" "REQUIRED" "" ""  ${ARGN})
    find_package(${PACKAGE_NAME} QUIET GLOBAL)
    Set(FETCHCONTENT_QUIET FALSE)
    if ( NOT ${PACKAGE_NAME}_FOUND )
        if (MOHSES_FETCH_THIRDPARTY)
            if (BUILD_THIRDPARTY_TEST)
                option(BUILD_${PACKAGE_NAME}_AVAILABILITY_TEST "Build ${PACKAGE_NAME} sample project for testing" ON)
            endif()

            set(CMAKE_FOLDER "${CMAKE_FOLDER}/${PACKAGE_NAME}")
            FetchContent_Declare(
                ${PACKAGE_NAME}
                GIT_REPOSITORY ${GIT_REPOSITORY} 
                GIT_TAG ${GIT_TAG}
                GIT_PROGRESS TRUE
                DOWNLOAD_EXTRACT_TIMESTAMP TRUE
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
             find_path(${PACKAGE_NAME}_DIR NAMES libxsd PATHS ${${FETCH_NAME}_SOURCE_DIR}/x86_64-linux-gnu/ NO_DEFAULT_PATH)
             find_file(${PACKAGE_NAME}_EXECUTABLE  NAMES xsd PATHS ${${FETCH_NAME}_SOURCE_DIR}/x86_64-linux-gnu/bin/ NO_DEFAULT_PATH)
             find_path(${PACKAGE_NAME}_INCLUDE_DIR  NAMES "xsd/cxx/config.hxx"  PATHS ${${FETCH_NAME}_SOURCE_DIR}/x86_64-linux-gnu/libxsd NO_DEFAULT_PATH)
            endif()

            mark_as_advanced(CodeSynthesis_DIR)
            set(CodeSynthesis_FOUND TRUE CACHE INTERNAL "CodeSynthesis HAS BEN FOUND !"   FORCE)
            if (NOT TARGET ${PACKAGE_EXPORT})
                add_library(${PACKAGE_EXPORT} INTERFACE IMPORTED GLOBAL)
                
                set_target_properties(${PACKAGE_EXPORT}
                PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES
                ${${FETCH_NAME}_SOURCE_DIR}
                )
                target_include_directories(${PACKAGE_EXPORT} INTERFACE $<INSTALL_INTERFACE:include> $<BUILD_INTERFACE:${${PACKAGE_NAME}_INCLUDE_DIR}> )
                target_link_libraries(${PACKAGE_EXPORT} INTERFACE Xerces::xerces)
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

guarantee_CodeSynthesis_availability()
