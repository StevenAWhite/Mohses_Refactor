cmake_minimum_required(VERSION 3.20.0)

function(guarantee_TinyXML2_availability)
    set(GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git)
    set(GIT_TAG 8.1.0)

    if (BUILD_THIRDPARTY_TEST)
        option(BUILD_TinyXML2_AVAILABILITY_TEST "Build TinyXML2 sample project for testing" ON)
    endif()
    cmake_parse_arguments("TinyXML2" "REQUIRED" "" ""  ${ARGN})
    find_package(TinyXML2 QUIET)
    Set(FETCHCONTENT_QUIET FALSE)
    option(MOHSES_FETCH_THIRDPARTY "This option will try to fetch third party dependencies for building" ON)
    if ( NOT TinyXML2_FOUND )
        if (MOHSES_FETCH_THIRDPARTY)

            set(CMAKE_FOLDER "${CMAKE_FOLDER}/TinyXML2")
            FetchContent_Declare(
                TinyXML2
                GIT_REPOSITORY ${GIT_REPOSITORY} 
                GIT_TAG ${GIT_TAG}
                GIT_PROGRESS TRUE
                OVERRIDE_FIND_PACKAGE  TRUE
            
            )
            message(STATUS "TinyXML2 not found Fetching ${GIT_TAG}")          
    
            FetchContent_MakeAvailable(TinyXML2)

            if(NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/TinyXML2-extra.cmake AND
            NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/TinyXML2Extra.cmake)
            get_target_property(TINYXML2_INCLUDE_DIR  tinyxml2::tinyxml2 INCLUDE_DIRECTORIES)
           file(WRITE ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/TinyXML2-extra.cmake                                
            "
               if(\"\${TINYXML2_INCLUDE_DIR}\" STREQUAL \"\" AND TARGET  tinyxml2::tinyxml2)
                 set(TINYXML2_INCLUDE_DIR ${TINYXML2_INCLUDE_DIR})
               endif()
               if(\"\${TINYXML2_INCLUDE_DIRS}\" STREQUAL \"\" AND TARGET  tinyxml2::tinyxml2)
                 set(TINYXML2_INCLUDE_DIRS ${TINYXML2_INCLUDE_DIR})
               endif()
               if(\"\${TINYXML2_LIBRARY}\" STREQUAL \"\" AND TARGET  tinyxml2::tinyxml2)
                 set(TINYXML2_LIBRARY tinyxml2::tinyxml2)
               endif()
               if(\"\${TINYXML2_LIBRARIES}\" STREQUAL \"\" AND TARGET  tinyxml2::tinyxml2)
                 set(TINYXML2_LIBRARIES  tinyxml2::tinyxml2)
               endif()
            ")
         endif()

            if (BUILD_TinyXML2_AVAILABILITY_TEST AND BUILD_THIRDPARTY_TEST)
                add_executable(TinyXML2_test ${PROJECT_SOURCE_DIR}/cmake/tests/TinyXML2.cpp )
                set_target_properties(TinyXML2_test PROPERTIES FOLDER "${CMAKE_FOLDER}/Tests")
                target_link_libraries(TinyXML2_test PRIVATE tinyxml2::tinyxml2 )            
            endif()
        endif()
    endif()

    if (TinyXML2_REQUIRED AND NOT TinyXML2_FOUND)
        message(FATAL_ERROR "Unable to find TinyXML2 or fetch it from ${GIT_REPOSITROY}. 
        Check your network connection or install the TinyXML2 package and configure your CMAKE_PREFIX_PATH to ensure visibility
        https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
        https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
    endif()


endfunction()
