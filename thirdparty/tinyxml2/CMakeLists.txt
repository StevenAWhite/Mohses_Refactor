cmake_minimum_required(VERSION 3.25.0)

include(FetchContent)

function(guarantee_TinyXML2_availability)
    set(GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git)
    set(GIT_TAG 8.1.0)

    set(FETCH_NAME tinyxml2)
    set(PACKAGE_NAME TinyXML2)
    set(PACKAGE_PREFIX TINYXML2)
    set(PACKAGE_EXPORT tinyxml2::tinyxml2
    )
    if (BUILD_THIRDPARTY_TEST)
        option(BUILD_${PACKAGE_NAME}_AVAILABILITY_TEST "Build ${PACKAGE_NAME} sample project for testing" ON)
    endif()
    cmake_parse_arguments("${PACKAGE_NAME}" "REQUIRED" "" ""  ${ARGN})
    find_package(${PACKAGE_NAME} QUIET)
    Set(FETCHCONTENT_QUIET FALSE)
    option(MOHSES_FETCH_THIRDPARTY "This option will try to fetch third party dependencies for building" ON)
    if ( NOT ${PACKAGE_NAME}_FOUND )
        if (MOHSES_FETCH_THIRDPARTY)

            set(CMAKE_FOLDER "${CMAKE_FOLDER}/${PACKAGE_NAME}")
            set(tinyxml2_BUILD_TESTING OFF CACHE INTERNAL "Build TinyXML2 Testing" FORCE)
            
            FetchContent_Declare(
                ${PACKAGE_NAME}
                GIT_REPOSITORY ${GIT_REPOSITORY} 
                GIT_TAG ${GIT_TAG}
                GIT_PROGRESS TRUE
                OVERRIDE_FIND_PACKAGE  TRUE
            
            )
            message(STATUS "${PACKAGE_NAME} not found Fetching ${GIT_TAG}")          
    
            FetchContent_MakeAvailable(${PACKAGE_NAME})

            if(NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PACKAGE_NAME}-extra.cmake AND
            NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PACKAGE_NAME}Extra.cmake)
               get_target_property(${PACKAGE_PREFIX}_INCLUDE_DIR  ${PACKAGE_EXPORT} INCLUDE_DIRECTORIES)
               get_target_property(${PACKAGE_PREFIX}_OUTPUT_NAME_Release  tinyxml2 OUTPUT_NAME_Release)

               file(WRITE ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PACKAGE_NAME}-extra.cmake                                
               "
                  if(\"\${${PACKAGE_PREFIX}_INCLUDE_DIR}\" STREQUAL \"\" AND TARGET  ${PACKAGE_EXPORT})
                    set(${PACKAGE_PREFIX}_INCLUDE_DIR ${${PACKAGE_PREFIX}_INCLUDE_DIR})
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_INCLUDE_DIRS}\" STREQUAL \"\" AND TARGET  ${PACKAGE_EXPORT})
                    set(${PACKAGE_PREFIX}_INCLUDE_DIRS ${${PACKAGE_PREFIX}_INCLUDE_DIR})
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_LIBRARY}\" STREQUAL \"\" AND TARGET  ${PACKAGE_EXPORT})
                    set(${PACKAGE_PREFIX}_LIBRARY ${PACKAGE_EXPORT})
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_LIBRARIES}\" STREQUAL \"\" AND TARGET  ${PACKAGE_EXPORT})
                    set(${PACKAGE_PREFIX}_LIBRARIES  ${PACKAGE_EXPORT})
                  endif()
               ")
            endif()
             install(TARGETS tinyxml2 EXPORT ${PACKAGE_NAME})  
             export(TARGETS tinyxml2 FILE ${PACKAGE_NAME}-targets.cmake)

             file(WRITE ${${FETCH_NAME}_SOURCE_DIR}/cmake/tinyxml2.pc.in
             "
                prefix=@CMAKE_INSTALL_PREFIX@
                exec_prefix=\${prefix}
                libdir=\${exec_prefix}/@CMAKE_INSTALL_LIBDIR@
                includedir=\${prefix}/@CMAKE_INSTALL_INCLUDEDIR@

                Name: TinyXML2
                Description: simple, small, C++ XML parser
                Version: @tinyxml2_VERSION@
                Libs: -L\${libdir} -ltinyxml2
                Cflags: -I\${includedir}
             "
             )

             
            if (BUILD_${PACKAGE_NAME}_AVAILABILITY_TEST AND BUILD_THIRDPARTY_TEST)
                add_executable(${PACKAGE_NAME}_test ${CMAKE_CURRENT_SOURCE_DIR}/tests/${PACKAGE_NAME}.cpp )
                set_target_properties(${PACKAGE_NAME}_test PROPERTIES FOLDER "${CMAKE_FOLDER}/Tests")
                target_link_libraries(${PACKAGE_NAME}_test PRIVATE ${PACKAGE_EXPORT} )            
            endif()
        endif()
    endif()

    if (${PACKAGE_NAME}_REQUIRED AND NOT ${PACKAGE_NAME}_FOUND)
        message(FATAL_ERROR "Unable to find ${PACKAGE_NAME} or fetch it from ${GIT_REPOSITROY}. 
        Check your network connection or install the ${PACKAGE_NAME} package and configure your CMAKE_PREFIX_PATH to ensure visibility
        https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
        https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
    endif()


endfunction()

guarantee_TinyXML2_availability()
