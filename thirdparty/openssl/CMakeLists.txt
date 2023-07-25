cmake_minimum_required(VERSION 3.25.0)

include (FetchContent)

function(guarantee_openssl_availability)
   set(GIT_REPOSITORY https://github.com/viaduck/openssl-cmake.git )
   set(GIT_TAG 3.0)
   set(PACKAGE_NAME openssl)
   set(PACKAGE_PREFIX OPENSSL)

   if (BUILD_THIRDPARTY_TEST)
        option(BUILD_${PACKAGE_NAME}_AVAILABILITY_TEST "Build ${PACKAGE_NAME} sample project for testing" ON)
   endif()
   cmake_parse_arguments("${PACKAGE_NAME}" "REQUIRED" "" ""  ${ARGN})
   find_package(OpenSSL QUIET GLOBAL)
   Set(FETCHCONTENT_QUIET FALSE)
   option(MOHSES_FETCH_THIRDPARTY "This option will try to fetch third party dependencies for building" ON)
   if ( NOT ${PACKAGE_NAME}_FOUND AND NOT MSVC)
        if (MOHSES_FETCH_THIRDPARTY)
            set(CMAKE_FOLDER "${CMAKE_FOLDER}/${PACKAGE_NAME}")
            FetchContent_Declare(
                ${PACKAGE_NAME}
                GIT_REPOSITORY ${GIT_REPOSITORY} 
                GIT_TAG ${GIT_TAG}
                GIT_PROGRESS TRUE
                OVERRIDE_FIND_PACKAGE  TRUE
                CMAKE_ARGS -D BUILD_${PACKAGE_PREFIX}=ON
                           -D ${PACKAGE_PREFIX}_BRANCH=OpenSSL_3.1.0
            )
            message(STATUS "${PACKAGE_NAME} not found Fetching 2.10")
          
    
            FetchContent_MakeAvailable(${PACKAGE_NAME})
            if(NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PACKAGE_NAME}-extra.cmake AND
            NOT EXISTS ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PACKAGE_NAME}Extra.cmake)
               file(WRITE ${CMAKE_FIND_PACKAGE_REDIRECTS_DIR}/${PACKAGE_NAME}-extra.cmake                                
               "
                  if(\"\${${PACKAGE_PREFIX}_INCLUDE_DIR}\" STREQUAL \"\" AND TARGET  ${PACKAGE_NAME})
                    set(${PACKAGE_PREFIX}_INCLUDE_DIR ${${PACKAGE_PREFIX}_INCLUDE_DIR})
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_INCLUDE_DIRS}\" STREQUAL \"\" AND TARGET  ${PACKAGE_NAME})
                    set(${PACKAGE_PREFIX}_INCLUDE_DIRS ${${PACKAGE_PREFIX}_INCLUDE_DIR})
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_LIBRARY_DEBUG}\" STREQUAL \"\" AND TARGET  ${PACKAGE_NAME})
                    set(${PACKAGE_PREFIX}_LIBRARY ${${PACKAGE_PREFIX}_LIBRARY_DEBUG})
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_LIBRARY_RELEASE}\" STREQUAL \"\" AND TARGET  ${PACKAGE_NAME})
                    set(${PACKAGE_PREFIX}_LIBRARY_RELEASE  ${${PACKAGE_PREFIX}_LIBRARY_RELEASE})
                  endif()
                  if(\"\${${PACKAGE_PREFIX}_LIBRARIES}\" STREQUAL \"\" AND TARGET  ${PACKAGE_NAME})
                    set(${PACKAGE_PREFIX}_LIBRARIES  optimized ${${PACKAGE_PREFIX}_LIBRARY_RELEASE} debug ${${PACKAGE_PREFIX}_LIBRARY_DEBUG})
                  endif()
               ")
            endif()
            install(TARGETS ${PACKAGE_NAME} EXPORT ${PACKAGE_NAME})  
            export(TARGETS  ${PACKAGE_NAME} FILE ${PACKAGE_NAME}-targets.cmake)
            if (BUILD_${PACKAGE_NAME}_AVAILABILITY_TEST AND BUILD_THIRDPARTY_TEST)
                add_executable(${PACKAGE_NAME}_test ${PACKAGE_SOURCE_DIR}/cmake/tests/${PACKAGE_NAME}.cpp)
                set_target_properties(${PACKAGE_NAME}_test PROPERTIES FOLDER "${CMAKE_FOLDER}/Tests")
                target_link_libraries(${PACKAGE_NAME}_test PRIVATE ${PACKAGE_NAME})            
            endif()
        endif()
   elseif(NOT ${PACKAGE_NAME}_FOUND AND MSVC)
      message(STATUS "OpenSSL binaries are required for this build. Downloads are avaliable for Windows at Shining Light Productions.
                      https://slproweb.com/products/Win32OpenSSL.html . The full development installation of OpenSSL v3.1.1 140MBs.
                      Adjust CMAKE_PREFIX_PATH with the folder containing the instllation.")
      find_package(OpenSSL REQUIRED GLOBAL)
   endif()

   find_package(OpenSSL REQUIRED GLOBAL)
   if (AND NOT ${PACKAGE_NAME}_FOUND)
      message(FATAL_ERROR "Unable to find ${PACKAGE_NAME} or fetch it from ${GIT_REPOSITROY}. 
      Check your network connection or install the ${PACKAGE_NAME} package and configure your CMAKE_PREFIX_PATH to ensure visibility
      https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html 
      https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package")
   endif()


endfunction()

guarantee_openssl_availability()
